#include <stdlib.h>
#include <iostream>
#include "Thread.h"
#include "uthreads.h"
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <signal.h>
#include <setjmp.h>




using namespace std;

/////////////////////////////////// global variables ///////////////////////////////////
map<int, Thread> all_threads;
deque<Thread *> ready_queue;
int lib_quantum;
set<int> available_ids;
Thread* curr_running;
/////////////////////////////////// private functions ///////////////////////////////////

/***
 * @return the next available id
 */
int get_next_id() {
    static int next_id = 1;
    int id;
    if (available_ids.empty()) {
        id = next_id;
        ++next_id;
    } else {
        id = *available_ids.begin();
        available_ids.erase(id);
    }
    return id;
}


Thread* get_next_thread()
{
    if ( ready_queue.empty ())
    {
        return &all_threads[0]; //TODO what now?
    }

    return ready_queue.front();
}




/////////////////////////////////// public functions ///////////////////////////////////
/*
 * Description: This function initializes the thread library.
 * You may assume that this function is called before any other thread library
 * function, and that it is called exactly once. The input to the function is
 * the length of a _quantum in micro-seconds. It is an error to call this
 * function with non-positive quantum_usecs.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_init(int quantum_usecs) {
    if (quantum_usecs <= 0) {
        cerr << "Error - Illegal quantum value" << endl;
        return -1;
    }
    lib_quantum = quantum_usecs;

    try {
        Thread *thread_0 = new Thread(lib_quantum, 1, nullptr, STACK_SIZE);
        all_threads[0] = *thread_0;
        curr_running = thread_0;
    }
    catch (exception &e) {
        cerr << "Error - library initialization failed" << endl;
        return -1;
    }
    return 0;
}

/*
 * Description: This function creates a new thread, whose entry point is the
 * function f with the signature void f(void). The thread is added to the end
 * of the READY threads list. The uthread_spawn function should fail if it
 * would cause the number of concurrent threads to exceed the limit
 * (MAX_THREAD_NUM). Each thread should be allocated with a stack of size
 * STACK_SIZE bytes.
 * Return value: On success, return the ID of the created thread.
 * On failure, return -1.
*/
int uthread_spawn(void (*f)(void)) { // TODO - check allocation success

    // check thread count
    if (all_threads.size() < MAX_THREAD_NUM) {
        int id = get_next_id();
        Thread *new_thread = new Thread(lib_quantum, id, f, STACK_SIZE);
        // add thread to all_threads list and to ready list
        all_threads[id] = *new_thread;
        ready_queue.push_back(new_thread);
        return new_thread->get_id();
    }
    cerr << "Error - exceeded num of allowed threads MADAFAKA" << endl;
    return -1;
}


/*
 * Description: This function terminates the thread with ID tid and deletes
 * it from all relevant control structures. All the resources allocated by
 * the library for this thread should be released. If no thread with ID tid
 * exists it is considered an error. Terminating the main thread
 * (tid == 0) will result in the termination of the entire process using
 * exit(0) [after releasing the assigned library memory].
 * Return value: The function returns 0 if the thread was successfully
 * terminated and -1 otherwise. If a thread terminates itself or the main
 * thread is terminated, the function does not return.
*/
int uthread_terminate(int tid) {    // TODO - make sure to free the allocations using delete
    // TODO - add to enviroment.
    if (!tid) {
        // in case of deleting the main thread
        // TODO - maybe clean up before?
        exit(0);
    }
    Thread *toKill = &all_threads[tid];
    switch (toKill->get_status()) {
        case (READY):
            ready_queue.erase(find(ready_queue.begin(), ready_queue.end(), toKill));
            break;
        case (RUNNING):
            // TODO - stop running, send next ready to run
            break;
        case (BLOCKED):
            // TODO - delete, no one cares
            break;
        default:
            break;
    }
    // re-use the id, and delete the thread.
    available_ids.insert(tid);
    all_threads.erase(tid);
    return 0;
}


/*
 * Description: This function blocks the thread with ID tid. The thread may
 * be resumed later using uthread_resume. If no thread with ID tid exists it
 * is considered as an error. In addition, it is an error to try blocking the
 * main thread (tid == 0). If a thread blocks itself, a scheduling decision
 * should be made. Blocking a thread in BLOCKED state has no
 * effect and is not considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_block(int tid) {
    auto it = all_threads.find(tid);
    if (it == all_threads.end()) {
        cerr << "Error - you stupid dog, you make me look bad" << endl;
        return -1;
    }
    Thread *curr = &(it->second);
    switch (curr->get_status()) {
        case (READY):
            ready_queue.erase(find(ready_queue.begin(), ready_queue.end(), curr));
            break;
        case (RUNNING):
            // TODO - send to handle
            break;
        default: // in this case - do nothing.
            break;
    }

    it->second.set_status(BLOCKED);
    return 0;
}

void switchThreads( state new_st) {
    int ret_val = sigsetjmp(*(curr_running -> get_env()), 1); //TODO update curr_run
    cout << "SWITCHING from: " << curr_running->get_id () << endl;
    if (ret_val == 1) {
        return;
    }

    switch  (new_st)
    {
        case (BLOCKED):
            curr_running -> set_status (new_st);
        case (TERMINATED):
            all_threads.erase (curr_running->get_id ());
        case ( READY ):
            //TODO - set ready queue

    }

    Thread* next_th = get_next_thread();
    curr_running = next_th;
    curr_running->set_status(RUNNING);

    siglongjmp( *(next_th->get_env()), 1);
}


/*
 * Description: This function resumes a blocked thread with ID tid and moves
 * it to the READY state. Resuming a thread in a RUNNING or READY state
 * has no effect and is not considered as an error. If no thread with
 * ID tid exists it is considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_resume(int tid);

/*
 * Description: This function blocks the RUNNING thread for usecs micro-seconds in real time (not virtual
 * time on the cpu). It is considered an error if the main thread (tid==0) calls this function. Immediately after
 * the RUNNING thread transitions to the BLOCKED state a scheduling decision should be made.
 fter the sleeping time is over, the thread should go back to the end of the READY threads list.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_sleep(unsigned int usec);


/*
 * Description: This function returns the thread ID of the calling thread.
 * Return value: The ID of the calling thread.
*/
int uthread_get_tid();


/*
 * Description: This function returns the total number of quantums since
 * the library was initialized, including the current _quantum.
 * Right after the call to uthread_init, the value should be 1.
 * Each time a new _quantum starts, regardless of the reason, this number
 * should be increased by 1.
 * Return value: The total number of quantums.
*/
int uthread_get_total_quantums();


/*
 * Description: This function returns the number of quantums the thread with
 * ID tid was in RUNNING state. On the first time a thread runs, the function
 * should return 1. Every additional _quantum that the thread starts should
 * increase this value by 1 (so if the thread with ID tid is in RUNNING state
 * when this function is called, include also the current _quantum). If no
 * thread with ID tid exists it is considered an error.
 * Return value: On success, return the number of quantums of the thread with ID tid.
 * 			     On failure, return -1.
*/
int uthread_get_quantums(int tid);


