#include <limits>
#include <set>
#include "Request.h"
#include "Menu.h"

Request::Request() {}

/**
 * @brief Copy constructor
 * @param request - request to be copied
 */
Request::Request(const Request &request) {
    this->student = request.student;
    this->removeAdd = request.removeAdd;
}

/**
 * @brief Parametrized constructor
 * @param student_ - the student on which the changes are to be made
 * @param pairs_ - list of pairs. Each pair is a UcClass to remove and a UcClass to add
 */
Request::Request(Student student_, list<pair<UcClass, UcClass *>> pairs_) {
    this->student = student_;
    this->removeAdd = pairs_;
}

/**
 * @brief Pairs getter
 * @return a list of pairs of UcClasses
 */
list<pair<UcClass, UcClass *>> Request::getPairs() const {
    return this->removeAdd;
}

/**
 * @brief Student getter
 * @return a student
 */
Student Request::getStudent() const {
    return this->student;
}

/**
 * Uses binary search to
 * @brief Finds the first class from a curricular unit
 * @param ucCode - name of the curricular unit
 * @param ucClasses - vector of all classes to be searched
 * @return
 */
int Request::findUc(string ucCode, vector<UcClass> ucClasses) {
    int low = 0, high = ucClasses.size() - 1;
    int middle;
    while (low != high) {
        middle = low + (high - low)/2;
        if (ucClasses[middle].getUcCode() >= ucCode) {
            high = middle;
        }
        else {
            low = middle + 1;
        }
    }
    return low;
}

/**
 * Firstly the student's upCode is asked to fetch the student on which the changes are to be made. After that the option
 * inputted represents what happens: \n
 * (1) Option '3': Removes a class from the classes that the student has; \n
 * (2) Option '4': Adds a class to the student's classes; \n
 * (3) Option '5': Changes a pair or multiple pair of classes. In each pair, a class from the student is removed and a class chosen is added \n
 * These changes don't take effect after the execution of this function. They will only be analysed and submitted when the function Database::handleRequests() is called \n
 * Complexity: (1) O(n) being n the number of classes of the student (process of fetching the class to remove). (2) O(n) if the creation of the menu is taken into account,
 * otherwise O(log(n)) n being the number of classes in the vector of classes; (3) O(m*n) being m the number of pairs that the user wants to change
 * and n the number of classes in the vector of classes (to create the menu), or the number of classes of the student (to fetch the class to remove)
 * @brief Depending on the option selected, builds a new request to be added to the main queue
 * @see getUcClassToRemove()
 * @see getUcClassToAdd()
 * @param students - pointer to the set of students of the database
 * @param ucClasses - pointer to the vector of classes of the database
 * @param option - char that represents the type of request to be made
 */
Request::Request(set<Student>* students, vector<UcClass>* ucClasses, char option) {
    int studentCode;
    string subMenuOption;
    vector<string> buttons;
    set<UcClass> alreadyAdded;
    list<UcClass> ucClassesList;
    UcClass *toAdd;

    // Get student code of student to change
    system("clear");
    cout << "Write your student code: ";
    cin >> studentCode;
    while (cin.fail() || students->find(Student("", studentCode, ucClassesList)) == students->end()) {
        cout << endl << "Please insert a valid student code: ";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin >> studentCode;
    }
    this->student = *(students->find(Student("", studentCode, ucClassesList)));

    switch (option) {
        case '3': {
            UcClass toRemove = getUcClassToRemove();
            pair<UcClass, UcClass *> p(toRemove, nullptr);
            this->removeAdd.push_back(p);
            break;
        }
        case '4': {
            toAdd = getUcClassToAdd(ucClasses);
            pair<UcClass, UcClass *> p(UcClass("-1", "-1", {}), toAdd);
            this->removeAdd.push_back(p);
            break;
        }

        case '5': {
            list<UcClass> ucClassesAvailable = student.getUcClasses();
            bool done = false;

            // Get the class to Remove
            while (ucClassesAvailable.size() > 0) {
                Menu menu1(ucClassesAvailable);
                buttons = menu1.getButtons();
                buttons.push_back("Submit request");
                menu1.setButtons(buttons);
                menu1.draw();
                cout<<"Choose an option: ";
                while (true) {
                    cin >> subMenuOption;
                    if (checkRequestInput(buttons, subMenuOption)) {
                        if (stoi(subMenuOption) == buttons.size())
                            done = true;
                        break;
                    }
                    cout << "Please insert a valid option: ";
                }

                if (done)
                    break;

                // Remove class chosen from available to choose from
                auto itr1 = ucClassesAvailable.begin();
                advance(itr1, stoi(subMenuOption) - 1);
                UcClass intermediate = *itr1;
                ucClassesAvailable.erase(itr1);
                UcClass toRemove = intermediate;

                // Get the class to add
                while (true) {
                    toAdd = getUcClassToAdd(ucClasses);
                    if (alreadyAdded.find(*toAdd) == alreadyAdded.end())
                        break;
                    else{

                        cout << "You have already added this class in this request!Choose again:\n";


                    }
                }
                alreadyAdded.insert(*toAdd);
                pair<UcClass, UcClass *> p(toRemove, toAdd);
                this->removeAdd.push_back(p);
            }
        }
    }
}

/**
 * Complexity: O(n) n being the number of classes the student is in
 * @brief Chooses the class to remove from the student the request is about
 * @return class to remove from student
 */
UcClass Request::getUcClassToRemove() {
    string subMenuOption;
    vector<string> buttons;

    list<UcClass> ucClassesList = this->student.getUcClasses();
    Menu menu = Menu(ucClassesList);
    buttons = menu.getButtons();
    menu.draw();
    cout<<"Choose an UC to remove: ";
    while (true) {
        cin >> subMenuOption;
        if (checkRequestInput(buttons, subMenuOption)) {
            break;
        }
        cout << "Please insert a valid option: ";
    }
    auto itr = ucClassesList.begin();
    advance(itr, stoi(subMenuOption) - 1);
    return *itr;
}

/**
 * The function fetches the chosen class with binary search and doesn't let the user choose a class the student already has\n
 * Complexity: O(log(n)) being n the number of classes in the vector of classes of the database if the menu creation is accounted for, otherwise
 * it is O(n)
 * @brief Chooses a class to be added to the student the request is about
 * @see findUc()
 * @param ucClasses - pointer to the vector of classes of the database
 * @return pointer to the class that is to be added
 */
UcClass *Request::getUcClassToAdd(vector<UcClass>* ucClasses) {
    string subMenuOption;
    vector<string> buttons;
    int ucIndex;
    UcClass* toAdd;
    bool choseUcClass = false;

    Menu menu1 = Menu(*ucClasses);
    menu1.draw();
    cout<<"Choose an UC to add: ";
    while (true) {
        Menu menu = Menu(*ucClasses);
        buttons = menu.getButtons();
        cin >> subMenuOption;

            if (checkRequestInput(buttons, subMenuOption)) {
                string aUcCode = buttons[stoi(subMenuOption) - 1];

                buttons.clear();
                ucIndex = findUc(aUcCode, *ucClasses);
                for (int i = ucIndex; (*ucClasses)[i].getUcCode() == aUcCode; i++) {
                    buttons.push_back((*ucClasses)[i].getClassCode());
                }
                menu.setButtons(buttons);
                menu.draw();
                cout << "Now choose a class for the UC: ";
                while (true) {
                    cin >> subMenuOption;
                    if (checkRequestInput(buttons, subMenuOption)) {
                        toAdd = &(*ucClasses)[ucIndex + stoi(subMenuOption) - 1];
                        if (!this->student.hasUcClass(*toAdd)) {
                            choseUcClass = true;
                        } else
                            menu1.draw();
                            cout << "You are already part of this class.Choose again:" << endl;
                        break;
                    }
                }
            }

        else{
            choseUcClass=false;
            menu1.draw();
            cout<<"You already have this UC!Choose again:";
        }
        if (choseUcClass)
            break;
        menu1.draw();
        cout << "Please insert a valid option: ";
    }
    return toAdd;
}

/**
 * @brief Allows the verification of the input depending on the number of buttons of the menu
 * @param buttons - buttons of the menu to be printed
 * @param option - option chosen by the user
 * @return
 */
bool Request::checkRequestInput(vector<std::string> buttons, std::string option) {
    if (buttons.size() > 9) {
        if (option.size() == 1 && isdigit(option[0])) {
            if (stoi(option) >= 1 && stoi(option) <= 9)
                return true;
        }
        else if (option.size() == 2 && isdigit(option[0]) && isdigit(option[1]))
            if (stoi(option) >= 10 && stoi(option) <= buttons.size())
                return true;
    }
    else {
        if (option.size() == 1 && isdigit(option[0]))
            if (stoi(option) >= 1 && stoi(option) <= buttons.size()) {
                return true;
            }
    }
    return false;
}

/**
 * This function handles a certain request. Firstly the function checks if the student to which the changes are to be made hasn't been removed
 * Afterwards, there are two things that are handled: \n
 * (1) If the left side of the pair is a valid class, that class needs to be removed from the student. For that, the function checks
 * if the student has that class and if its removal doesn't cause unbalance. If so the class is removed from the student
 * (2) If the right side of the pair is a valid class, that class needs to be added to the student. For that, the function checks if
 * the number of current students isn't equal to the capacity of the class so that the capacity isn't exceeded; if
 * the student is already in a class in that curricular unit; if the change may cause unbalance and if there is an invalid overlap between
 * the lectures to be added and each lecture from the classes the student is in. If everything checks out, the class is added to the student
 * Complexity: O(m*(n + p)) being m the number of pairs to be analysed, n = O(Student::hasUcClass() + checkUnbalance() + Student::removeUcClass())
 * and p = O(Student::hasUc() + checkUnbalance() + a*b*c*(Lecture::Overlaps() + Lecture::isOverlapableWith()) being a the number
 * of classes the student is in, b the number of lectures in each of those classes and c the number of lectures from the class to add
 * @brief Handles a request
 * @param students - pointer to the set of students of the database
 * @param ucClasses - vector of classes of the database
 * @return a list of pairs of booleans so that the database knows which classes have to have their "current number of students" updated
 */
list<pair<bool, bool>> Request::handleRequest(set<Student>* students,vector<UcClass> ucClasses) {
    list<pair<bool, bool>> changeNumberStudents;// right increment left decrement
    pair<bool, bool> aChange;// just auxiliary pair
    auto newStudentItr = (*students).find(this->student);// copy of the student
    if(newStudentItr==students->end()) {
        // Student doesn't exist anymore
        cout<<"Failed! Student does not exist anymore!";
        return {};
    }
    Student newStudent = *newStudentItr;// auxiliary student
    list<UcClass> stuUcClasses;//ucClasses da copia
    UcClass *toAdd;//para ir buscar a parte direita do pair
    list<Lecture> toAddLectures;//aux recebe as aulas da ucClass em cima
    int posForAdding;//posição onde adicionar

    for (auto itr = removeAdd.begin(); itr != removeAdd.end(); itr++) {
        aChange = {false, false};
        UcClass toRemove = itr->first;

        if (toRemove.getUcCode() != "-1") {
            if (newStudent.hasUcClass(toRemove)) {
                toRemove.setNumberOfStudents(toRemove.getNumberOfStudents() - 1);
                if (!checkUnbalance(ucClasses, toRemove, 0)) {
                    newStudent.removeUcClass(toRemove);
                    aChange.first = true;
                } else {
                    cout<<"Failed! Change would cause unbalance!\n";
                    return {};
                }
            }else{
                cout<<"Failed! Student does not have the UC "+toRemove.getUcCode()+", thus is not able to remove it!\n";
                return {};
            }
        }
        changeNumberStudents.push_back(aChange);
    }

    auto itrChanges = changeNumberStudents.begin();
    for (auto itr = removeAdd.begin(); itr != removeAdd.end(); itr++) {
        stuUcClasses = newStudent.getUcClasses();
        toAdd = itr->second;
        posForAdding = 0;

        if (toAdd != nullptr) {

            if (toAdd->getNumberOfStudents() >= toAdd->getCapacity()) {
                cout<<"Failed! Class "+toAdd->getClassCode()+" in the UC"+toAdd->getUcCode()+" is already full\n";
                return {{false,false}};
            }
            else if (newStudent.hasUc(toAdd->getUcCode())){
                cout<<"Failed! Student already has "+toAdd->getUcCode()+" has an UC!\n";
                return {};
            }
            else {
                toAdd->setNumberOfStudents(toAdd->getNumberOfStudents() + 1);
                if (checkUnbalance(ucClasses, *toAdd, 1)) {
                    cout<<"Failed! Change would cause unbalance!\n";
                    return {};
                }
                for (auto itrUcClasses = stuUcClasses.begin(); itrUcClasses != stuUcClasses.end(); itrUcClasses++) {
                    list<Lecture> lectures = itrUcClasses->getLectures();
                    if (*itrUcClasses < *toAdd)
                        posForAdding++;
                    for (auto itrLectures = lectures.begin(); itrLectures != lectures.end(); itrLectures++) {
                        toAddLectures = toAdd->getLectures();
                        for (auto itrToAddLectures = toAddLectures.begin(); itrToAddLectures != toAddLectures.end(); itrToAddLectures++) {
                            if (itrToAddLectures->Overlaps(*itrLectures) && !itrToAddLectures->isOverlapableWith(*itrLectures)) {
                                cout<<"Failed! " +toAdd->getUcCode()+'-'+toAdd->getClassCode()+" overlaps with "+itrUcClasses->getUcCode()+'-'+itrUcClasses->getClassCode()+"\n";
                                return {{false,false}};
                            }
                        }
                    }
                }
                newStudent.addUcClass(toAdd, posForAdding);
                itrChanges->second = true;
            }
        }
        itrChanges++;
    }
    this->student = newStudent;
    cout<<"Passed!\n";
    return changeNumberStudents;
}

/**
 * The unbalance exists if in a particular curricular unit, the difference between the current number of students of two classes
 * is higher than 3. If so the user will be prompted to choose if the change should go through or not \n
 * Complexity: O(m * n) being m the number of classes of the vector of classes from the database and n the number of classes
 * of a particular curricular unit
 * @brief Checks if adding or removing a student of a class causes unbalance of the number of students in a curricular unit
 * @param ucClasses - vector of classes of the database
 * @param ucClass - class to be added to removed
 * @param type - type of request (removing or adding a class)
 * @return true if there is unbalance and the user choose to go through with the change, false if there is no unbalance or the user doesn't want
 * to go through with the change
 */
bool Request::checkUnbalance(vector<UcClass> ucClasses, UcClass ucClass, int type)  {
    int index=findUc(ucClass.getUcCode(),ucClasses);
    bool cond=false;
    int numberStudents=ucClass.getNumberOfStudents();
    while(index<ucClasses.size()&& ucClasses[index].getUcCode()==ucClass.getUcCode()){
        if(abs(ucClasses[index].getNumberOfStudents()-numberStudents) >3){
            cond=true;
            break;
        }
        index++;
    }
    if(cond){
        if (type == 0)
            cout << "Removing " << ucClass.getUcCode() << ' ' << ucClass.getClassCode() << " from student " << this->student.getStudentCode() << endl;
        else if (type == 1)
            cout << "Adding " << ucClass.getUcCode() << ' ' << ucClass.getClassCode() << " to student " << this->student.getStudentCode() << endl;
        cout<<"This change will cause unbalance do you want to change it anyway?[y/n] ";
        char answer;
        cin>>answer;
        while (cin.fail() || (tolower(answer)!='y' and tolower(answer)!='n')) {
            cout<<"Invalid input.Please insert a y(yes) or a n(no): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin>>answer;
        }
        if(tolower(answer)=='n') return true;
    }
    return false;
}