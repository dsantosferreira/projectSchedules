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


    int getNumberUcClasses() const;
    void searchByUC(std::string ucCode);
    /*bool*/void searchByYear(int year) const;
    /*bool*/void searchByYearAdmission(int year) const;
    int findUc(string ucCode);
    void pushRequestToQueue(Request request);
    Request popRequestFromQueue();


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
