#ifndef PROJETO_SCHEDULE_REQUEST_H
#define PROJETO_SCHEDULE_REQUEST_H

#include "Student.h"
#include <set>

class Database;

class Request {
private:
    Student student;
    list<pair<UcClass*, UcClass*>> removeAdd; // Collection of pairs of iterators of UcClass to remove and UcClass to add
public:
    Request(Database &database, char option);
    void handleRequest();
};

#endif
