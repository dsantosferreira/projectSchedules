//
// Created by franciscocardoso on 26-10-2022.
//

#include "Program.h"

Program::Program() {
    this->currentMenuPage=0;
    createMenu();
    this->data=Database();
}
void Program::createMenu() {
    this->menus.push_back(Menu("../Menus/mainMenu.txt"));//Inatialize main menu
    this->menus.push_back(Menu("../Menus/searchSubMenu.txt"));// Inatialize search submenu
    this->menus.push_back(Menu("../Menus/scheduleSubMenu.txt"));// Inatialize schedule submenu
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
                            this->currentMenuPage=2;

                            break;
                        case '3':
                            //use func or change currentMenuPage
                            break;
                        case '4':
                            //use func or change currentMenuPage
                            break;

                        case '5':
                            this->currentMenuPage = -1; //-1 indicates that it wants to leave
                            break;
                        default:
                            cond = true;
                    }
                    break;
                case 1: //is on show sub-menu
                    switch (option[0]) {
                        case '1':
                            searchStudent();
                            break;
                        case '2':

                            break;
                        case '3':
                           searchByUc();
                            break;
                        case '4':
                            searchByClass();
                            break;
                        case '5':
                            searchByUcClass();
                            break;

                        case '6':
                            this->currentMenuPage = 0;// Go back to main menu
                            break;
                        default:
                            cond = true;
                    }
                    break;
                case 2:
                    switch (option[0]) {
                        case '1':
                            printClassSchedule();
                            break;
                        case '2':
                            printStudentSchedule();
                            break;
                        case '3':
                            this->currentMenuPage=0;
                            break;
                        default:
                            cond=true;
                    }
                    break;

                default:
                    cond = true;
            }
        }
        if (cond) cout << "\nInvalid intput. Insert a valid option:"; //the input was invalid
    }
}
void Program::printStudentSchedule() const {
    system("clear");
    Menu menu("../Menus/scheduleSubMenu2.txt");
    menu.draw();

    string option;
    cin >>option;
    while( option!="1" and option!="2"){
        cout<<"Invalid input.Please enter a valid option: ";
        cin>>option;
    }
    cout<<"Introduce Students code: ";
    int upCode;
    cin>>upCode;
    list<UcClass>emptyList;
    set<Student> students= data.getStudents();
    auto itr=students.find(Student("Irrelevant",upCode,emptyList));
    if(itr!=students.end()){
        if(option=="1")itr->printGraphicalSchedule();
        else itr->printDiagramSchedule();
    }else {
        cout<<"Student not found\n";
    }
    cout<< "\n\nEnter anything to go back:";
    string wait;
    cin>>wait;
}

void Program::printClassSchedule() const {
    system("clear");
    Menu menu("../Menus/scheduleSubMenu2.txt");
    menu.draw();

    string option;
    cin >>option;
    while( option!="1" and option!="2"){
        cout<<"Invalid input.Please enter a valid option: ";
        cin>>option;
    }
    cout<<"Insert the class:";
    string class_;
    cin>>class_;
    if(option=="1") data.printClassGraphicSchedule(class_);
    else data.printClassDiagramSchedule(class_);
    cout<< "\n\nEnter anything to go back:";
    string wait;
    cin>>wait;
}

void Program::searchStudent() const {
    system("clear");
    cout<<"Insert Student code (up):";
    int upCode;
    cin>>upCode;
    list<UcClass>emptyList;
    set<Student> students= data.getStudents();
    auto itr=students.find(Student("Irrelevant",upCode,emptyList));
    if(itr!=students.end()){
       itr->print();
    }else {
        cout<<"Student not found\n";
    }
    cout<< "Enter anything to go back:";
    string wait;
    cin>>wait;

}
void Program::searchByClass() const {
    system("clear");
    cout<<"Insert the class:";
    string class_;
    cin>>class_;
    this->data.searchByClass(class_);
    cout<< "Enter anything to go back:";
    string wait;
    cin>>wait;
}
void Program::searchByUc() const {
    system("clear");
    cout<<"Insert the Uc:";
    string uc_;
    cin>>uc_;
    this->data.searchByUC(uc_);
    cout<<"Enter anything to go back:";
    string wait;
    cin>>wait;
}
void Program::searchByUcClass() const {
    system("clear");
    cout<<"Insert the uc:";
    string uc_;
    cin>>uc_;
    cout<< "Insert the class:";
    string class_;
    cin>>class_;
    list<Lecture> empty;
    this->data.searchByUcClass(UcClass(uc_,class_,empty));
    cout<<"Enter anything to go back:";
    string wait;
    cin>>wait;
}


