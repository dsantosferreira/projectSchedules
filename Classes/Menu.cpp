#include "Menu.h"
#include <stdlib.h>
#include <set>

/**
 * Builds the buttons of the menu based on the file that is given \n
 * Complexity: Linear in the number of lines of the file
 * @brief Constructor from a file
 * @param file_ - a file with all the options of the menu
 */
Menu::Menu(string file_) {
    ifstream file(file_);
    for(string button; getline(file,button);){
        this->buttons.push_back(button);
    }
}

/**
 * Complexity: linear in the total number of classes
 * @brief Creates a menu of all the curricular units
 * @param ucClasses a vector with all the UcClasses
 */
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
/**
 * Complexity: O(log(n) + p) being n the number of classes and p the number of classes of the curricular unit n
 * @brief Creates a menu of all the classes of a particular curricular unit
 * @param ucClasses - a vector with all the UcClasses
 * @param ucCode - a string with a ucCode
 */
Menu::Menu(vector<UcClass>ucClasses,string ucCode){
    int begin=0, end= ucClasses.size()-1;
    int middle;
    while(begin<end){
        middle=begin+(end-begin)/2;
        if(ucClasses[middle].getUcCode()>=ucCode) end=middle;
        else begin=middle+1;
    }
    while(begin<ucClasses.size() and  ucClasses[begin].getUcCode()==ucCode){
        this->buttons.push_back(ucClasses[begin].getClassCode());
        begin++;
    }

}
/**
 * Complexity: O(log(n) + p) being n the number of classes and p the number of classes from a certain year
 * @brief Creates a menu with all the classes from a certain year
 * @param ucClasses a vector of classes
 * @param year a char representing an year
 */
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
/**
 * Complexity: linear in the number of classes of a student
 * @brief Creates a menu with all the classes of a student
 * @param ucClasses list of UcClasses
 */
Menu::Menu(list<UcClass> ucClasses) {
    for (UcClass ucClass : ucClasses) {
        this->buttons.push_back(ucClass.getUcCode() + ' ' + ucClass.getClassCode());
    }
}

/**
 * @brief Getter of menu's buttons
 * @return list of all the buttons
 */
vector<string> Menu::getButtons() const {
    return buttons;
}

/**
 * @brief Setter for the menu's buttons
 * @param  buttons_ - a vector of strings
 */
void Menu::setButtons(vector<std::string> buttons_) {
    this->buttons = buttons_;
}

/**
 * Complexity: Linear in the number of buttons
 * @brief Draws a menu
 */
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

}
