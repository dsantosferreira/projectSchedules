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
    void handleRequestOption(char option);
    void showStudents() const;
    void showUcs() const;
    void showClasses() const;
    void customSorts(vector<Student> &search) const;
    template<typename type >
    bool getInput(type &input) const;
    void showSearch(vector<Student> search) const;

private:
    bool validateStudentCode(int studentCode);
    int currentMenuPage;
    vector<Menu> menus;
    Database data;
};


#endif
