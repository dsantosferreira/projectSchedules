#include "Student.h"
#include "UcClass.h"
#include <vector>
#include <set>
using namespace std;

#ifndef PROJETO_SCHEDULE_DATABASE_H
#define PROJETO_SCHEDULE_DATABASE_H


class Database {
public:
    Database();
    set<Student> getStudents() const;
    vector<UcClass> getSchedule() const;

    /* Funcões para listagens
     * Funcões para pesquisa
     * Funçoes dos pedidos
     * Funcões de inicialização de estruturas
     * funcões gerais
     * Funções de leitura
     * Funcões print
     * Funções de escrita em ficheiros
     * */
private:
    void readUcClasses();
    void readUcClassesFile();
    void readStudentClassesFile();
    UcClass* findUcClass(string ucCode, string classCode);
    //set<Unkownstructer> IDK; set para varias ordenações de estudante
    set<Student> students;
    vector<UcClass> schedule;
};


#endif //PROJETO_SCHEDULE_DATABASE_H
