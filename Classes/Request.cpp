#include <limits>
#include <set>
#include "Request.h"
#include "Menu.h"
#include "Database.h"

Request::Request(Database &database, char option) {
    set<Student> students = database.getStudents();
    vector<UcClass> ucClasses = database.getSchedule();
    int studentCode, ucIndex;
    string subMenuOption;
    vector<string> buttons;
    set<string> alreadySeen;
    list<UcClass> ucClassesList;

    system("clear");
    cout << "Write your student code: ";
    cin >> studentCode;
    while (cin.fail() || students.find(Student("", studentCode, ucClassesList)) == students.end()) {
        cout << endl << "Please insert a valid student code: ";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin >> studentCode;
    }
    this->student = *(students.find(Student("", studentCode, ucClassesList)));
    ucClassesList = this->student.getUcClasses();
    switch (option) {
        case '1':
        {
            Menu menu = Menu(ucClassesList);
            menu.draw();
            while(true) {
                cin >> subMenuOption;
                if (subMenuOption.size() == 1 && isdigit(subMenuOption[0]))
                    if (stoi(subMenuOption) >= 1 && stoi(subMenuOption) <= ucClassesList.size())
                        break;
                cout << "Please insert a valid option: ";
            }
            auto itr = ucClassesList.begin();
            advance(itr, stoi(subMenuOption) - 1);
            UcClass* toRemove = &(*itr);
            pair<UcClass*, UcClass*> p(toRemove, nullptr);
            this->removeAdd.push_back(p);
            break;
        }
        case '2':
        {
            Menu menu = Menu(ucClasses);
            buttons = menu.getButtons();
            menu.draw();
            while(true) {
                cin >> subMenuOption;
                if (subMenuOption.size() == 1 && isdigit(subMenuOption[0]))
                    if (stoi(subMenuOption) >= 1 && stoi(subMenuOption) <= 9)
                        break;
                else if (subMenuOption.size() == 2 && isdigit(subMenuOption[0]) && isdigit(subMenuOption[1]))
                    // FIX BOUNDARIES
                    if (stoi(subMenuOption) >= 10 && stoi(subMenuOption) <= 99)
                        break;
                cout << "Please insert a valid option: ";
            }
            buttons.clear();
            string aUcCode = buttons[stoi(subMenuOption) - 1];
            ucIndex = database.findUc(aUcCode);
            for (int i = ucIndex; ucClasses[i].getUcCode() == aUcCode; i++) {
                buttons.push_back(ucClasses[i].getClassCode());
            }
            menu.setButtons(buttons);
            menu.draw();
            while(true) {
                cin >> subMenuOption;
                if (subMenuOption.size() == 1 && isdigit(subMenuOption[0]))
                    if (stoi(subMenuOption) >= 1 && stoi(subMenuOption) <= 9)
                        break;
                    else if (subMenuOption.size() == 2 && isdigit(subMenuOption[0]) && isdigit(subMenuOption[1]))
                        // FIX BOUNDARIES
                        if (stoi(subMenuOption) >= 10 && stoi(subMenuOption) <= 99)
                            break;
                cout << "Please insert a valid option: ";
            }
            UcClass* toAdd = &ucClasses[ucIndex + stoi(subMenuOption) - 1];
            pair<UcClass*, UcClass*> p(nullptr, toAdd);
            this->removeAdd.push_back(p);
            break;
        }
    }
    /*
     * PARA ADICIONAR MENU PARA UCS E DEPOIS PARA TURMAS CORRESPONDENTES
     * PARA ALTERAR MENU SÓ PARA AS TURMAS DA UC PARA REMOVER
     */
}

void Request::handleRequest() {
    Student newStudent(student);
    list<UcClass> stuUcClasses = newStudent.getUcClasses();
    UcClass *toRemove, *toAdd;
    list<Lecture> toAddLectures;
    int posForAdding;
    bool Acceptable = true;

    for (auto itr = removeAdd.begin(); itr != removeAdd.end(); itr++) {
        //toRemove = itr->first;
        toAdd = itr->second;
        toAddLectures = toAdd->getLectures();
        posForAdding = 0;

        if (toRemove != nullptr) {
            // Check if Student has UcClass
            //stuUcClasses.erase(toRemove);
        }

        if (toAdd != nullptr) {
            if (toAdd->getNumberOfStudents() >= toAdd->getCapacity()) {
                Acceptable = false;
            }
            else if (abs(toAdd->getNumberOfStudents() + 1 - (toRemove->getNumberOfStudents() - 1)) > 3) {
                Acceptable = false;
            }
            else {
                for (auto itrUcClasses = stuUcClasses.begin(); itrUcClasses != stuUcClasses.end(); itrUcClasses++) {
                    list<Lecture> lectures = itrUcClasses->getLectures();
                    if (*itrUcClasses < *toAdd)
                        posForAdding++;
                    for (auto itrLectures = lectures.begin(); itrLectures != lectures.end(); itrLectures++) {
                        for (auto itrToAddLectures = toAddLectures.begin(); itrToAddLectures != toAddLectures.end(); itrToAddLectures++) {
                            if (itrToAddLectures->Overlaps(*itrLectures) && !itrToAddLectures->isOverlapableWith(*itrLectures)) {
                                Acceptable = false;
                            }
                        }
                    }
                }
            }
        }
        if (Acceptable) {
            newStudent.addUcClass(*toAdd, posForAdding);
            toRemove->setNumberOfStudents(toRemove->getNumberOfStudents() - 1);
            toAdd->setNumberOfStudents(toAdd->getNumberOfStudents() + 1);
        }
        else
            break;
    }
    //Change the students set
    if (Acceptable) {
        //remover do set o estudante original e meter o novo
    }
}