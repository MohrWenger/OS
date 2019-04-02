//
// Created by ellonet on 4/2/19.
//
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef EX2_THREAD_H
#define EX2_THREAD_H

typedef void (*func)(void);

enum state {
    READY, RUNNING, BLOCKED
};


class Thread {

public:
    Thread(int quantum, int id, func f) : _quantum(quantum), _id(id), _f(f), _status(READY) {}

    int get_status() {
        return _status;
    }

    int get_quantum() {
        return _quantum;
    }

    int get_id() {
        return _id;
    }

private:
    int _quantum;
    int _id;
    func _f;
    int _status;
};


#endif //EX2_THREAD_H
