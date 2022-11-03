#include "Menu.h"
#include <stdlib.h>
#include <set>

Menu::Menu(string file_) {
    ifstream file(file_);
    for(string button; getline(file,button);){
        this->buttons.push_back(button);
    }
}

Menu::Menu(vector<UcClass> ucClasses) {
    set<string> alreadySeen;
    for (UcClass ucClass : ucClasses) {
        string ucCode = ucClass.getUcCode();
        if (alreadySeen.find(ucCode) == alreadySeen.end()) {
            alreadySeen.insert(ucCode);
            this->buttons.push_back(ucCode);
        }
    }
}
Menu::Menu(vector<UcClass>ucClasses,string ucCode){
    int begin=0, end= ucClasses.size()-1;
    int middle;
    while(begin<end){
        middle=begin+(end-begin)/2;
        if(ucClasses[middle].getUcCode()>=ucCode) end=middle;
        else begin=middle+1;
    }
    while(ucClasses[begin].getUcCode()==ucCode){
        this->buttons.push_back(ucClasses[begin].getClassCode());
        begin++;
    }

}

Menu::Menu(vector<UcClass>ucClasses,char year){
    set<string> alreadySeen;
    int begin=0, end= ucClasses.size()-1;
    int middle;
    while(begin<end){
        middle=begin+(end-begin)/2;
        if(ucClasses[middle].getClassCode()[0]>=year) end=middle;
        else begin=middle+1;
    }
    while(ucClasses[begin].getClassCode()[0]==year){
        if (alreadySeen.find(ucClasses[begin].getClassCode()) == alreadySeen.end()) {
            alreadySeen.insert(ucClasses[begin].getClassCode());
            this->buttons.push_back(ucClasses[begin].getClassCode());

        }
        begin++;
    }

}

Menu::Menu(list<UcClass> ucClasses) {
    for (UcClass ucClass : ucClasses) {
        this->buttons.push_back(ucClass.getUcCode() + ' ' + ucClass.getClassCode());
    }
}

vector<string> Menu::getButtons() const {
    return buttons;
}

void Menu::setButtons(vector<std::string> buttons_) {
    this->buttons = buttons_;
}

void Menu::draw() const {
    system("clear");
    string display;
    display =" _____________________________________________ \n"
             "|<<<<<<<<<<<<<<<<<>  Menu  <>>>>>>>>>>>>>>>>>>|\n"
             "|---------------------------------------------|\n";

    for(int i=0; i<this->buttons.size();i++){
        display+="| ["+to_string(i+1)+"] "+this->buttons[i];
        for(int j=0; j<(39-this->buttons[i].length());j++) display+=" "; //adding spaces to format the menu
        if(i<9) display+=' ';
        display+="|\n";
    }
    display+="|_____________________________________________|\n";
    cout<<display<<endl;
    cout<<"Choose an option: ";
}
