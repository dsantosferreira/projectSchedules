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
#include <limits>

class Request {
public:
    Request(){};
    Request(Student student,list<pair<UcClass*,UcClass*>> pairs);
    void print(){
        this->student.print();
        for(pair<UcClass,UcClass>p:removeAdd){
            cout<<p.first.getUcCode() +'-'+p.first.getClassCode()+'\n'+p.second.getUcCode()+'-'+p.second.getClassCode()+'\n';
        }

    }
    list<pair<UcClass*,UcClass*>> getPairs() const;
    Student getStudent()const;
    bool handleRequest(set<Student>* students, vector<UcClass>* ucClasses);
    bool checkUnbalance(vector<UcClass> ucClasses, UcClass ucClass, int type);
    int findUc(string ucCode, vector<UcClass> ucClasses);

private:
    Student student;
    list<pair<UcClass*,UcClass*>> removeAdd;


};


#endif //PROJETO_SCHEDULE_REQUEST_H
