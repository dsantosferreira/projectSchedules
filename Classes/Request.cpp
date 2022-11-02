#include <limits>
#include <set>
#include "Request.h"
#include "Menu.h"

Request::Request(set<Student> students, vector<UcClass> ucClasses, char option) {
    int studentCode;
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
            Menu menu = Menu(ucClassesList);
            menu.draw();

    }
    /*
     * PARA ADICIONAR MENU PARA UCS E DEPOIS PARA TURMAS CORRESPONDENTES
     * PARA ALTERAR MENU SÓ PARA AS TURMAS DA UC PARA REMOVER
     */
}

void Request::handleRequest() {
    Student newStudent(student);
    list<UcClass> stuUcClasses = newStudent.getUcClasses();
    list<UcClass>::iterator toRemove;
    UcClass* toAdd;
    list<Lecture> toAddLectures;
    int posForAdding;
    bool Acceptable = true;

    for (auto itr = removeAdd.begin(); itr != removeAdd.end(); itr++) {
        toRemove = itr->first;
        toAdd = itr->second;
        toAddLectures = toAdd->getLectures();
        posForAdding = 0;

        if (toRemove != stuUcClasses.end()) {
            // Change to indexes
            stuUcClasses.erase(toRemove);
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