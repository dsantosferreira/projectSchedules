#include "Student.h"
#include "UcClass.h"
#include <list>
#include <set>
using namespace std;

#ifndef PROJETO_SCHEDULE_DATABASE_H
#define PROJETO_SCHEDULE_DATABASE_H


class dataBase {
public:
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
    //set<Unkownstructer> IDK; set para varias ordenações de estudante
    set<Student> students;
    list<UcClass> schedule;
};


#endif //PROJETO_SCHEDULE_DATABASE_H
