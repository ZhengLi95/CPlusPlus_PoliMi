#include <iostream>
#include "request.h"

Request::Request(const char* d, size_t s, const Connection& c): sz(s), data(new char[s]), connection(new Connection(c)) {
    for (size_t i = 0; i<s; ++i)
        data[i] = d[i];
}

Request::Request(const Request& other): sz(other.sz), connection(new Connection(*other.connection)){
    data = new char[sz];
    for (size_t i = 0; i<other.sz; ++i)
    data[i] = other.data[i]; 
}

Request& Request::operator=(const Request& other) {
    sz = other.sz;
    char *temp = new char[sz];
    for (size_t i = 0; i< sz; ++i)
    temp[i] = other.data[i];
    delete[] data;
    delete connection;
    data = temp;
    connection = new Connection(*other.connection);
    return *this; 
}

void Request::setElement(size_t i, char elem) {
    if (i < sz)
        data[i] = elem;
}
    
void Request::print() {
    for (size_t i = 0; i<sz; ++i)
        std::cout << data[i] << ", ";
    std::cout << connection->getPriority();
    std::cout << std::endl; 
}

Request::~Request() {
    delete[] data;
    delete connection;
}