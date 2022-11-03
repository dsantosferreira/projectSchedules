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
    int getNumberUcClasses() const;
    void searchByUC(std::string ucCode);
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
    //set<Unkownstructer> IDK; set para varias ordenações de estudante
    set<Student> students;
    vector<UcClass> schedule;
    queue<Request> mainQueue;
    queue<Request> archive;
};


#endif //PROJETO_SCHEDULE_DATABASE_H
