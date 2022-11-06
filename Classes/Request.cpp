#include <limits>
#include <set>
#include "Request.h"
#include "Menu.h"

Request::Request() {}

/**
 * @brief Copy constructor
 * @param request a request to be copied
 */
Request::Request(const Request &request) {
    this->student = request.student;
    this->removeAdd = request.removeAdd;
}

/**
 * @brief Parametrized constructor
 * @param student_ the student on which the changes are to be made
 * @param pairs_ list of pairs. Each pair is a UcClass to remove and a UcClass to add
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
 * @brief Finds the first class from a Curricular Unit
 * @param ucCode name of the Curricular Unit
 * @param ucClasses vector of all classes to be searched
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

Request::Request(set<Student>* students, vector<UcClass>* ucClasses, char option) {
    int studentCode, ucIndex;
    string subMenuOption;
    vector<string> buttons;
    set<UcClass> alreadyAdded;
    list<UcClass> ucClassesList;
    UcClass *toAdd;
    bool choseUcClass = false;

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
    ucClassesList = this->student.getUcClasses();

    switch (option) {
        case '3': {
            Menu menu = Menu(ucClassesList);
            buttons = menu.getButtons();
            menu.draw();
            while (true) {
                cin >> subMenuOption;
                if (checkRequestInput(buttons, subMenuOption)) {
                    break;
                }
                cout << "Please insert a valid option: ";
            }
            auto itr = ucClassesList.begin();
            advance(itr, stoi(subMenuOption) - 1);
            UcClass toRemove = *itr;
            pair<UcClass, UcClass *> p(toRemove, nullptr);
            this->removeAdd.push_back(p);
            break;
        }
        case '4': {
            Menu menu = Menu(*ucClasses);
            menu.draw();
            while (true) {
                menu = Menu(*ucClasses);
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
                    while (true) {
                        cin >> subMenuOption;
                        if (checkRequestInput(buttons, subMenuOption)) {
                            toAdd = &(*ucClasses)[ucIndex + stoi(subMenuOption) - 1];
                            if (!this->student.hasUcClass(*toAdd)) {
                                choseUcClass = true;
                            }
                            else
                                cout << "You are already part of this class." << endl;
                            break;
                        }
                    }
                }
                if (choseUcClass)
                    break;
                cout << "Please insert a valid option: ";
            }

            pair<UcClass, UcClass *> p(UcClass("-1", "-1", {}), toAdd);
            this->removeAdd.push_back(p);
            break;
        }

        case '5': {
            list<UcClass> ucClassesAvailable = student.getUcClasses();
            bool done = false;

            while (ucClassesAvailable.size() > 0) {
                choseUcClass = false;
                Menu menu1(ucClassesAvailable);
                buttons = menu1.getButtons();
                buttons.push_back("Quit");
                menu1.setButtons(buttons);
                menu1.draw();
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

                // Remove from available to choose from
                auto itr1 = ucClassesAvailable.begin();
                advance(itr1, stoi(subMenuOption) - 1);
                UcClass intermediate = *itr1;
                ucClassesAvailable.erase(itr1);
                UcClass toRemove = intermediate;

                Menu menu2 = Menu(*ucClasses);
                menu2.draw();
                while (true) {
                    menu2 = Menu(*ucClasses);
                    buttons = menu2.getButtons();
                    cin >> subMenuOption;
                    if (checkRequestInput(buttons, subMenuOption)) {
                        string aUcCode = buttons[stoi(subMenuOption) - 1];
                        buttons.clear();
                        ucIndex = findUc(aUcCode, *ucClasses);
                        for (int i = ucIndex; (*ucClasses)[i].getUcCode() == aUcCode; i++) {
                            buttons.push_back((*ucClasses)[i].getClassCode());
                        }
                        menu2.setButtons(buttons);
                        menu2.draw();
                        while (true) {
                            cin >> subMenuOption;
                            if (checkRequestInput(buttons, subMenuOption)) {
                                toAdd = &(*ucClasses)[ucIndex + stoi(subMenuOption) - 1];
                                if (!this->student.hasUcClass(*toAdd) && alreadyAdded.find(*toAdd) == alreadyAdded.end()) {
                                    choseUcClass = true;
                                }
                                else
                                    cout << "You are already part of this class or already added it in this request." << endl;
                                break;
                            }
                        }
                    }
                    if (choseUcClass)
                        break;
                    cout << "Please insert a valid option: ";
                }
                alreadyAdded.insert(*toAdd);
                pair<UcClass, UcClass *> p(toRemove, toAdd);
                this->removeAdd.push_back(p);
            }
        }
    }
}

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

list<pair<bool, bool>> Request::handleRequest(set<Student>* students,vector<UcClass> ucClasses) {
    list<pair<bool, bool>> changeNumberStudents;// right increment left decrement
    pair<bool, bool> aChange;// just aux pair
    auto newStudentItr = (*students).find(this->student);// real student
    Student newStudent = *newStudentItr;// aux student
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
                cout<<"Failed!Student does not have the UC "+toRemove.getUcCode()+", thus is not able to remove it!\n";
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
                cout<<"Failed!Class "+toAdd->getClassCode()+" in the UC"+toAdd->getUcCode()+" is already full\n";
                return {{false,false}};
            }
            else if (newStudent.hasUcClass(*toAdd)){
                cout<<"Failed!Student already has "+toAdd->getUcCode()+" has an UC!\n";
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
                                cout<<"Failed!" +toAdd->getUcCode()+'-'+toAdd->getClassCode()+" overlaps with"+itrUcClasses->getUcCode()+'-'+itrUcClasses->getClassCode()+"\n";
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

bool Request::checkUnbalance(vector<UcClass> ucClasses,UcClass ucClass, int type)  {
    int index=findUc(ucClass.getUcCode(),ucClasses);
    bool cond=false;
    int numberStudents=ucClass.getNumberOfStudents();
    while(ucClasses[index].getUcCode()==ucClass.getUcCode()){
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