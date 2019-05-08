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


struct ThreadContext {
    // TODO - change redundant pointers..
    pthread_t *workingThreads;
    atomic<int> atomic_index;
    const MapReduceClient *global_client;
    const InputVec *inputVec;
    OutputVec *outputVec;
    Barrier *barrier;
    sem_t *semaphore;
    atomic<int> dealer;
    int thNum;
    stage_t jobStage;
    atomic<int> mapCounter;
    atomic<int> reduceCounter;
    int mapTotal;
    atomic<int> reduceTotal;
    vector<IntermediateVec *> phase2vec;
    pthread_mutex_t lock_shuffledPairs{};
    pthread_mutex_t lock_outputVec{};
    deque<IntermediateVec> shuffledPairs;
    bool wasJoined;

    ThreadContext(pthread_t *workingTh, const MapReduceClient *client,
                  const InputVec *input, OutputVec *output, Barrier *bar, sem_t *sem, int num) :
            workingThreads(workingTh), atomic_index(0), global_client(client), inputVec(input), outputVec(output),
            barrier(bar), semaphore(sem), dealer(0), thNum(num), jobStage(MAP_STAGE), mapCounter(0),
            reduceCounter(0), mapTotal(0), reduceTotal(0),wasJoined(0){};

    ~ThreadContext() {
        free(workingThreads);
        for (auto vec2: phase2vec)
        {
            delete(vec2);
        }

        //TODO - add more
    }

} typedef ThreadContext;

///////////////////// private functions /////////////////////

bool compareKeys(IntermediatePair &p1, IntermediatePair &p2) {
    return (*(p1.first) < *(p2.first)); //they only implemented <

}

IntermediatePair *getMax(vector<IntermediateVec *> vecs) //get maximum to compare
{
    IntermediatePair *max = nullptr;
    for (auto &vec : vecs) {
        if (!max && !(vec->empty())) // if there isn't a value ther yet then put one.
        {
            max = &vec->back();
        } else if (!(vec->empty())) {
            if (*(max->first) < *(vec->back().first)) {
                max = &vec->back();
            }
        }
    }
    return max;
}

void shuffle(ThreadContext * context) {
    context->jobStage = REDUCE_STAGE;
    IntermediatePair *max = getMax(context->phase2vec);
    IntermediateVec tempVec;
    while (max) // while it doesn't return a nullptr because there exists a max
    {
        for (auto &i : context->phase2vec) {
            while (!(i->empty()) && !(*(i->back().first) < *max->first)) {
                tempVec.push_back(i->back());
                i->pop_back();
            }
        }
        if (pthread_mutex_lock(&context->lock_shuffledPairs) != 0) {
            fprintf(stderr, "In Shuffle: error on pthread_mutex_lock");
            exit(1);
        }
        context->shuffledPairs.push_back(tempVec);
        context->reduceTotal++;
        sem_post(context->semaphore);
        if (pthread_mutex_unlock(&context->lock_shuffledPairs) != 0) {
            fprintf(stderr, "In Shuffle: error on pthread_mutex_unlock");
            exit(1);
        }

        tempVec.clear();
        max = getMax(context->phase2vec);
    }
}


void *threadWrapper(void *arg) {
    auto context = (ThreadContext *) arg; // casting in order to use the attributes of the vector
    int len = (int) context->inputVec->size();
    int old = (context->atomic_index)++;
    auto map_results = new(IntermediateVec);

    while (old < len) {

        context->global_client->map(context->inputVec->at(old).first, context->inputVec->at(old).second,
                                    map_results);
        old = (context->atomic_index)++;
        context->mapCounter++;
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

    context->barrier->barrier(); // barrier - wait until all threads finish mapping.

    if (!((context->dealer)++)) {
        shuffle(context);
    }

    while (!context->shuffledPairs.empty()) { // TODO - is this the correct condition?

        sem_wait(context->semaphore);

        if (pthread_mutex_lock(&context->lock_shuffledPairs) != 0) {
            fprintf(stderr, "In threadWrapper: error on pthread_mutex_lock");
            exit(1);
        }
        if (!context->shuffledPairs.empty()) {
            context->global_client->reduce(&context->shuffledPairs.back(), context);
            context->shuffledPairs.pop_back();
            context->reduceCounter++;
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


void emit2(K2 *key, V2 *value, void *context) {
    auto jobVec = (IntermediateVec *) context;
    IntermediatePair toAdd = std::make_pair(key, value);
    jobVec->push_back(toAdd);
}

void emit3(K3 *key, V3 *value, void *context) {
    auto local_context = (ThreadContext *) context;
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


void *init_mutexes(ThreadContext * jobContext) {
    if (pthread_mutex_init(&jobContext->lock_shuffledPairs, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }
    if (pthread_mutex_init(&jobContext->lock_outputVec, nullptr) != 0) {
        cout << "Error initializing mutex" << endl;
        return nullptr;
    }
    return nullptr;
}

JobHandle startMapReduceJob(const MapReduceClient &client,
                            const InputVec &inputVec, OutputVec &outputVec,
                            int multiThreadLevel) {

    // initializing variables
    cout << "heree " << endl;
    auto *barrier = new Barrier(multiThreadLevel);
    auto semaphore = new sem_t;
    sem_init(semaphore, 0, 1);

    auto workingThreads = new pthread_t[multiThreadLevel];
    auto jobContext = new ThreadContext(workingThreads, &client, &inputVec, &outputVec, barrier,
                                        semaphore, multiThreadLevel);

    init_mutexes(jobContext); // init mutexes
    for (unsigned long i = 0; i < multiThreadLevel; ++i) { // creating threads
        pthread_create(jobContext->workingThreads + i, nullptr, threadWrapper, jobContext);
    }

    return jobContext;
}

void waitForJob(JobHandle job) {
    auto jobContex = (ThreadContext *) job;
//    bool joined = false;
    for (unsigned long i = 0; i < jobContex->thNum; ++i) {
        if (jobContex->wasJoined == false) {
            pthread_join(*(jobContex->workingThreads + i), nullptr);
            jobContex->wasJoined = true;
        }
    }
}

void getJobState(JobHandle job, JobState *state) {
    // TODO - count status of work -
    auto jobContext = (ThreadContext *) job;
    auto allMapJobs = jobContext->inputVec->size();
    auto allReduceJobs = (float) jobContext->reduceTotal;
    auto currMap = (float) jobContext->mapCounter;
    auto currRed = (float) jobContext->reduceCounter;


    state->stage = jobContext->jobStage;
    state->percentage = ((currMap + currRed) / (allMapJobs + allReduceJobs)) * 100;
    // for map 100% = size of inputVec
    //         1% = each time we called client map
    // for reduce 100% = len of shuffled pairs
    //            x% = x len of subvector
}

void closeJobHandle(JobHandle job) {
    waitForJob(job);
    auto jobContext = (ThreadContext *) job;
    jobContext->~ThreadContext();
    // TODO - delete everything kill them all!
}