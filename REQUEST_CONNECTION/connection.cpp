#include "connection.h"

Connection::Connection(const Connection& other): priority(other.priority), count(other.count){
    ++*count;
}

Connection& Connection::operator=(const Connection& other) {
    if (--*count == 0) {
        delete priority;
        delete count;
    }
    priority = other.priority;
    count = other.count;
    ++*count;
    return *this; 
}

size_t Connection::getPriority() {
    return *priority;
}

void Connection::setPriority(size_t p) {
    *priority = p;
}

Connection::~Connection() {
    if (--*count == 0){
        delete priority;
        delete count;
    } 
};