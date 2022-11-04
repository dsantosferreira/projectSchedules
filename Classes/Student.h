#ifndef PROJETO_SCHEDULE_STUDENT_H
#define PROJETO_SCHEDULE_STUDENT_H

#include <string>
#include <list>
#include "UcClass.h"
#include <vector>

using namespace std;

class Student {
public:
    Student();
    Student(const Student &student);
    Student(string studentName_, int studentCode_, list<UcClass> ucClasses_);
    list<UcClass> getUcClasses() const;
    void setStudentName(string studentName_);
    void setStudentCode(int studentCode_);
    void setUcClasses(list<UcClass> ucClasses_);
    void addUcClass(UcClass* aUcClass, int pos);
    void removeUcClass(UcClass aUcClass);
    string getStudentName() const;
    int getStudentCode() const;
    string classOfUc(string ucCode_)const;
    string ucOfClass(string classCode_ ) const;
    bool hasClass(string classCode_)const;
    bool hasUc(string ucCode_)const;
    bool operator< (const Student & student) const; // para o set conseguir comparar os estudantes;
    void printGraphicalSchedule() const;
    void printDiagramSchedule() const;
    bool hasUcClass(UcClass ucClass_) const;
    void print()const;

private:
    string studentName;
    int studentCode;
    list<UcClass> ucClasses;
};


#endif
