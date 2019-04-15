//
// Created by ellonet on 4/2/19.
//
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

enum state {
    READY, RUNNING, BLOCKED, TERMINATE, SLEEPING
};

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
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
    Thread() = default;

    Thread( int id, func f, int stack_size) : _times_ran(0), _id(id), _status(READY) ,_is_sleeping(false){
        _pc = translate_address((address_t) f);
        _sp = new char[stack_size];
        //blocked_signals_set inviornment
        (env->__jmpbuf)[JB_PC] = _pc;
        (env->__jmpbuf)[JB_SP] = translate_address((address_t) _sp + stack_size - sizeof(unsigned int));
        sigemptyset(&env->__saved_mask);

    }

    ~Thread() {
        delete[] _sp;
    }

    int get_id() {
        return _id;
    }

    int get_status() {
        return _status;
    }

    void set_status(state s) {
        _status = s;
    }

    void inc_times_ran()
    {
        ++_times_ran;
    }
    int get_times_ran() {
        return _times_ran;
    }

//    void set_timer_virtual(int msec) {
//        _timer.it_value.tv_sec = 0;
//        _timer.it_value.tv_usec = msec;
//    }

//    void reset_quantum(int q) {
//        _times_ran = q;
//    }

    sigjmp_buf *get_env() {
        return &env;
    }

    void set_sleep (bool stat)
    {
        _is_sleeping = stat;
    }

    bool get_sleeping(){
        return _is_sleeping;
    }
private:

    int _times_ran;
    int _id;
    int _status;
//    bool _is_blocked;
    bool _is_sleeping;
    address_t _pc;
    char *_sp; // TODO - if accessing stack - make sure range is legal
    sigjmp_buf env;
//    struct itimerval _timer;
};


#endif //EX2_THREAD_H
