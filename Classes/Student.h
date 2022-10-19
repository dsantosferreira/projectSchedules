//
// Created by franciscocardoso on 18-10-2022.
//
#include <string>
#include<list>
using namespace std;
#ifndef PROJETO_SCHEDULE_STUDENT_H
#define PROJETO_SCHEDULE_STUDENT_H


class Student {
public:
    Student();
    Student(string name_, int up_, list<pair<string,string>> l);
    string getName()const;
    int getUp() const;
    list<pair<string,string>> getClassOfUc() const;
    void print();
    bool operator< (const Student & student); // para o set conseguir comparar os estudantes;
private:
    string name;
    int up;
    list<pair<string,string>> classOfUc;// tentar transformar em int int
};


#endif //PROJETO_SCHEDULE_STUDENT_H
