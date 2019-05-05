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
    atomic<int> *new_dealer;
    vector<IntermediateVec *> phase2vec;
    pthread_mutex_t lock_shuffledPairs;
    pthread_mutex_t lock_outputVec;
    pthread_mutex_t lock_phase2vec;
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
//                cout << "size i : " << i->size() << endl;
                i->pop_back();
            }
        }
        // TODO - realize that this protection is not needed cuz only one thread goes here
//        if (pthread_mutex_lock(&context->lock_shuffledPairs) != 0) {
//            fprintf(stderr, "In Shuffle: error on pthread_mutex_lock");
//            exit(1);
//        }
        context->shuffledPairs.push_back(tempVec);
        sem_post(context->semaphore);
//        if (pthread_mutex_unlock(&context->lock_shuffledPairs) != 0) {
//            fprintf(stderr, "In Shuffle: error on pthread_mutex_unlock");
//            exit(1);
//        }

        tempVec.clear();
        max = getMax(context->phase2vec);
    }
//    cout << "len of shuffled: " << context->shuffledPairs.size() << endl;
//    flush(cout);
}


void *threadWrapper(void *arg) {
    auto context = (threadContext *) arg; // casting in order to use the attributes of the vector
    int len = (int) context->inputVec->size();
    int old = (*(context->atomic_index))++;
    auto map_results = new(IntermediateVec);

    while (old < len) {
        context->global_client->map(context->inputVec->at(old).first, context->inputVec->at(old).second,
                                    map_results);
        old = (*(context->atomic_index))++;
    }


    sort(map_results->begin(), map_results->end(), compareKeys);
    // locking the common phase2vector:
    if (pthread_mutex_lock(&context->lock_outputVec) != 0) {
        fprintf(stderr, "In emit3: error on pthread_mutex_lock");
        exit(1);
    }
    context->phase2vec.push_back(map_results);
    if (pthread_mutex_unlock(&context->lock_outputVec) != 0) {
        fprintf(stderr, "In emit3: error on pthread_mutex_unlock");
        exit(1);
    }

    // barrier - wait until all threads finish mapping.
    context->bar->barrier();

    if (!((*(context->new_dealer))++)) {    // TODO - explain to mor
        shuffle(context);
    }

    while (!context->shuffledPairs.empty()) {

        sem_wait(context->semaphore);

        //calling client's reduce with API: (const IntermediateVec* pairs, void* context)
        if (pthread_mutex_lock(&context->lock_shuffledPairs) != 0) {
            fprintf(stderr, "In threadWrapper: error on pthread_mutex_lock");
            exit(1);
        }
        if (!context->shuffledPairs.empty()) {
            context->global_client->reduce(&context->shuffledPairs.back(), context);
            context->shuffledPairs.pop_back();
        } else {
            sem_post(context->semaphore);
        }
        if (pthread_mutex_unlock(&context->lock_shuffledPairs) != 0) {
            fprintf(stderr, "In threadWrapper: error on pthread_mutex_lock");
            exit(1);
        }
    }
    return nullptr;
}


void MapReduce(int threadAmount, threadContext &context) {
    // todo - protect with mutex?
    for (unsigned long i = 0; i < threadAmount; ++i) {
        pthread_create(workingThreads + i, nullptr, threadWrapper, &context);
    }
    // TODO - move to wait for join!!
    for (unsigned long i = 0; i < threadAmount; ++i) {
        pthread_join(*(workingThreads + i), nullptr);
    }
    cout << "\nBehold! I have finished reducing\nElla: I'm so clever!!" << endl;
}


/////////////////////////// given ///////////////////////
void emit2(K2 *key, V2 *value, void *context) {
    auto jobVec = (IntermediateVec *) context;
    IntermediatePair toAdd = std::make_pair(key, value);
    jobVec->push_back(toAdd);
}

void emit3(K3 *key, V3 *value, void *context) {
    auto local_context = (threadContext *) context;
    OutputPair toAdd = std::make_pair(key, value);

    if (pthread_mutex_lock(&local_context->lock_outputVec) != 0) {
        fprintf(stderr, "In emit3: error on pthread_mutex_lock");
        exit(1);
    }
    local_context->outputVec->push_back(toAdd);
    if (pthread_mutex_unlock(&local_context->lock_outputVec) != 0) {
        fprintf(stderr, "In emit3: error on pthread_mutex_unlock");
        exit(1);
    }
}

JobHandle startMapReduceJob(const MapReduceClient &client,
                            const InputVec &inputVec, OutputVec &outputVec,
                            int multiThreadLevel) {

    // initializing variables
    std::atomic<int> atomic_index(0);
    std::atomic<int> atomic_index2(0);
    std::atomic<bool> atomic_dealer(true);
    auto *barrier = new Barrier(multiThreadLevel);
    auto semaphore = new sem_t;
    sem_init(semaphore, 0, 1);
    threadContext jobContext = {&atomic_index, &client, &inputVec, &outputVec, barrier, &atomic_dealer, semaphore,
                                &atomic_index2};
    workingThreads = new pthread_t[multiThreadLevel];
    // init mutexes
    if (pthread_mutex_init(&jobContext.lock_shuffledPairs, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }
    if (pthread_mutex_init(&jobContext.lock_outputVec, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }
    if (pthread_mutex_init(&jobContext.lock_phase2vec, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }
    // calling main function
    MapReduce(multiThreadLevel, jobContext);
    return nullptr;
}

void waitForJob(JobHandle job) {
    // TODO - put the join here
}

void getJobState(JobHandle job, JobState *state) {
    // TODO - count status of work -
    // for map 100% = size of inputVec
    //         1% = each time we called client map
    // for reduce 100% = len of shuffled pairs
    //            x% = x len of subvector
}

void closeJobHandle(JobHandle job) {
    // TODO - delete every thing
}