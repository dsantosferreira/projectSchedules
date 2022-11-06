//
// Created by franciscocardoso on 04-11-2022.
//

#include "Request.h"

Request::Request(Student student_, list<pair<UcClass, UcClass>> pairs_) {
    this->student=student_;
    this->removeAdd=pairs_;
}
list<pair<UcClass,UcClass>> Request::getPairs() const {
    return this->removeAdd;
}
Student Request::getStudent()const{
    return this->student;
}

bool Request::handleRequest(set<Student>* students, vector<UcClass>* ucClasses) {

    vector<UcClass> ucClassesCopy=*ucClasses;
    auto newStudentItr = (*students).find(this->student);// real student
    Student newStudent = *newStudentItr;// aux student
    list<UcClass> stuUcClasses;//ucClasses da copia
    list<Lecture> toAddLectures;//aux recebe as aulas da ucClass em cima
    int posForAdding;//posição onde adicionar

    /**Removing the ucClasses*/
    for(pair<UcClass,UcClass> p:removeAdd){
        string uc=p.first.getUcCode();
        if(uc!="-1"){
            if(student.hasUc(uc)){
                if (!checkUnbalance(ucClassesCopy, p.first, 0)) {
                    newStudent.removeUcClass(p.first);
                    int index= findUc(uc,ucClassesCopy);
                    ucClassesCopy[index].setNumberOfStudents(ucClassesCopy[index].getNumberOfStudents()-1);/**decreasing the number of students in a uc class*/

                } else {
                    cout<<"Failed!Change would case unbalance!";
                    return false;
                }
            }else
                cout<<"Failed! Student does not have "+uc+" has an UC, thus it is impossible to remove!";
                return false;
        }

        }

    /**Adding the UcClasses*/
    for(pair<UcClass,UcClass> p:removeAdd){
        string uc=p.second.getUcCode();
        string class_=p.second.getClassCode();
        int index= findUc(uc,ucClassesCopy);
        UcClass ucClassToAdd=ucClassesCopy[index];
        if(uc!="-1"){
            if(!student.hasUc(uc)){
                if (checkUnbalance(ucClassesCopy, p.second, 1)) {
                    cout<<"Failed!Change would case unbalance!";
                    return false;
                }
                if(ucClassToAdd.getNumberOfStudents()>=ucClassToAdd.getCapacity()){
                    cout<<"Failed! The Class "+class_+" in the UC "+uc+" is already full!";
                    return false;
                }else{
                    for(UcClass ucClass:newStudent.getUcClasses() ){
                        if(ucClassToAdd<ucClass) {
                            posForAdding++;
                        }
                        for(Lecture lecture:ucClass.getLectures()){
                            for(Lecture lectureToAdd:ucClassToAdd.getLectures()){
                                if(lectureToAdd.isOverlapableWith(lecture)){
                                    cout<<"Failed!"+ucClassToAdd.getUcCode()+'-'+ucClassToAdd.getClassCode()+" lectures would overlap with"+
                                    ucClass.getUcCode()+'-'+ucClass.getClassCode()+" lectures!";
                                    return false;
                                }
                            }
                        }
                    }
                    newStudent.addUcClass(ucClassToAdd,posForAdding);
                    ucClassesCopy[index].setNumberOfStudents(ucClassesCopy[index].getNumberOfStudents()-1);/**Adding one to the number of students in UcClass*/

                }

            }else
                cout<<"Failed! Student already has "+uc+" has an UC!";
            return false;
        }
    }

    this->student=newStudent;
    *ucClasses=ucClassesCopy;
    students->erase(newStudentItr);
    students->insert(this->student);
    return true;
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

bool Request::checkUnbalance(vector<UcClass> ucClasses, UcClass ucClass, int type)  {
    int index=findUc(ucClass.getUcCode(),ucClasses);
    bool cond=false;
    int numberStudents=ucClass.getNumberOfStudents();
    if(type==0) numberStudents--;
    else numberStudents++;
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
