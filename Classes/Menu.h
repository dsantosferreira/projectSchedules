#ifndef PROJETO_SCHEDULE_MENU_H
#define PROJETO_SCHEDULE_MENU_H

#include <vector>
#include <fstream>
#include "UcClass.h"
#include "Student.h"

using namespace std;

class Menu {
public:
    Menu(string file_);
    Menu(vector<UcClass> ucClasses);
    Menu(list<UcClass> ucClasses);
    void draw()const;
private:
    vector<string> buttons;
};


#endif //PROJETO_SCHEDULE_MENU_H
