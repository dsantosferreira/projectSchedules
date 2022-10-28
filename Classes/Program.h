//
// Created by franciscocardoso on 26-10-2022.
//
#include <iostream>
#include <vector>
#include "Menu.h"
#include <string>
#include "Database.h"
#include "Student.h"
using namespace std;
#ifndef PROJETO_SCHEDULE_PROGRAM_H
#define PROJETO_SCHEDULE_PROGRAM_H


class Program {
public:
    Program();
    int getCurrentPage()const;
    void setCurrentPage(int newCurrentpage);
    void draw() const;
    void run();
    void menu();
    void createMenu();
    void printSchedule()const;


private:
    int currentMenuPage;
    vector<Menu> menus;
    Database data;
};


#endif //PROJETO_SCHEDULE_PROGRAM_H
