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
    bool operator<(const Student student) const; // para o set conseguir comparar os estudantes;
private:
    string studentName;
    int studentCode;
    list<UcClass> ucClasses;// tentar transformar em int int
};


#endif //PROJETO_SCHEDULE_STUDENT_H
