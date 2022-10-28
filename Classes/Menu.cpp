//
// Created by franciscocardoso on 26-10-2022.
//

#include "Menu.h"
#include <stdlib.h>


Menu::Menu(string file_) {
    ifstream file(file_);
    for(string button; getline(file,button);){
        this->buttons.push_back(button);
    }
}

/**
 * d snds
 *
 **/
void Menu::draw() const {
    system("clear");
    string display;
    display =" ________________________________________ \n"
             "|<<<<<<<<<<<<<<<<< Menu >>>>>>>>>>>>>>>>>|\n"
             "|----------------------------------------|\n";

    for(int i=0; i<this->buttons.size();i++){
        display+="| ["+to_string(i+1)+"] "+this->buttons[i];
        for(int j=0; j<(35-this->buttons[i].length());j++) display+=" "; //adding spaces to format the menu
        display+="|\n";
    }
    display+="|________________________________________|\n"
              ;
    cout<<display<<endl;
    cout<<"Chooce a option: ";
}
