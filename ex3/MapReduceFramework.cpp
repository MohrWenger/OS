#include "MapReduceFramework.h"
#include <pthread.h>
#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

///////////////////// Global variables /////////////////////


pthread_t *workingThreads;

struct threadContext {
    atomic<int> *atomic_index;
    const MapReduceClient *global_client;
    const InputVec *inputVec;
    OutputVec *outputVec;
    pthread_mutex_t lock;

} typedef threadContext;
///////////////////// private functions /////////////////////


void *mapWrapper(void *arg) {
    auto *context = (threadContext *) arg; // casting in order to use the attributes of the vector
    int len = (int) context->inputVec->size();
    int old = (*(context->atomic_index))++;

    while (old < len) {
        pthread_mutex_lock(&context->lock); // critical
//        std::thread::id this_id = std::this_thread::get_id();
//        std::cout << "thread " << this_id << endl;
//        std::cout << "processing " << context->inputVec->at(old).second << endl;
        context->global_client->map(context->inputVec->at(old).first, context->inputVec->at(old).second, context);
        old = (*(context->atomic_index))++;
        pthread_mutex_unlock(&context->lock); // out of critical
    }
    return nullptr;
}


void mapInput(int threadAmount, threadContext &context) {
    // todo - protect with mutex?
    for (unsigned long i = 0; i < threadAmount; ++i) {
        cout << "create tread i = " << i << endl;
        pthread_create(workingThreads + i, nullptr, mapWrapper, &context);
    }
    for (unsigned long i = 0; i < threadAmount; ++i) {
        pthread_join(*(workingThreads + i), nullptr);
    }

}


/////////////////////////// given ///////////////////////
void emit2(K2 *key, V2 *value, void *context) {
}

void emit3(K3 *key, V3 *value, void *context) {

}

JobHandle startMapReduceJob(const MapReduceClient &client,
                            const InputVec &inputVec, OutputVec &outputVec,
                            int multiThreadLevel) {

    // initializing variables
    std::atomic<int> atomic_index(0);
    threadContext jobContext = {&atomic_index, &client, &inputVec, &outputVec};
    workingThreads = new pthread_t[multiThreadLevel];

    if (pthread_mutex_init(&jobContext.lock, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }

    // activating client's map
    mapInput(multiThreadLevel, jobContext);
    return nullptr;
}

void waitForJob(JobHandle job) {

}

void getJobState(JobHandle job, JobState *state) {

}

void closeJobHandle(JobHandle job) {
    // TODO - delete workingThreads

}
