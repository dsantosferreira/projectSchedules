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
    Menu(list<UcClass*> ucClasses);
    Menu(vector<UcClass>ucClasses,string ucCode);
    Menu(vector<UcClass>ucClasses,char year);
    vector<string> getButtons() const;
    void setButtons(vector<string> buttons_);
    void draw()const;
private:
    vector<string> buttons;
};


#endif //PROJETO_SCHEDULE_MENU_H
