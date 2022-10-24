#include "UcClass.h"

UcClass::UcClass(std::string ucCode_, std::string classCode_, list<Lecture> lectures_) {
    this->ucCode=ucCode_;
    this->classCode=classCode_;
    this->lectures=lectures_;
}
string UcClass::getUcCode() const {
    return this->ucCode;
}
string UcClass::getClassCode() const {
    return this->classCode;
}

list<Lecture> UcClass::getLectures() const {
    return this->lectures;
}

