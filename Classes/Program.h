#ifndef PROJETO_SCHEDULE_PROGRAM_H
#define PROJETO_SCHEDULE_PROGRAM_H

#include <iostream>
#include <vector>
#include "Menu.h"
#include <string>
#include "Database.h"
#include "Student.h"
#include "Request.h"
using namespace std;

class Program {
public:
    Program();
    int getCurrentPage()const;
    void setCurrentPage(int newCurrentpage);

    Database getData(){
        return this->data;
    }
    void draw() const;
    void run();
    void menu();
    void createMenu();
    void printStudentSchedule()const;
    void printClassSchedule()const;
    void searchStudent()const;
    void searchByClass() const;
    void searchByUc() const;
    void searchByUcClass() const;
    void vacancies()const;
    void moreThan() const;
    void searchByYear() const;
    void searchByAdmissionYear()const;
    void wait() const;
    void requests(char option);
    bool validateStudentCode(int studentCode) ;
    template<typename type >
    bool getInput(type &input) const;



private:
    int currentMenuPage;
    vector<Menu> menus;
    Database data;
};


#endif //PROJETO_SCHEDULE_PROGRAM_H
