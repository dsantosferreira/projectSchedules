#ifndef PROJETO_SCHEDULE_DATABASE_H
#define PROJETO_SCHEDULE_DATABASE_H

#include "Student.h"
#include "UcClass.h"
#include "Request.h"
#include <vector>
#include <set>
#include <queue>

using namespace std;


class Database {
public:
    Database();
    set<Student> getStudents() const;
    vector<UcClass> getSchedule() const;
    bool searchByUC(std::string ucCode)const;
    bool searchByUcClass(UcClass ucClass)const;
    bool searchByClass(string class_) const;
    bool searchStudent(int upCode)const;
    void printClassDiagramSchedule(string classCode_)const;
    void printClassGraphicSchedule(string classCode_)const;
    bool searchMoreThan(int n) const;
    bool searchByYear(int year)const;
    bool searchByYearAdmission(int year) const;


    int getNumberUcClasses() const;

    int findUc(string ucCode)const;
    void addRequestToQueue(Request request);


    /** Funcões para listagens
     * Funcões para pesquisa
     * Funçoes dos pedidos
     * Funcões de inicialização de estruturas
     * funcões gerais
     * Funções de leitura
     * Funcões print
     * Funções de escrita em ficheiros
      */
private:
    void readUcClasses();
    void readUcClassesFile();
    void readStudentClassesFile();
    UcClass* findUcClass(string ucCode, string classCode);
    set<Student> students;
    vector<UcClass> schedule;
    queue<Request> mainQueue;
    queue<Request> archive;
};


#endif //PROJETO_SCHEDULE_DATABASE_H
