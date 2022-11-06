#ifndef PROJETO_SCHEDULE_UCCLASS_H
#define PROJETO_SCHEDULE_UCCLASS_H

#include <string>
#include "Lecture.h"
#include <list>

using namespace std;

class UcClass {
public:
    UcClass();
    UcClass(string ucCode_, string classCode_, list<Lecture> lectures_);
    string getUcCode() const;
    string getClassCode() const;
    list<Lecture> getLectures() const;
    int getNumberOfStudents() const;
    int getCapacity() const;
    void setNumberOfStudents(int newNumberOfStudents);
    void setCapacity(int newCapacity);
    void addALecture(Lecture aLecture);
    bool operator<(const UcClass secondUcClass) const;
    void print() const;
    void printUcCode() const;
    void printClassCode() const;
private:
    string ucCode;
    string classCode;
    list<Lecture> lectures;
    int capacity;
    int numberOfStudents;

};

#endif
