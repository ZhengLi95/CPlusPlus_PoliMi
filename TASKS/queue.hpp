#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
#include <task.hpp>

class Queue{
    public:
    virtual void enqueue(Task &) = 0;
    virtual std::vector<int> execute();
    virtual bool empty();

    protected:
    std::vector<Task> tasks;
};

#endif