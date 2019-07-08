#include <cstddef>
#include "connection.h"

class Request{
    private:
    size_t sz;
    char *data;
    Connection *connection;
    
    public:
    Request(const char* d, size_t s, const Connection &c);
    Request& operator=(const Request &other);
    Request(const Request &rhs);
    ~Request();
    void print();
    void setElement(size_t, char);
};