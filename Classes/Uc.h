//
// Created by franciscocardoso on 18-10-2022.
//
#include <string>
#include "Classes.h"
#include<list>
using namespace std;
#ifndef PROJETO_SCHEDULE_UC_H
#define PROJETO_SCHEDULE_UC_H

class Uc {
public:
    Uc(string uc_, list<Classes> l);
    string getUc()const;
    list<Classes> getClasses();
    void print() const;
private:

    string uc;
    list<Classes> classes;
};


#endif //PROJETO_SCHEDULE_UC_H
