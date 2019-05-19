//
// Created by yehoshua on 26/01/17.
//

#include "Task.h"

Task::Task(void *(*func)(void *), void *arg) {
    this->func = func;
    this->arg = arg;
}

void Task::operator()() {
    this->func(this->arg);
}

Task::~Task() {

}
