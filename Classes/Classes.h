//
// Created by franciscocardoso on 18-10-2022.
//
#include<string>
#include "Lecture.h"
#include <list>
using namespace std;
#ifndef PROJETO_SCHEDULE_CLASSES_H
#define PROJETO_SCHEDULE_CLASSES_H


class Classes {
public:
    Classes(string classcode_, list<Lecture> lectures );
    string getClassCode()const;
    list<Lecture> getLectures() const;
    void print()const;
private:
    string classCode;// tentar dividir em duas uma para o ano e uma para a turma
    list<Lecture> lectures;

};


#endif //PROJETO_SCHEDULE_CLASSES_H
