#include "Menu.h"
#include <stdlib.h>
#include <set>

/**Functionality: Creating a menu with options taken from a file
 *
 * Description: This function is Constructor of the Menu using a file to initialize it.The function will receive a file as a parameter
 * and will go through every line of the file one by one, each line will be a button, so the function will give push_back of the line to
 * its attribute buttons.
 *
 * @param file_ a file with all the options of the menu
 */
Menu::Menu(string file_) {
    ifstream file(file_);
    for(string button; getline(file,button);){
        this->buttons.push_back(button);
    }
}
/**Functionality: Creating a menu with Ucs as options
 *
 * Description:This function is Constructor of the Menu using a vector of UcClasses to initialize it.This function will receive a vector of
 * UcClasses as parameter and will go through every UcClass getting all uc code adding them to the attribute of the Menu buttons ,the function
 * will verify if the uc code is already in buttons and will only add them to the buttons if it was not already added.
 *
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
/**Functionality: Creating a menu with classes of a Uc as options
 * Description: This function is a Constructor of the Menu using a vector of UcClasses and a Uc code. This function will receive as parameters
 * a vector of UcClasses and a string which will have a UC code, the function will find all the classes from that UC and add them to the Menu
 * attribute buttons
 *
 * @param ucClasses  a vector with all the UcClasses
 * @param ucCode  a string with a Uc code
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
/**Functionality:Creating a menu with classes of a year as options
 *
 * Description: This function is a Constructor of the Menu using a vector of UcClasses and a year. This function will receive as parameters
 * a vector of UcClasses and a char which will represent a year, the function will find all the classes belonging to that year and adding them
 * to the attribute of the Menu buttons
 *
 * @param ucClasses a vector of UcClasees
 * @param year a char representing a year
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
/**Functionality: Creating a menu with pairs of UCs and Classes as options
 *
 * Descriptions: This function is a Constructor of the Menu using a list of UcClasses.This function will receive as parameters a list of UcClasses
 * and will go through all the UcClasses adding the string with the UcCode and the classCode to the buttons
 *
 * @param ucClasses list of UcClasses
 */
Menu::Menu(list<UcClass> ucClasses) {
    for (UcClass ucClass : ucClasses) {
        this->buttons.push_back(ucClass.getUcCode() + ' ' + ucClass.getClassCode());
    }
}
/**Functionality: Getter of the Menu attribute buttons
 *
 * @return vector<strings> buttons
 */
vector<string> Menu::getButtons() const {
    return buttons;
}
/**Functionality: Setter for the buttons
 * Description: Receives a vector of string as a parameter and replaces the current buttons of the new ones
 *
 * @param  buttons_ a vector of strings
 */
void Menu::setButtons(vector<std::string> buttons_) {
    this->buttons = buttons_;
}
/**Functionality:Draw a menu
 *
 * Description:This function will get the attribute of the Menu buttons and will go through all of them printing them in a pleasant way
 * it will also ask the user for a input however it will not handle the user input.
 *
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
