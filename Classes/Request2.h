#ifndef PROJETO_SCHEDULE_REQUEST2_H
#define PROJETO_SCHEDULE_REQUEST2_H

#include "Student.h"
#include <set>
#include <vector>

class Request2 {
private:

    Student student;
    list<pair<UcClass, UcClass*>> removeAdd; // Collection of pairs of iterators of UcClass to remove and UcClass to add
    int findUc(string ucCode, vector<UcClass> ucClasses);
    bool checkRequestInput(vector<string> buttons_, string option);
public:
    Request2();
    Request2(const Request2 &request);
    Request2(Student student_, list<pair<UcClass, UcClass*>> pairs);
    Request2(set<Student>* students, vector<UcClass>* ucClasses, char option);
    Student getStudent() const;
    list<pair<UcClass, UcClass*>> getPairs() const;
    list<pair<bool, bool>> handleRequest(set<Student>* students,vector<UcClass>ucClasses);
    bool checkUnbalance(vector<UcClass> ucClasses,UcClass ucClass, int type);
};

#endif
