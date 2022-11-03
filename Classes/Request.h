#ifndef PROJETO_SCHEDULE_REQUEST_H
#define PROJETO_SCHEDULE_REQUEST_H

#include "Student.h"
#include <set>

class Request {
private:
    Student student;
    list<pair<UcClass*, UcClass*>> removeAdd; // Collection of pairs of iterators of UcClass to remove and UcClass to add
    int findUc(string ucCode, vector<UcClass> ucClasses);
public:
    Request(set<Student> &students, vector<UcClass> &ucClasses, char option);
    list<pair<UcClass*, UcClass*>> getPairs() const;
    void handleRequest();
};

#endif
