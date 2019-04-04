//
// Created by ellonet on 4/2/19.
//
#include <stdlib.h>
#include <string>
#include <stack>

using namespace std;

#ifndef EX2_THREAD_H
#define EX2_THREAD_H

typedef void (*func)(void);

enum state {
    READY, RUNNING, BLOCKED
};


class Thread {

public:
    Thread() = default;

    Thread(int quantum, int id, func f, int stack_size) : _quantum(quantum), _id(id), _f(f), _status(READY) {
        thread_stack = new char[stack_size];
    }

    ~Thread() {
        delete[] thread_stack;
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

    int get_quantum() {
        return _quantum;
    }

    void set_quantum(int q) {
        _quantum = q;
    }

    void decrease_quantum() {
        --_quantum;
    }

private:
    int _quantum;
    int _id;
    func _f;
    int _status;
    char *thread_stack; // TODO - if accessing stack - make sure range is legal
};


#endif //EX2_THREAD_H
