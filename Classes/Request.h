//
// Created by franciscocardoso on 04-11-2022.
//

#ifndef PROJETO_SCHEDULE_REQUEST_H
#define PROJETO_SCHEDULE_REQUEST_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Student.h"
#include "UcClass.h"
#include <set>

class Request {
public:
    Request(set<Student>students,pair<UcClass,UcClass>,vector<UcClass>ucClasses);
private:
    Student student;
    list<pair<UcClass,UcClass>> pairs;


};


#endif //PROJETO_SCHEDULE_REQUEST_H
