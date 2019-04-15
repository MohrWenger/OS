#include <stdlib.h>
#include <string>
#include <stack>
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>

using namespace std;

#ifndef EX2_THREAD_H
#define EX2_THREAD_H

typedef void (*func)(void);

/**
 * Enum list representing the possible states for a Thread object.
 */
enum state {
    READY, RUNNING, BLOCKED, TERMINATE, SLEEPING
};

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/**
 * This function translates the given address to maching language.
 * @param addr - the address to be translated.
 * @return the translated address.
 */
address_t translate_address(address_t addr) {
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
                 "rol    $0x11,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
        "rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}
#endif


class Thread {

public:
    /**
     * A default constructor.
     * used in the initialization of the Thread containers.
     */
    Thread() = default;

    /**
     * A constructor of a Thread with the given ID and the PC value.
     * @param id - thread id
     * @param f - the function this thread runs.
     * @param stack_size - the stack size allocated for this thread.
     */
    Thread(int id, func f, int stack_size) : _times_ran(0), _id(id), _status(READY) {
        _pc = translate_address((address_t) f);
        _sp = new char[stack_size];
        (env->__jmpbuf)[JB_PC] = _pc;
        (env->__jmpbuf)[JB_SP] = translate_address((address_t) _sp + stack_size - sizeof(unsigned int));
        sigemptyset(&env->__saved_mask);

    }

    /**
     * A constructor which safely deletes the allocated stack.
     */
    ~Thread() {
        delete[] _sp;
    }

    /**
     * @returns the id of this thread
     */
    int get_id() {
        return _id;
    }

    /**
     * @returns the status of this thread
     */
    int get_status() {
        return _status;
    }

    /**
     * sets the status of this thread.
     * @param s - the new status.
     */
    void set_status(state s) {
        _status = s;
    }

    /**
     * Increments the times this thread was in running mode
     */
    void inc_times_ran() {
        ++_times_ran;
    }

    /**
     * @returns the times this thread ran.
     */
    int get_times_ran() {
        return _times_ran;
    }

    /**
     * @returns the context of this thread as it was saved last.
     */
    sigjmp_buf *get_env() {
        return &env;
    }


private:

    /** Holds the amount of times this thread was in running mode */
    int _times_ran;
    /** The id of this thread */
    int _id;
    /** The current status of this thread */
    int _status;
    /** The address of the program code of this thread */
    address_t _pc;
    /** A pointer to the stack of this thread */
    char *_sp;
    /** A sigjmp_buf object which holds the context of this thread */
    sigjmp_buf env;
};


#endif //EX2_THREAD_H
