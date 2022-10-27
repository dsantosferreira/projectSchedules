#include "Student.h"

Student::Student(string studentName_, int studentCode_, list<UcClass> ucClasses_){
    this->studentCode=studentCode_;
    this->studentName= studentName_;
    this->ucClasses=ucClasses_;
}
string Student::getStudentname() const {
    return this->studentName;
}
list<UcClass> Student::getUcClasses() const {
    return  this->ucClasses;
}
bool Student::operator<(const Student &student) {
    return this->studentCode < student.studentCode;
}

int Student::getstudentCode() const {
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
