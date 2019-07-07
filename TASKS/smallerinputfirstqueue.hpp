#ifndef SMALLERINPUTFIRSTQUEUE_HPP
#define SMALLERINPUTFIRSTQUEUE_HPP

#include "queue.hpp"

class SmallerInputFirstQueue: public Queue{
    public:
    void enqueue(Task&) override;
};

#endif