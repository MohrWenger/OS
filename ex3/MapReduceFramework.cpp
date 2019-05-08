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

/**
 * This is aa sturct that keeps all the context that is relevant for all the threads in the same job
 */
struct ThreadContext {
    // TODO - change redundant pointers..
    pthread_t *workingThreads;
    atomic<int> atomic_index;
    const MapReduceClient *global_client;
    const InputVec *inputVec;
    OutputVec *outputVec;
    Barrier barrier;
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

    /**
     * This is the constructor for the Thread context
     * @param workingTh a list of the worknig threads
     * @param client  the client whos map reduce functions we run
     * @param input the input given
     * @param output a pointer to where we put the output
     * @param sem a semaphor
     * @param num the number of threads
     */
    ThreadContext(pthread_t *workingTh, const MapReduceClient *client,
                  const InputVec *input, OutputVec *output, sem_t *sem, int num) :
            workingThreads(workingTh), atomic_index(0), global_client(client), inputVec(input), outputVec(output),
            barrier(Barrier(num)), semaphore(sem), dealer(0), thNum(num), jobStage(MAP_STAGE), mapCounter(0),
            reduceCounter(0), mapTotal(0), reduceTotal(0), wasJoined(false) {};

    /**
     * S destructor for the thread context
     */
    ~ThreadContext() {
        delete[] workingThreads;
        for (auto vec2: phase2vec) {
            delete (vec2);
        }
        delete semaphore;
    }

} typedef ThreadContext;

///////////////////// private functions /////////////////////

/**
 * a compartor we use to sort the pairs
 * @param p1 first pair
 * @param p2 second pair
 * @return if the first pair is smaller then the second
 */
bool compareKeys(IntermediatePair &p1, IntermediatePair &p2) {
    return (*(p1.first) < *(p2.first)); //they only implemented <

}

/**
 * gets the maximum value  of all pairs
 * @param vecs a vector f vector of pairs
 * @return the maximim
 */
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

/**
 * shuffles the results of the map
 */
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

/**
 * This is the actuall proceedure for each thread
 * @param arg the context for every job
 * @return nullptr ( nessecary so we can add it o thread create )
 */
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

    context->barrier.barrier(); // barrier - wait until all threads finish mapping.

    if (!((context->dealer)++)) {
        shuffle(context);
    }

    while (!context->shuffledPairs.empty()) {

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

/**
 * creates the intermediate vector
 * @param key a key from the map
 * @param value the value produced from the map
 * @param context the vector to add the pairs to
 */
void emit2(K2 *key, V2 *value, void *context) {
    auto jobVec = (IntermediateVec *) context;
    IntermediatePair toAdd = std::make_pair(key, value);
    jobVec->push_back(toAdd);
}

/**
 * creates the vector for the output
 * @param key a key to put the vector in
 * @param value the value to produce from the reduce
 * @param context the context for all the job
 */
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

/**
 * initializes the mutexes
 */
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
    auto semaphore = new sem_t;
    sem_init(semaphore, 0, 1);

    auto workingThreads = new pthread_t[multiThreadLevel];
    auto jobContext = new ThreadContext(workingThreads, &client, &inputVec, &outputVec, semaphore, multiThreadLevel);
    init_mutexes(jobContext); // init mutexes
    for (int i = 0; i < multiThreadLevel; ++i) { // creating threads
        pthread_create(jobContext->workingThreads + i, nullptr, threadWrapper, jobContext);
    }

    return jobContext;
}

/**
 * joins the threads to make sure they all finish
 * @param job the job context of the threads we want to connect
 */
void waitForJob(JobHandle job) {
    auto jobContex = (ThreadContext *) job;
    for (int i = 0; i < jobContex->thNum; ++i) {
        if (!jobContex->wasJoined) {
            pthread_join(*(jobContex->workingThreads + i), nullptr);
        }
    }
    jobContex->wasJoined = true;
}

/**
 * return the job state and percentage
 * @param job the job handle of the job we want to get the state of
 * @param state the state of the relevant job
 */
void getJobState(JobHandle job, JobState *state) {
    auto jobContext = (ThreadContext *) job;
    auto allMapJobs = jobContext->inputVec->size();
    auto allReduceJobs = (float) jobContext->reduceTotal;
    auto currMap = (float) jobContext->mapCounter;
    auto currRed = (float) jobContext->reduceCounter;

    state->stage = jobContext->jobStage;
    state->percentage = ((currMap + currRed) / (allMapJobs + allReduceJobs)) * 100;
}

/**
 * closes and frees the heap
 * @param job the job of the current state
 */
void closeJobHandle(JobHandle job) {
    waitForJob(job);
    auto jobContext = (ThreadContext *) job;
    delete jobContext;
}