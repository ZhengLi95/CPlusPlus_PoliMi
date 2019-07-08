#include <cstddef>
#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Connection {
    private:
    size_t *priority;
    size_t *count;
    public:
    Connection(size_t p): priority(new size_t(p)), count(new size_t(1)) {};
    Connection(const Connection&);
    Connection& operator=(const Connection&);
    ~Connection();
    size_t getPriority();
    void setPriority(size_t); 
};

#endif