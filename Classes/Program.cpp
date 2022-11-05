#include "Program.h"
#include <limits>
/**Functionality: The constructor of Program
 *
 * Description: It will define the current menu page at 0, create all the menus and initialize the database
 *
 */
Program::Program() {
    this->currentMenuPage=0;
    createMenu();
    this->data=Database();
    cout<<"Welcome to the Better Sigarra.\n";
}



/**Functionality: Initialize all the menus
 * Auxiliary function of the constructor Program(),this function is used for creating the menus the program needs,
 * it does that by initializing it and then pushing it to the attribute of the Program menus which is a vector of menus
 */
void Program::createMenu() {
    this->menus.push_back(Menu("../Menus/mainMenu.txt"));//Initialize main menu
    this->menus.push_back(Menu("../Menus/searchSubMenu.txt"));// Initialize search submenu
    this->menus.push_back(Menu("../Menus/scheduleSubMenu.txt"));// Initialize schedule submenu
    this->menus.push_back(Menu("../Menus/requestsMenu"));

}

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

/**Functionality: draw the current page of the menu we are in
 * Description: Take the attribute menus get the current menu and use the method draw of the menu to draw it
 */
void Program::draw() const {
    this->menus[this->currentMenuPage].draw(); //draw the current menu
}

/**Functionality: Run the program
 *
 * Description: Uses a while to stop the program from finishing without the users permission, the while will ne broke when the Program attribute
 * currentMenuPage is equal to -1
 */
void Program:: run(){
    while(this->currentMenuPage!=-1){
        menu();
// runs until quit option is selected
    }
    if(data.getMainRequest().size()>0 || data.getArchiveRequest().size()>0){
        cout<< "Do you want to save the stored requests?[y/n]: ";
        char answer;
        while(getInput(answer) || (tolower(answer)!='y' && tolower(answer)!='n'))cout<<"Invalid input please enter y(yes) or n(no)";
        if(tolower(answer)=='y'){
            data.handleRequests();
        }
    }
    data.updateStudents();
    data.updateArchive();

}

/**Functionality: Makes the Program work, calls the functions and deals with the majority of the inputs and with the current menu page.
 *
 * Description: This function is what is going to make our program work, it will draw the current menu pages get the inputs the user gives
 * (giving a warning if the input is invalid) and decides what the program should do next,it will do that by calling other function from the
 * Program with the help pf a switch.
 */
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
                            data.handleRequests();
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
                {
                    handleRequestOption(option[0]);
                    break;
                }
                default:
                    cond = true;
                }
            }
        if (cond) cout << "\nInvalid input. Insert a valid option: "; //the input was invalid
    }
}

/**Functionality: Print the schedule of the Student and make it more user friendly.
 *
 * Description: This function will  make the program be more user friendly it will draw the menu page corresponding to the schedule option and then it will ask
 * the user to choose between printing a graphical or a diagram menu then it will ask for the Students up code and then will call the functions to
 * print the menu, giving a warning if no Student was found, the function will wait until the user has finished seeing the menu to finish its execution
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

/**Functionality: Print class Schedule and make it more user friendly.
 *
 * Description: This function will  make the program be more user friendly, it will draw the menu page corresponding to the schedule option and then it will ask
 * the user to choose between printing a graphical or a diagram menu, then it will ask the class's year, after that it  will display a menu with all
 * the classes from that year and ask you to choose one(giving a warning if the option is invalid) then it will call the functions to print the menu,
 * the function will wait until the user has finished seeing the menu to finish its execution.
 */
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
    cout<<"Insert the class's year";
    char year;
    while(getInput(year)|| (year-'1'>2 || year-'1'<0))cout<<"Invalid input please insert a number between 1-3:";
    system("clear");
    Menu secondaryMenu(data.getSchedule(),year);
    secondaryMenu.draw();
    vector<string> options=secondaryMenu.getButtons();
    cout<<"Insert the class:";
    int secondOption;
    while(getInput(secondOption)|| secondOption>options.size() || secondOption<1)cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';
    string  class_=options[secondOption-1];
    if(option=="1") data.printClassGraphicSchedule(class_);
    else data.printClassDiagramSchedule(class_);
    wait();
}

/**Functionality: Search Student and make it more user friendly
 *
 * Description:This function will  make the program more user friendly,it will start by clearing the terminal window,then it will ask the user to insert the
 * up code of a student(giving a warning if the input is invalid) and the will search the Student and printing his name and his up(if student was not
 * found then the function will give a warning)the function will wait until the user as finished seeing the Student to finish its execution
 */
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

/**Functionality: Search Students in a Class and make it more user friendly
 *
 * Description: This function will  make the program more user friendly,it will start by clearing the terminal window,it will ask the user the class's year and then
 * it will display a menu with all the classes from that year, after that it will ask the user to choose a class(giving a warning if the input is invalid)
 * and then it will search for all the Students belonging to that class,the function will wait until the user as finished seeing the Student to finish its
 * execution.
 */
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
    while(getInput(option)|| option>options.size() || option<1)cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';
    this->data.searchByClass(options[option-1]);

    wait();

}

/**Function: Search Student in a UC and make it more user friendly
 *
 * Description: This function will make the program more user friendly,it will start by clearing the terminal window,following that it will display a menu with all
 * the Ucs,after that it will ask the user to choose one Uc(giving a warning if the input is invalid) and then it will search for all the students
 * belonging to that Uc, displaying them in the process,the function will wait until the user as finished seeing the Student to finish its execution.
 */
void Program::searchByUc() const {
    system("clear");
    Menu menu(this->data.getSchedule());
    menu.draw();
    vector<string> options=menu.getButtons();
    cout<<"Insert the Uc:";
    int option;
    while(getInput(option)|| option>options.size() || option<1)cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';
    string ucCode=options[option-1];
    this->data.searchByUC(ucCode);
    wait();
}

/**Function: Search Students belonging to a class on an UC.
 *
 * Description: This function will make the program more user friendly,it will start by clearing the terminal window,then it will display a menu with all the UCs,
 * following that it will ask the user to choose one(giving a warning if the input is invalid) and after that it will display another menu this time
 * with all the classes of the chosen Uc,this time will ask the user to choose a class(giving aa warning if the input is invalid) and then it will
 * search for all the Students belonging to that class for that UC, displaying them in the process,the function will wait until the user as finished
 * seeing the Student to finish its execution.
 */
void Program::searchByUcClass() const {
    system("clear");
    Menu menu(this->data.getSchedule());
    menu.draw();
    vector<string> options=menu.getButtons();
    cout<<"Insert the uc:";
    int option;
    while(getInput(option)|| option>options.size() || option<1)cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';

    string ucCode=options[option-1];
    Menu secondMenu(this->data.getSchedule(),ucCode);
    system("clear");
    secondMenu.draw();
    options=secondMenu.getButtons();
    cout<<"Insert the class:";

    while(getInput(option)|| option>options.size() || option<1)cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';
    string class_=options[option-1];
    list<Lecture> empty;
    vector<Student> search = this->data.searchByUcClass(UcClass(ucCode,class_,empty));

    wait();
}

/**Functionality: display the capacity,number of students and the vacancies left of the classes of a UC.
 *
 * Description: This function will make the program more user friendly,it will start by clearing the terminal window,then it will display a menu with
 * all the UCs, following that it will ask the user to choose one(giving a warning if the input is invalid),after that it will search all the classes
 * of that UC and for each one of them will display the capacity,the number of students belonging to them and the vacancies left,the function will wait
 * until the user as finished seeing the Student to finish its execution.
 */
void Program::vacancies() const{
    system("clear");
    Menu menu(this->data.getSchedule());
    menu.draw();
    vector<string> options=menu.getButtons();
    cout<<"Insert the Uc:";
    int option;
    while(getInput(option)|| option>options.size() || option<1)cout<<"Invalid input please insert a number:";
    string ucCode=options[option-1];
    system("clear");
    int index;
    index= data.findUc(ucCode);
    cout<<ucCode+":\n";
    while(index<data.getSchedule().size() and this->data.getSchedule()[index].getUcCode()==ucCode){
       cout<<"Class:"+this->data.getSchedule()[index].getClassCode()+"|Capacity:"<<this->data.getSchedule()[index].getCapacity()<<
       "|Number of Students:"<<this->data.getSchedule()[index].getNumberOfStudents()<<"|Vacancies:"<<
       this->data.getSchedule()[index].getCapacity()-this->data.getSchedule()[index].getNumberOfStudents()<<endl;
        index++;
    }
    wait();

}

/**Functionality: Display the Students that have more that n UCs.
 *
 *Description:  This function will make the program more user friendly,it will start by clearing the terminal window,then it will ask the user
 * to insert the minimum number of UCs the Student should hava,after that it will display all the Students who met the condition,the function
 * will wait until the user as finished seeing the Student to finish its execution.
 */
void Program::moreThan() const {
    system("clear");
    cout<<"Insert number of minimum Ucs Student should have:";
    int n;
    while(getInput(n))cout<<"Invalid input please insert a number:";
    if(data.searchMoreThan(n).empty()){
        cout<<"No student with more than "<<n<<" UCs was found\n";
    }
    wait();

}

/**Functionality:  Display all the students belonging to a year
 *
 * Description: This function will make the program more user friendly,it will start by clearing the terminal window,then it will ask the user to insert
 * the year the Students should belong,after that it will search and display all the Students belonging to that year,the function will wait until the
 * user as finished seeing the Student to finish its execution.
 */
void Program::searchByYear() const {
    system("clear");
    cout<<"Insert the year:";
    int year;
    while(getInput(year))cout<<"Invalid input please insert a number:";
    if(data.searchByYear(year).empty()) cout<<"No students found\n";
    wait();
}

/**Functionality: Display all the Students who enter FEUP in the year X.
 *
 * Description: This function will make the program more user friendly,it will start by clearing the terminal window,then it will ask the user to insert
 * the year the Students should have entered,after that it will search and display all the Students who entered that year,the function will wait until the
 * user as finished seeing the Student to finish its execution.
 */
void Program::searchByAdmissionYear() const {
    system("clear");
    cout<<"Insert the year:";
    int year;
    while(getInput(year)) cout << "Invalid input please insert a number:";
    vector<Student> search = data.searchByYearAdmission(year);
    if(search.empty()) cout<<"No students found\n";
    else{
        showSearch(search);
    }
    wait();

}

/**Functionality: Make the program wait until the user wants it to continue
 *
 * Description: This is an auxiliary function, it will create a string and ask the user to insert anything when he wants to continue the program. That
 * way the program will be on hold until the user tells it to continue.
 */
void Program::wait() const {
    cout<<"\nEnter anything to go back:";
    string wait;
    cin>>wait;
}

void Program::handleRequestOption(char option) {
    set<Student> students = data.getStudents();
    int studentCode;
    string studentName;
    // Exiting the menu
    if (option == '6')
        this->currentMenuPage = 0;

    // Removing a student
    else if (option == '1') {
        cout << "Insert the student code from the student you want to remove: ";
        while (getInput(studentCode) || students.find(Student("Irrelevant", studentCode, {})) == students.end())
            cout << "Invalid input. Please insert a valid student code: ";
        data.removeStudent(studentCode);
    }

    // Adding a student
    else if (option == '2') {
        cout << "Insert a student code, that doesn't already exist, for the student you want to add: ";
        while (getInput(studentCode) || !validateStudentCode(studentCode) || students.find(Student("Irrelevant", studentCode, {})) != students.end())
            cout << "Invalid input. Please insert a valid student code: ";
        cout << "Insert the name of the student to add: ";
        cin.get();
        getline(cin, studentName);
        data.addStudent(studentCode, studentName);
    }

    // Adding a request to push to queue
    else {
        set<Student>* students = data.getStudentsReference();
        vector<UcClass>* ucClasses = data.getScheduleReference();
        Request newRequest = Request(students, ucClasses, option);
        if (!newRequest.getPairs().empty())
            data.pushRequestToQueue(newRequest);
    }
}

bool Program::validateStudentCode(int studentCode) {
    int year = studentCode / 100000;
    if (studentCode / 100000000 > 0 && studentCode / 1000000000 == 0 && year > 1926)
        return true;
    return false;
}

/**Functionality: Get the input in a safer way,that is, checking if the input given by the user is valid. If it is it will return true, otherwise
 * it will return false.
 *
 * Description: This is an auxiliary function, it will have a parameter passed by reference which will be the variable in which we are going to store the input
 * (the use of the template will make this function useful for every type of variable) then it will ask the user to give an input and after that will check
 * if the input is valid for the type of the variable. If it not valid it will clear the i nput and return false, otherwise ir will return true. As the
 * variable is passed by reference it will keep the value of the input.
 * @tparam type input
 * @return bool
 */
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

void Program::showSearch(vector<Student> search) const {
    system("clear");
    int start = 0;
    vector<int> starts;
    int previous_start = -1;
    int end;
    while(start>=0 && start < search.size()){
        system("clear");
        bool cond = false;
        for(int s : starts){
            if(s == start) cond = true;
        }
        if(!cond) starts.push_back(start);
        end = start + 20;
        if(end >= search.size()) end = search.size();
        while(start < end){
            search.at(start).print();
            start++;
        }
        start++;
        char option;
        bool c = true;
        cout << "[1] Next page\n[2] Previous page\n[3] Go back\nChoose an option: ";
        while (c) {
            cin >> option;
            switch (option) {
                case '1':
                    previous_start++;
                    c = false;
                    break;
                case '2':
                    if (previous_start < 0) start = -1;
                    else start = starts.at(previous_start);
                    previous_start--;
                    c = false;
                    break;
                case '3':
                    start = -1;
                    c = false;
                    break;
            }
            if(c) cout << "Choose a valid option: ";
        }
    }
}