#include "MapReduceFramework.h"
#include "Barrier.h"
#include <pthread.h>
#include <atomic>
#include <iostream>
#include <thread>
#include <algorithm>
#include <deque>

using namespace std;

///////////////////// Global variables /////////////////////


pthread_t *workingThreads;

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
    vector<IntermediateVec *> phase2vec;
    pthread_mutex_t lock;
    deque<IntermediateVec > shuffledPairs;

} typedef threadContext;
///////////////////// private functions /////////////////////

bool equalKeys (IntermediatePair& p1, IntermediatePair& p2)
{
    cout <<p1.first <<"  and  "<< p2.first << (p1<p2) << endl;
    if  (p1 < p2 || p2 < p1) //they only implemented <
    {
        return false;
    }
    return true;
}

IntermediatePair getMax ( vector<IntermediateVec *> vecs) //get maximum to compare
{
    IntermediatePair max;
//    if (vecs.at(0)->empty())
//    {
//        max = nullptr;
//    }
//    IntermediatePair max = vecs.at(0)->back();
//    for (int i = 0; i < vecs.size() ; ++i )
//    {
//        if (! (vecs.at(i)->empty())) {
//            if (max < vecs.at(i)->back()) {
//                max = vecs.at(i)->back();
//            }
//        }
//    }
//    return max;
}

void shuffle (threadContext& context)
{
    IntermediatePair maxim = getMax(context.phase2vec);
    while (maxim) // while it doesn't return a nullptr becuse there exists a max
    for (auto &i : context.phase2vec) {
//            if (i->empty()) {
//                continue;
//            } else {

}
//void shuffle(void *arg) {
//    auto context = (threadContext *) arg;
//    IntermediateVec tempVec;
//    cout << "len of vec = " << context->phase2vec.size() << endl;
//    int allSums = 0;
//    for (int k = 0; k < context->phase2vec.size(); ++k)
//    {
//        allSums += context->phase2vec.at(k)->size();
//    }
//
//    cout << allSums << endl;
//
//    while(allSums > 0) {
//        for (auto &i : context->phase2vec) {
//            if (i->empty()) {
//                continue;
//            } else {
//                auto curr = i->back();
//                if (tempVec.empty() || equalKeys(tempVec.back(), curr)){
//                    if (tempVec.empty())
//                    {
//                        cout << "-->empty" << endl;
//                    }
//
//                    if (!tempVec.empty() )
//                    {
//                        cout << tempVec.back().first << endl;
//                        if(tempVec.back().first == curr.first) {
//                            cout << "eqqqqqqqqqqqqqqqqq <-----" << endl;
//                            continue;
//                        }
//                    }
//
//                    cout << "heree" << endl;
//                    tempVec.push_back(curr);
//                    i->pop_back();
//                    --allSums;
//                    continue;
//                }
//            }
//            context->shuffledPairs.push_back(tempVec);
//            cout << "added" << endl;
//            tempVec.clear();
//        }
//    }
//}


void *threadWrapper(void *arg) {
    auto context = (threadContext *) arg; // casting in order to use the attributes of the vector
    int len = (int) context->inputVec->size();
    int old = (*(context->atomic_index))++;
    auto map_results = new(IntermediateVec);

    while (old < len) {
        pthread_mutex_lock(&context->lock); // critical
        context->global_client->map(context->inputVec->at(old).first, context->inputVec->at(old).second,
                                    map_results);
        old = (*(context->atomic_index))++;
        pthread_mutex_unlock(&context->lock); // out of critical

    }
    sort(map_results->begin(), map_results->end());
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
    threadContext jobContext = {&atomic_index, &client, &inputVec, &outputVec, barrier, &atomic_dealer};
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
