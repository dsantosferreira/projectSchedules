#include "Program.h"
#include <limits>

Program::Program() {
    this->currentMenuPage=0;
    createMenu();
    this->data=Database();
}
void Program::createMenu() {
    this->menus.push_back(Menu("../Menus/mainMenu.txt"));//Inatialize main menu
    this->menus.push_back(Menu("../Menus/showSubMenu.txt"));// Inatialize show submenu
    this->menus.push_back(Menu("../Menus/requestsMenu"));
    //third menu (Search sub menu)
    // ... to be implemented after deciding what we are going to do...
}

//basic functions get and set
int Program::getCurrentPage() const {
    return this->currentMenuPage;
}

void Program::setCurrentPage(int newCurrentPage)  {
    this->currentMenuPage=newCurrentPage;
}

void Program::draw() const {
    this->menus[this->currentMenuPage].draw(); //draw the current menu
}

void Program:: run(){
    int option;
    while(this->currentMenuPage!=-1){
        menu();
// runs until quit option is selected
    }
}

void Program::menu() {
    draw(); //draw the current menu
    string option;
    bool cond = true;
    while (cond) {
        cin >> option;
        if (option.length() == 1 && isdigit(option[0])) {
            cond = false;
            switch (this->currentMenuPage) {
                case 0: // Is on main menu
                    switch (option[0]) {
                        case '1': //option show was selected, changing to submenu show
                            this->currentMenuPage = 1;
                            break;
                        case '2':
                            //use func or change currentMenuPage
                            break;
                        case '3':
                            //use func or change currentMenuPage
                            break;
                        case '4':
                            this->currentMenuPage = 2;
                            break;
                        case '5':
                            //use func or change currentMenuPage
                            break;
                        case '6':
                            this->currentMenuPage = -1; //-1 indicates that it wants to leave
                            break;
                        default:
                            cond = true;
                    }
                    break;
                case 1: //is on show sub-menu
                    switch (option[0]) {
                        case '1':
                            //use func or change currentMenuPage
                            break;
                        case '2':
                            //use func or change currentMenuPage
                            break;
                        case '3':
                            //use func or change currentMenuPage
                            break;
                        case '4':
                            //use func or change currentMenuPage
                            break;
                        case '5':
                            //use func or change currentMenuPage
                            break;
                        case '6':
                            this->currentMenuPage = 0;// Go back to main menu
                            break;
                        default:
                            cond = true;
                    }
                    break;
                case 2:
                    if (option[0] == 4)
                        this->currentMenuPage = 0;
                    else
                        data.addRequestToQueue(Request(data.getStudents(), data.getSchedule(), option[0]));
                default:
                    cond = true;
            }
        }
        if (cond) cout << "\nInvalid input. Insert a valid option:"; //the input was invalid
    }
}
void Program::printSchedule() const {
    cout<<"Introduce Students code: ";
    int up;
    cin>>up;
    list<UcClass>emptyList;
    set<Student> students= data.getStudents();
    auto itr=students.find(Student("Irrelevant",up,emptyList));
    if(itr==students.end()){
        cout<<"Student not found\n";
    }else {
        itr->printGraficalSchedule();
    }
}


