#include "Program.h"
#include <limits>
#include <algorithm>

/**
 * Defines the current menu page at 0, creates all the menus and initialize the database
 * @brief The constructor of Program
 */
Program::Program() {
    this->currentMenuPage=0;
    createMenu();
    this->data=Database();
    cout<<"Welcome to the Better Sigarra.\n";
}

/**
 * Auxiliary function of the constructor Program(). It creates the menus the program needs by initializing them
 * and then pushing them to the Program's menu vector
 * @brief Initializes all the menus
 */
void Program::createMenu() {
    this->menus.push_back(Menu("../Menus/mainMenu.txt"));//Initialize main menu
    this->menus.push_back(Menu("../Menus/showMenu.txt"));//Initialize show menu
    this->menus.push_back(Menu("../Menus/searchSubMenu.txt"));// Initialize search submenu
    this->menus.push_back(Menu("../Menus/scheduleSubMenu.txt"));// Initialize schedule submenu
    this->menus.push_back(Menu("../Menus/requestsMenu"));

}

/**
 * @see Menu::draw()
 * @brief Draws the current page of the menu we are in
 */
void Program::draw() const {
    this->menus[this->currentMenuPage].draw(); //draw the current menu
}

/**
 * Uses a while loop to stop the program from finishing without the users permission. The while will loop will be broke
 * when the Program attribute currentMenuPage is equal to -1. It also guarantees that the initial files are updated when
 * exiting the application
 * @brief Starts the program and exits it properly
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

/**
 * This function is what is going to make our program work, it will draw the current menu pages get the inputs the user gives
 * (giving a warning if the input is invalid) and decides what the program should do next. It will do that by calling other functions from the
 * Program with the help of a switch.
 * @brief Decides what is done based on the menu that is being shown and the input that is given
 */
void Program::menu() {
    draw(); //draw the current menu
    cout<<"Choose an option: ";
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
                            this->currentMenuPage=3;
                            break;
                        case '4':
                            vacancies();
                            break;
                        case '5':
                            this->currentMenuPage = 4;
                            break;
                        case '6':
                            data.handleRequests();
                            break;
                        case '7':
                            this->currentMenuPage = -1;
                            break;

                        default:
                            cond = true;
                    }
                    break;
                case 1:
                    switch (option[0]){
                        case '1':
                            showStudents();
                            break;
                        case '2':
                            showUcs();
                            break;
                        case '3':
                            showClasses();
                            break;
                        case '4':
                            currentMenuPage=0;
                            break;
                        default:
                            cond = true;
                    }



                    break;
                case 2: //is on show sub-menu
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

                case 3:
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
                case 4:
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

/**
 * Prints a student's schedule using a graphical representation or a diagram depending on the user's input. The user will
 * be notified if the student code that was given doesn't exist.
 * @see Student::printGraphicalSchedule
 * @see Student::printDiagramSchedule
 * @brief Prints the schedule of a Student
 */
void Program::printStudentSchedule() const {
    system("clear");
    Menu menu("../Menus/scheduleSubMenu2.txt");
    menu.draw();
    cout<<"Choose an option: ";
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
        system("clear");
        if(option=="1")itr->printGraphicalSchedule();
        else itr->printDiagramSchedule();
    }else {
        cout<<"Student not found\n";
    }
    wait();
}

/**
 * Prints a class' schedule using a graphical representation or a diagram depending on the user's input. The user will
 * be notified if the year or class input is invalid.
 * @see Database::printClassGraphicSchedule
 * @see Database::printClassDiagramSchedule
 * @brief Prints the schedule of class
 */
void Program::printClassSchedule() const {
    system("clear");
    Menu menu("../Menus/scheduleSubMenu2.txt");
    menu.draw();
    cout<<"Choose an option: ";
    string option;
    cin >>option;
    while( option!="1" and option!="2"){
        cout<<"Invalid input.Please enter a valid option: ";
        cin>>option;
    }
    system("clear");
    cout<<"Insert the class's year:";
    char year;
    while(getInput(year)|| (year-'1'>2 || year-'1'<0))cout<<"Invalid input please insert a number between 1-3:";
    system("clear");
    Menu secondaryMenu(data.getSchedule(),year);
    secondaryMenu.draw();
    cout<<"Choose an option: ";
    vector<string> options=secondaryMenu.getButtons();
    cout<<"Insert the class:";
    int secondOption;
    while(getInput(secondOption)|| secondOption>options.size() || secondOption<1)cout<<"Invalid input please insert a number between 1-"<<options.size()<<':';
    string  class_=options[secondOption-1];
    system("clear");
    if(option=="1") data.printClassGraphicSchedule(class_);
    else data.printClassDiagramSchedule(class_);
    wait();

}

/**
 * Given a student code by the user as input, prints the name and student code of that student if it exists in the database.
 * If not, the student code given is invalid and the user is notified.
 * @brief Searches and prints a student's name and student code
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
        cout << " _______________________________________________________________________\n";
        cout << "|                                                                       |\n";
        itr->print();
        cout << "|_______________________________________________________________________|\n";
    }else {
        cout<<"Student not found\n";
    }
    wait();

}

/**
 * Given an year and corresponding class from the menu as input, prints the name and student code of every student in that class. If the input
 * is invalid the user is notified.
 * @see showSearch()
 * @see customSorts()
 * @brief Search and prints all students from a class
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
    vector<Student> search = data.searchByClass(options[option-1]);
    if(!search.empty()){
        customSorts(search);
        showSearch(search);
    }
}

/**
 * Given a curricular unit from the menu as input, prints the name and student code of every student in that curricular unit.
 * If the input is invalid the user is notified.
 * @see showSearch()
 * @see customSorts()
 * @brief Search and prints all students from a curricular unit
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
    vector<Student> search = data.searchByUC(ucCode);
    if(!search.empty()){
        customSorts(search);
        showSearch(search);
    }

}

/**
 * Given a curricular unit and a class from that curricular unit as input from the menu, prints the name and student code of every student
 * in the class of that particular course unit. If the input invalid the user is notified.
 * @see showSearch()
 * @see customSorts()
 * @brief Search Students belonging to a class of a particular curricular unit
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
    vector<Student> search = data.searchByUcClass(UcClass(ucCode,class_,empty));
    if(!search.empty()){
        customSorts(search);
        showSearch(search);
    }

}

/**
 * Given a curricular unit as input from the menu, prints the capacity, vacancies and current number os students enrolled in each class
 * of that curricular unit. If the input is invalid the user is notified. \n
 * Complexity: O(m + n) being m the number of classes in the classes vector and n the number of classes of a particular curricular unit
 * @see Database::findUc()
 * @brief Displays the capacity, number of students and the vacancies of the classes from a curricular unit
 */
void Program::vacancies() const{
    system("clear");
    Menu menu(this->data.getSchedule());
    menu.draw();
    cout<<"Choose an option: ";

    vector<string> options=menu.getButtons();
    cout<<"Insert the Uc:";
    int option;
    while(getInput(option)|| option>options.size() || option<1)cout<<"Invalid input please insert a number:";
    string ucCode=options[option-1];
    system("clear");
    int index;
    index = data.findUc(ucCode);
    cout<<ucCode+":\n";
    cout<<" _______________________________________________________________________\n";
    cout<<"|                                                                       |\n";
    while(index<data.getSchedule().size() and this->data.getSchedule()[index].getUcCode()==ucCode){
       cout<<"| Class: "+this->data.getSchedule()[index].getClassCode()+" | Capacity: "<<this->data.getSchedule()[index].getCapacity()<<
       " | Number of Students: "<<this->data.getSchedule()[index].getNumberOfStudents()<<" | Vacancies: "<<
       this->data.getSchedule()[index].getCapacity()-this->data.getSchedule()[index].getNumberOfStudents()<<" |\n";
        index++;
    }
    cout<<"|_______________________________________________________________________|\n";
    wait();

}

/**
 * Given an integer "n" as input, prints all the students' names and student codes that are enrolled in "n" or more curricular units. If the input
 * is lower than 1 all students will be printed.
 * @see customSorts()
 * @brief Displays the students that are enrolled in "n" or more curricular units
 */
void Program::moreThan() const {
    system("clear");
    cout<<"Insert number of minimum Ucs Student should have:";
    int n;
    while(getInput(n))cout<<"Invalid input please insert a number:";
    vector<Student> search = data.searchMoreThan(n);
    if(!search.empty()){
        customSorts(search);
        showSearch(search);
    }


}

/**
 * Given an year "n" as input, prints the name and student code of every student that is in the "n"th year.
 * @see showSearch()
 * @see customSorts()
 * @brief Displays all the students belonging to a year
 */
void Program::searchByYear() const {
    system("clear");
    cout<<"Insert the year:";
    int year;
    while(getInput(year))cout<<"Invalid input please insert a number:";
    vector<Student> search = data.searchByYear(year);
    if(!search.empty()){
        customSorts(search);
        showSearch(search);
    }

}

/**
 * Given an year "n" as input, prints the name and student code of every student that became a student at FEUP in the year n.
 * @see showSearch()
 * @see customSorts()
 * @brief Displays all the Students who became a student at FEUP in the year n.
 */
void Program::searchByAdmissionYear() const {
    system("clear");
    cout<<"Insert the year:";
    int year;
    while(getInput(year)) cout << "Invalid input please insert a number:";
    vector<Student> search = data.searchByYearAdmission(year);
    if(!search.empty()){
        customSorts(search);
        showSearch(search);
    }


}

/**
 * @brief Pauses the program until the user writes something in the console.
 */
void Program::wait() const {
    cout<<"\nEnter anything to go back:";
    string wait;
    cin>>wait;
}

/**
 * Chooses what to do based on the option given: \n
 * (1) Remove a student from the database \n
 * (2) Add a student to the database \n
 * (3) Submit a request to remove a class of a student \n
 * (4) Submit a request to add a class of a student \n
 * (5) Submit a request to change a class of a student \n
 * (6) Goes back to the main menu
 * @brief Handles what to do next based on the option that is given as input
 * @param option - option of the request
 */
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

/**
 * @brief Determines if the given student's student code is valid or not
 * @param studentCode - student code of a student
 * @return true if the student code is valid, false otherwise
 */
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
 * Gets user's input and checks if it valid according to the type of the variable "input". The variable "input" will be
 * updated since it is passed by reference.
 * @brief Validates the input depending on the type of input that is desired
 * @tparam type - variable that will hold the user's input
 * @return true if the input was valid, false otherwise.
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

/**
 * Prints all the students' name and student code from the listing that was previously done. The printing is done by pages, so
 * that the user doesn't have to scroll to see all the outputs.
 * @brief Prints any student listing that was done
 * @param search - vector of students to print
 */
void Program::showStudents() const{
    vector<Student> search = data.allStudents();
    customSorts(search);
    showSearch(search);

}

/**
 * @brief Sets up the printing of the curricular units
 * @see UcClass::printUcCode()
 */
void Program::showUcs() const{
    vector<UcClass> search = data.allUcs();
    cout << " _______________________\n";
    cout << "|                       |\n";
    for(UcClass ucClass : search){
        ucClass.printUcCode();
    }
    cout << "|_______________________|\n";
    wait();
}

/**
 * @brief Sets up the printing of the classes
 * @see UcClass::printClassCode()
 */
void Program::showClasses() const{
    Menu menu(data.getSchedule());
    menu.draw();

    cout<<"Choose an UC:";
    int option;
    vector<string>options=menu.getButtons();
    while(getInput(option)||option<1 || option>options.size())cout<<"Invalid input please insert a number between 1-"+options.size()+':';
    string uc=options[option-1];
    vector<UcClass>ucClasses=data.getSchedule();
    int index= data.findUc(uc);
    cout << " _______________________\n";
    cout << "|                       |\n";
    while(ucClasses[index].getUcCode()==uc){
        ucClasses[index].printClassCode();
        index++;
    }
    cout << "|_______________________|\n";
    wait();



}

/**
 * @brief Sets up the printing for any vector of students given by the variable search. The printing is done in pages so that
 * the user doesn't have to scroll to see all the output
 * @param search - vector of students to print
 */
void Program::showSearch(vector<Student> search) const {
    system("clear");
    int start = 0;
    vector<int> starts;
    int previous_start = -1;
    int end;
    int currentPage = 1;
    while(start>=0 && start < search.size()){
        system("clear");
        bool cond = false;
        for(int s : starts){
            if(s == start) cond = true;
        }
        if(!cond) starts.push_back(start);
        end = start + 15;
        if(end >= search.size()) end = search.size();
        if(currentPage <= 9){
            cout << " _______________________________________________________________________\n";
            cout << "|                            Page: "<< currentPage <<"                                    |\n";
        }
        else{
            cout << " _______________________________________________________________________\n";
            cout << "|                            Page: "<< currentPage <<"                                   |\n";
        }
        cout << "|_______________________________________________________________________|\n";
        cout << "|                                                                       |\n";
        while(start < end){
            search.at(start).print();
            start++;
        }

        string option;
        bool c = true;
        cout << "|-----------------------------------------------------------------------|\n";
        cout << "| [1] Next page\t\t\t\t\t\t\t\t|\n| [2] Previous page\t\t\t\t\t\t\t|\n| [3] Go back\t\t\t\t\t\t\t\t|\n";
        cout << "|_______________________________________________________________________|\n";
        cout << "Choose an option: ";
        while (c) {
            cin >> option;
            if (option.length() == 1 && isdigit(option[0])) {
                switch (option[0]) {
                    case '1':
                        previous_start++;
                        currentPage++;
                        c = false;
                        break;
                    case '2':
                        if (previous_start < 0) start = -1;
                        else start = starts.at(previous_start);
                        previous_start--;
                        currentPage--;
                        c = false;
                        break;
                    case '3':
                        start = -1;
                        c = false;
                        break;
                }
            }
            if(c) cout << "Choose a valid option: ";
        }
    }
}

/**
 * @brief Used to order students by ascending alphabetic order
 * @param s1 - first student
 * @param s2 - second student
 * @return true if the first student's name is lower than the second's, false otherwise
 */
bool alfabeticOrder(Student s1, Student s2){
    return s1.getStudentName() <= s2.getStudentName();
}

/**
 * @brief Used to order students by descending alphabetic order
 * @param s1 - first student
 * @param s2 - second student
 * @return true if the first student's name is higher than the second's, false otherwise
 */
bool invertedAlfabeticOrder(Student s1, Student s2){
    return !alfabeticOrder(s1,s2);
}

/**
 * @brief Used to order students by upCode ascending order
 * @param s1 - first student
 * @param s2 - second student
 * @return true if the first student's upCode is lower than the second's, false otherwise
 */
bool upCodeOrder(Student s1, Student s2) {
    return s1.getStudentCode() <= s2.getStudentCode();
}

/**
 * @brief Used to order students by upCode descending order
 * @param s1 - first student
 * @param s2 - second student
 * @return true if the first student's upCode is higher than the second's, false otherwise
 */
bool invertedUpCodeOrder(Student s1, Student s2){
    return !upCodeOrder(s1,s2);
}

/**
 * If the students are enrolled int the same number of classes, thier are sorted in ascending student's name order
 * @param s1 - first student
 * @param s2 - second student
 * @return true if the first student is enrolled in more classes than the second student, false otherwise
 */
bool ucAmountOrder(Student s1, Student s2){
    if(s1.getUcClasses().size() == s2.getUcClasses().size()){
        return alfabeticOrder(s1,s2);
    }

    return s1.getUcClasses().size() < s2.getUcClasses().size();
}

/**
 * If the students are enrolled int the same number of classes, thier are sorted in ascending student's name order
 * @param s1 - first student
 * @param s2 - second student
 * @return true if the first student is enrolled in less classes than the second student, false otherwise
 */
bool invertedUcAmountOrder(Student s1, Student s2){
    if(s1.getUcClasses().size() == s2.getUcClasses().size()){
        return alfabeticOrder(s1,s2);
    }

    return s2.getUcClasses().size() < s1.getUcClasses().size();
}

/**
 * Orders the vector of students depending on the input given: \n
 * (1) Order by ascending alphabetic order \n
 * (2) Order by descending alphabetic order \n
 * (3) Order by ascending upCode order \n
 * (4) Order by descending upCode order \n
 * (5) Order by ascending number of curricular units order\n
 * (6) Order by descending number of curricular units order \n
 * Complexity: O(log(n)) being n the number of students to be sorted. The complexity doesn't depend on the option chosen
 * @see alfabeticOrder()
 * @see invertedAlfabeticOrder()
 * @see upCodeOrder()
 * @see invertedUpCodeOrder()
 * @see ucAmountOrder()
 * @see invertedUcAmountOrder()
 * @brief Orders the vector of students to be printed depending on the option that is chosen
 * @param search - vector of students to be sorted
 */
void Program::customSorts(vector<Student>& search) const {
    bool cond = true;
    string option;
    Menu menu = Menu("../Menus/sortMenu.txt");
    menu.draw();
    cout<<"Choose an option: ";
    while (cond) {
        cin >> option;
        if (option.length() == 1 && isdigit(option[0])) {
            switch (option[0]) {
                case '1':
                    sort(search.begin(), search.end(), alfabeticOrder);
                    cond = false;
                    break;
                case '2':
                    sort(search.begin(), search.end(), invertedAlfabeticOrder);
                    cond = false;
                    break;
                case '3':
                    sort(search.begin(), search.end(), upCodeOrder);
                    cond = false;
                    break;
                case '4':
                    sort(search.begin(), search.end(), invertedUpCodeOrder);
                    cond = false;
                    break;
                case '5':
                    sort(search.begin(), search.end(), ucAmountOrder);
                    cond = false;
                    break;
                case '6':
                    sort(search.begin(), search.end(), invertedUcAmountOrder);
                    cond = false;
                    break;
            }
        }
        if(cond) cout << "Choose a valid option\n";
    }
}

