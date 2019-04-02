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
    BLOCKED, READY, RUNNING
};


class Thread {

public:
    Thread(int quantum, int id, func f) : _quantum(quantum), _id(id), _f(f) {}

    string get_status() {
        return status;
    }

    int get_quantum() {
        return _quantum;
    }

    int get_id() {
        return _id;
    }

private:
    func _f;
    int _quantum;
    int _id;
    string status;
};


#endif //EX2_THREAD_H
