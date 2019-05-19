//
// Created by yehoshua on 26/01/17.
//

#include <unistd.h>
#include "ThreadPool.h"

static void* start_thread(void* arg)
{
    ThreadPool* tp = (ThreadPool*) arg;
    tp->execute_thread();
    return NULL;
}


ThreadPool::ThreadPool(int pool_size) {
    pthread_mutex_init(&this->lock,NULL);
    this->poolSize = pool_size;
    for (int i = 0; i < this->poolSize; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, start_thread, (void*) this);
        this->threads.push_back(tid);
    }
}

ThreadPool::~ThreadPool() {
    pthread_mutex_destroy(&this->lock);
}

void ThreadPool::execute_thread() {
    while(true) {
        pthread_mutex_lock(&this->lock);
        while (this->tasks.empty()){}
        Task* task = this->tasks.front();
        this->tasks.pop_front();
        (*task)();
        pthread_mutex_unlock(&this->lock);
        //delete task;
    }
}

void ThreadPool::add_task(Task *task) {
    this->tasks.push_back(task);
}
