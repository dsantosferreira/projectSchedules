#include <iostream>
#include "Student.h"

Student::Student() {}

void Student::setStudentCode(int studentCode_) {
    studentCode = studentCode_;
}

void Student::setStudentName(std::string studentName_) {
    studentName = studentName_;
}

void Student::setUcClasses(list<UcClass> ucClasses_) {
    ucClasses = ucClasses_;
}

void Student::addUcClass(UcClass aUcClass) {
    ucClasses.push_back(aUcClass);
}

void Student::print(){
    std::cout << studentName << '|' << studentCode << endl;
}

Student::Student(string studentName_, int studentCode_, list<UcClass> ucClasses_){
    this->studentCode=studentCode_;
    this->studentName= studentName_;
    this->ucClasses=ucClasses_;
}
string Student::getStudentName() const {
    return this->studentName;
}
list<UcClass> Student::getUcClasses() const {
    return this->ucClasses;
}
bool Student::operator<(const Student &student) const {
    return this->studentCode < student.studentCode;
}

int Student::getStudentCode() const {
    return this->studentCode;
}

string Student::classOfUc(string ucCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getUcCode()==ucCode_) return ucClass.getClassCode();
    }
    string s=0;
    return s;
}

string Student::ucOfClass(std::string classCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getClassCode()==classCode_) return ucClass.getUcCode();
    }
    string s=0;
    return s;
}

bool Student::hasClass(string classCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getClassCode()==classCode_) return true;
    }
    return false;
}

bool Student::hasUc(string ucCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getUcCode()==ucCode_) return true;
    }
    return false;
}

bool Student::hasUcClass(UcClass ucClass_) const{
    for(UcClass ucClass : ucClasses){
        if(ucClass.getUcCode()==ucClass_.getUcCode() && ucClass.getClassCode()==ucClass_.getClassCode()){
            return true;
        }
    }
    return false;
}
