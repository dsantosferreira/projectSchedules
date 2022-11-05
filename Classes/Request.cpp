//
// Created by franciscocardoso on 04-11-2022.
//

#include "Request.h"

Request::Request(Student student_, list<pair<UcClass, UcClass>> pairs_) {
    this->student=student_;
    this->pairs=pairs_;
}
list<pair<UcClass,UcClass>> Request::getPairs() const {
    return this->pairs;
}
Student Request::getStudent()const{
    return this->student;
}

bool Request::handleRequest(set<Student>* students, vector<UcClass> ucClasses) {
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
                    return {};
                }
            }else
                return {};
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
                return {{false,false}};
            }
            else if (newStudent.hasUcClass(*toAdd))
                return {};
            else {
                toAdd->setNumberOfStudents(toAdd->getNumberOfStudents() + 1);
                if (checkUnbalance(ucClasses, *toAdd, 1)) {
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
    return true;
}

bool Request::checkUnbalance(vector<UcClass> ucClasses, UcClass ucClass, int type)  {
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
