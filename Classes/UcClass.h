#include <string>
#include "Lecture.h"
#include <list>
using namespace std;
#ifndef PROJETO_SCHEDULE_UCCLASS_H
#define PROJETO_SCHEDULE_UCCLASS_H

class UcClass {
public:
    UcClass(string ucCode_, string classCode_, list<Lecture> lectures_);
    string getUcCode() const;
    string getClassCode() const;
    list<Lecture> getLectures() const;
    //void print() const;
private:
    string ucCode;
    string classCode;
    list<Lecture> lectures;
};

#endif
