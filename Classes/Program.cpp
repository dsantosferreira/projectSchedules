#include "Program.h"
#include <limits>
/**
 * The constructor of Program
 */
Program::Program() {
    this->currentMenuPage=0;
    createMenu();
    this->data=Database();
    cout<<"Welcome to the Better Sigarra.\n";
}
/**
 * Auxiliary function of the constructor Program(),this function is used for creating the menus the program needs
 */
void Program::createMenu() {
    this->menus.push_back(Menu("../Menus/mainMenu.txt"));//Inatialize main menu

    this->menus.push_back(Menu("../Menus/searchSubMenu.txt"));// Inatialize search submenu
    this->menus.push_back(Menu("../Menus/scheduleSubMenu.txt"));// Inatialize schedule submenu

    this->menus.push_back(Menu("../Menus/requestsMenu"));
    //third menu (Search sub menu)

    // ... to be implemented after deciding what we are going to do...
}

//basic functions get and set
/**
 *This Function is used to get the current page of the menu we are in
 * @return The current Page Of the Menu
 */
int Program::getCurrentPage() const {
    return this->currentMenuPage;
}
/**
 *
 * @param newCurrentPage
 * This function receive the index of the new menu page we are in and set it as the current menu page
 */
void Program::setCurrentPage(int newCurrentPage)  {
    this->currentMenuPage=newCurrentPage;
}
/**
 * This function draw the current page of the menu we are in
 */
void Program::draw() const {
    this->menus[this->currentMenuPage].draw(); //draw the current menu
}
/**
 * This function is what is going to make our program run, it will draw the current menu pages get the inputs the user give and decide what
 * the program should do next
 */
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
                            vacancies();
                            break;
                        case '4':
                            this->currentMenuPage = 3;
                            break;
                        case '5':
                            this->currentMenuPage=3;//????
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
                            searchStudent();
                            break;
                        case '2':
                            searchByYear();
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
                            moreThan();
                            break;
                        case '7':
                            searchByAdmissionYear();
                            break;

                        case '8':
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

                case 3:


                    if (option[0] == '4')
                        this->currentMenuPage = 0;
                    else{
                        set<Student> students = data.getStudents();
                        vector<UcClass> ucClasses = data.getSchedule();
                        Request newRequest = Request(students, ucClasses, option[0]);
                        data.pushRequestToQueue(newRequest);
                    }
                    break;


                default:
                    cond = true;
                }


            }
        if (cond) cout << "\nInvalid input. Insert a valid option:"; //the input was invalid
        }

    }

/**
 * This function will draw the menu page corresponding to the schedule option and then it will ask the user to choose between
 */
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
        while(getInput(upCode))cout<<"Invalid input please insert a number:";
        list<UcClass>emptyList;
        set<Student> students= data.getStudents();
        auto itr=students.find(Student("Irrelevant",upCode,emptyList));
        if(itr!=students.end()){
            if(option=="1")itr->printGraphicalSchedule();
            else itr->printDiagramSchedule();
        }else {
            cout<<"Student not found\n";
        }

        wait();

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
    system("clear");
    cout<<"Insert the  year which the class belongs:";
    char year;
    while(getInput(year)|| (year-'1'>2 || year-'1'<0))cout<<"Invalid input please insert a number between 1-3:";
    system("clear");
    Menu secondaryMenu(data.getSchedule(),year);
    secondaryMenu.draw();
    vector<string> options=secondaryMenu.getButtons();
    cout<<"Insert the class:";
    int secondOption;
    while(getInput(secondOption)|| (year-'1'>2 || year-'1'<0))cout<<"Invalid input please insert a number between 1-3:";
    string  class_=options[secondOption-1];
    if(option=="1") data.printClassGraphicSchedule(class_);
    else data.printClassDiagramSchedule(class_);
    wait();
}

void Program::searchStudent() const {
    system("clear");
    cout<<"Insert Student code (up):";
    int upCode;
    while(getInput(upCode))cout<<"Invalid input please insert a number:";
    list<UcClass>emptyList;
    set<Student> students= data.getStudents();
    auto itr=students.find(Student("Irrelevant",upCode,emptyList));
    if(itr!=students.end()){
       itr->print();
    }else {
        cout<<"Student not found\n";
    }
    wait();
}
void Program::searchByClass() const {

    system("clear");
    cout<<"Insert the  year which the class belongs:";
    char year;
    while(getInput(year)|| (year-'1'>2 || year-'1'<0))cout<<"Invalid input please insert a number between 1-3:";
    system("clear");
    Menu menu(data.getSchedule(),year);
    menu.draw();
    vector<string> options=menu.getButtons();
    cout<<"Insert the class:";
    int option;
    cin>>option;
    this->data.searchByClass(options[option]);

    wait();

}
void Program::searchByUc() const {
    system("clear");
    Menu menu(this->data.getSchedule());
    menu.draw();
    vector<string> options=menu.getButtons();
    cout<<"Insert the Uc:";
    int option;
    while(getInput(option))cout<<"Invalid input please insert a number:";
    string ucCode=options[option-1];
    this->data.searchByUC(ucCode);
    wait();
}
void Program::searchByUcClass() const {
    system("clear");
    system("clear");
    Menu menu(this->data.getSchedule());
    menu.draw();
    vector<string> options=menu.getButtons();
    cout<<"Insert the uc:";
    int option;
    while(getInput(option))cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';

    string ucCode=options[option-1];
    Menu secondMenu(this->data.getSchedule(),options[option]);
    system("clear");
    secondMenu.draw();
    options=secondMenu.getButtons();
    cout<<"Insert the class:";
    cin>>option;
    while(cin.fail() || option>options.size()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';
        cin>>option;
    }
    string class_=options[option-1];
    list<Lecture> empty;
    this->data.searchByUcClass(UcClass(ucCode,class_,empty));

    wait();
}

void Program::vacancies() const{
    system("clear");
    cout<<"Insert the Uc code:";
    string ucCode;
    cin>>ucCode;
    system("clear");

    int index;
    index= data.findUc(ucCode);
    cout<<ucCode+":\n";
    while(this->data.getSchedule()[index].getUcCode()==ucCode){
       cout<<"Class:"+this->data.getSchedule()[index].getClassCode()+"|Capacity:"<<this->data.getSchedule()[index].getCapacity()<<
       "|Number of Students:"<<this->data.getSchedule()[index].getNumberOfStudents()<<"|Vacancies:"<<
       this->data.getSchedule()[index].getCapacity()-this->data.getSchedule()[index].getNumberOfStudents()<<endl;
        index++;
    }
    wait();

}
void Program::moreThan() const {
    system("clear");
    cout<<"Insert number of minimum Ucs Student should have:";
    int n;
    while(getInput(n))cout<<"Invalid input please insert a number:";
    if(!data.searchMoreThan(n)){
        cout<<"No student with more than "<<n<<" UCs was found\n";
    }
    wait();

}
void Program::searchByYear() const {
    system("clear");
    cout<<"Insert the year:";
    int year;
    while(getInput(year))cout<<"Invalid input please insert a number:";
    if(!data.searchByYear(year)) cout<<"No students found\n";
    wait();
}
void Program::searchByAdmissionYear() const {
    system("clear");
    cout<<"Insert the year:";
    int year;
    while(getInput(year))cout<<"Invalid input please insert a number:";
    if(!data.searchByYearAdmission(year)) cout<<"No students found\n";
    wait();

}

void Program::wait() const {
    cout<<"\nEnter anything to go back:";
    string wait;
    cin>>wait;
}

template<typename type>
bool Program::getInput(type &input) const {
    cin>>input;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    return false;
}
