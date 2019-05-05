#include "MapReduceFramework.h"
#include "Barrier.h"
#include <pthread.h>
#include <atomic>
#include <iostream>
#include <thread>
#include <algorithm>
#include <deque>
#include <semaphore.h>

using namespace std;

///////////////////// Global variables /////////////////////


pthread_t *workingThreads;//TODO - map

//struct barrier {
//    atomic<int> *passed_threads;
//} typedef barrier;

struct threadContext {
    atomic<int> *atomic_index;
    const MapReduceClient *global_client;
    const InputVec *inputVec;
    OutputVec *outputVec;
    Barrier *bar;
    atomic<bool> *dealer;
    sem_t *semaphore;
    vector<IntermediateVec *> phase2vec;
    pthread_mutex_t lock;
    deque<IntermediateVec> shuffledPairs;

} typedef threadContext;

///////////////////// private functions /////////////////////

bool compareKeys(IntermediatePair &p1, IntermediatePair &p2) {
    return (*(p1.first) < *(p2.first)); //they only implemented <

}

IntermediatePair *getMax(vector<IntermediateVec *> vecs) //get maximum to compare
{
    IntermediatePair *max = nullptr;
    for (int i = 0; i < vecs.size(); ++i) {
        if (!max && !(vecs.at(i)->empty())) // if there isn't a value ther yet then put one.
        {
            max = &vecs.at(i)->back();
        } else if (!(vecs.at(i)->empty())) {
            if (*(max->first) < *(vecs.at(i)->back().first)) {
                max = &vecs.at(i)->back();
            }
        }
    }
    return max;
}

void shuffle(threadContext * context) {
    IntermediatePair *max = getMax(context->phase2vec);
    IntermediateVec tempVec;
    while (max) // while it doesn't return a nullptr because there exists a max
    {
        for (auto &i : context->phase2vec) {
            while (!(i->empty()) && !(*(i->back().first) < *max->first)) {
                tempVec.push_back(i->back());
                cout << "size i : " << i->size() << endl;
                i->pop_back();
            }
        }
        context->shuffledPairs.push_back(tempVec);
        // todo - notify all.
        cout << "len is : " << tempVec.size() << endl;
        tempVec.clear();
        max = getMax(context->phase2vec);
    }
}


void *threadWrapper(void *arg) {
    auto context = (threadContext *) arg; // casting in order to use the attributes of the vector
    int len = (int) context->inputVec->size();
    int old = (*(context->atomic_index))++;
    auto map_results = new(IntermediateVec);

    while (old < len) {
        pthread_mutex_lock(&context->lock); // critical TODO - ella down mutex?

        context->global_client->map(context->inputVec->at(old).first, context->inputVec->at(old).second,
                                    map_results);
        old = (*(context->atomic_index))++;

        pthread_mutex_unlock(&context->lock); // out of critical

    }


    sort(map_results->begin(), map_results->end(), compareKeys); // TODO - ella check my comperator
    context->phase2vec.push_back(map_results);
    // barrier - wait until all threads finish maping.
    context->bar->barrier();

    // barrier - wait until all threads finish maping.
    if (*(context->dealer)) {
        *(context->dealer) = false;
        shuffle(context);
        cout << "len of shuffled: " << context->shuffledPairs.size() << endl;
    }


    return nullptr;
}


void MapReduce(int threadAmount, threadContext &context) {
    // todo - protect with mutex?
    for (unsigned long i = 0; i < threadAmount; ++i) {
        pthread_create(workingThreads + i, nullptr, threadWrapper, &context);
    }
    for (unsigned long i = 0; i < threadAmount; ++i) {
        pthread_join(*(workingThreads + i), nullptr);
    }
}


/////////////////////////// given ///////////////////////
void emit2(K2 *key, V2 *value, void *context) {

    auto jobVec = (IntermediateVec *) context;
//    auto toAdd = new IntermediatePair(key, value);
    IntermediatePair toAdd = std::make_pair(key, value);
    jobVec->push_back(toAdd);
}

void emit3(K3 *key, V3 *value, void *context) {

}

JobHandle startMapReduceJob(const MapReduceClient &client,
                            const InputVec &inputVec, OutputVec &outputVec,
                            int multiThreadLevel) {

    // initializing variables
    std::atomic<int> atomic_index(0);
    std::atomic<bool> atomic_dealer(true);
    auto *barrier = new Barrier(multiThreadLevel);
    auto semaphore = new sem_t;
    threadContext jobContext = {&atomic_index, &client, &inputVec, &outputVec, barrier, &atomic_dealer, semaphore};
    workingThreads = new pthread_t[multiThreadLevel];
    // init mutex
    if (pthread_mutex_init(&jobContext.lock, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }
    // activating client's map
    MapReduce(multiThreadLevel, jobContext);
    return nullptr;
}

void waitForJob(JobHandle job) {

}

void getJobState(JobHandle job, JobState *state) {

}

void closeJobHandle(JobHandle job) {
    // TODO - delete workingThreads

}
