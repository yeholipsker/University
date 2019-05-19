//
// Created by yehoshua on 26/01/17.
//

#ifndef MISSION2_TASK_H
#define MISSION2_TASK_H


class Task {
private:
    void* (*func)(void*);
    void* arg;
public:
    Task(void *(*func)(void*), void* arg);
    ~Task();
    void operator()(); // functor
};


#endif //MISSION2_TASK_H
