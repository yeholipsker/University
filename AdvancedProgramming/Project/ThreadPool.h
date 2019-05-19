//
// Created by yehoshua on 26/01/17.
//

#include <iostream>
#include <pthread.h>

#include <deque>
#include <vector>
#include "Task.h"

#ifndef MISSION2_THREADPOOL_H
#define MISSION2_THREADPOOL_H

using namespace std;

class ThreadPool {
private:
    int poolSize;
    vector<pthread_t> threads;
    pthread_mutex_t lock;
    deque<Task * > tasks;
public:
    ThreadPool(int pool_size);
    ~ThreadPool();
    void execute_thread();
    void add_task(Task* task);
};


#endif //MISSION2_THREADPOOL_H
