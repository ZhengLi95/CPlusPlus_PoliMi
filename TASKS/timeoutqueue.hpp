#ifndef TIMEOUTQUEUE_HPP
#define TIMEOUTQUEUE_HPP

#include "queue.hpp"
#include <ctime>

class TimeoutQueue: public Queue{
    public:
    TimeoutQueue(std::time_t timeout):Queue(), timeout(timeout){};
    void enqueue(Task &) override;
    std::vector<int> execute() override;
    bool empty() override;
    
    protected:
    std::time_t timeout;
    void remove_expired();
};

#endif