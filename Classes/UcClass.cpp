#include "UcClass.h"

UcClass::UcClass(std::string ucCode_, std::string classCode_, list<Lecture> lectures_) {
    ucCode = ucCode_;
    classCode = classCode_;
    lectures = lectures_;
}

string UcClass::getUcCode() const {
    return ucCode;
}

string UcClass::getClassCode() const {
    return classCode;
}

list<Lecture> UcClass::getLectures() const {
    return lectures;
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