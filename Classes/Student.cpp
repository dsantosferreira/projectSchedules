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

list<UcClass> Student::getUcClasses() const {
    return ucClasses;
}

string Student::getStudentName() const {
    return studentName;
}

void Student::addUcClass(UcClass aUcClass) {
    ucClasses.push_back(aUcClass);
}

bool Student::operator<(const Student student) const {
    return this->studentCode < student.studentCode;
}

int Student::getStudentCode() const {
    return this->studentCode;
}