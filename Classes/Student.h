//
// Created by franciscocardoso on 18-10-2022.
//
#include <string>
#include<list>
#include "UcClass.h"
using namespace std;
#ifndef PROJETO_SCHEDULE_STUDENT_H
#define PROJETO_SCHEDULE_STUDENT_H

class Student {
public:

    Student(string studentName_, int studentCode_, list<UcClass> ucClasses_);
    Student();
    string getStudentname()const;
    int getstudentCode() const;
    list<UcClass> getUcClasses() const;
    string classOfUc(string ucCode_)const;
    string ucOfClass(string classCode_ ) const;
    bool hasClass(string classCode_)const;
    bool hasUc(string ucCode_)const;
    //void print();
    bool operator< (const Student & student)const; // para o set conseguir comparar os estudantes;
private:
    string studentName;
    int studentCode;
    list<UcClass> ucClasses;// tentar transformar em int int
};


#endif //PROJETO_SCHEDULE_STUDENT_H
