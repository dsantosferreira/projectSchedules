#include "Student.h"

#ifndef PROJETO_SCHEDULE_REQUEST_H
#define PROJETO_SCHEDULE_REQUEST_H

class Request {
private:
    Student student;
    list<pair<list<UcClass>::iterator , UcClass*>> removeAdd; // Collection of pairs of iterators of UcClass to remove and UcClass to add
public:
    Request(set<Student> students, vector<UcClass> ucClasses, char option);
    void handleRequest();
};

#endif
