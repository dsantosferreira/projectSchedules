//
// Created by franciscocardoso on 26-10-2022.
//

#ifndef PROJETO_SCHEDULE_MENU_H
#define PROJETO_SCHEDULE_MENU_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <list>
using namespace std;

class Menu {
public:
    Menu(string file_);
    void draw()const;
private:
    vector<string> buttons;
};


#endif //PROJETO_SCHEDULE_MENU_H
