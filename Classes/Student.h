#include <string>
#include<list>
#include "UcClass.h"
using namespace std;
#ifndef PROJETO_SCHEDULE_STUDENT_H
#define PROJETO_SCHEDULE_STUDENT_H

class Student {
public:
    Student();
    Student(string studentName_, int studentCode_, list<UcClass> ucClasses_);
    string getStudentname() const;
    void setStudentName(string studentName_);
    void setStudentCode(int studentCode_);
    void setUcClasses(list<UcClass> ucClasses_);
    void addUcClass(UcClass aUcClass);
    string getStudentName() const;
    int getStudentCode() const;
    list<UcClass> getUcClasses() const;
    void print();
    string classOfUc(string ucCode_)const;
    string ucOfClass(string classCode_ ) const;
    bool hasClass(string classCode_)const;
    bool hasUc(string ucCode_)const;
    bool operator< (const Student & student) const;

private:
    string studentName;
    int studentCode;
    list<UcClass> ucClasses;
};


#endif
