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
    Student();
    Student(string studentName_, int studentCode_, list<UcClass> ucClasses_);
    string getStudentname()const;
    int getstudentCode() const;
    list<UcClass> getUcClasses() const;
    void print();
    bool operator< (const Student & student); // para o set conseguir comparar os estudantes;
private:
    string studentName;
    int studentCode;
    list<UcClass> ucClasses;// tentar transformar em int int
};


#endif //PROJETO_SCHEDULE_STUDENT_H
