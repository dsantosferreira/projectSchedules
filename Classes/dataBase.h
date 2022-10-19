//
// Created by franciscocardoso on 18-10-2022.
//
#include "Student.h"
#include "Uc.h"
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
    list<Uc> schedule;



};


#endif //PROJETO_SCHEDULE_DATABASE_H
