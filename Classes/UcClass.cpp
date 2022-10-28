#include "UcClass.h"

UcClass::UcClass(std::string ucCode_, std::string classCode_, list<Lecture> lectures_) {
    this->ucCode=ucCode_;
    this->classCode=classCode_;
    this->lectures=lectures_;
}

bool UcClass::operator<(const UcClass secondUcClass) const {
    if (this->ucCode < secondUcClass.ucCode)
        return true;
    else if (this->ucCode == secondUcClass.ucCode) {
        if (this->classCode < secondUcClass.classCode)
            return true;
        return false;
    }
    else
        return false;
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

void UcClass::addALecture(Lecture aLecture) {
    lectures.push_back(aLecture);
}