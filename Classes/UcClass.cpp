#include "UcClass.h"

UcClass::UcClass() {}

UcClass::UcClass(std::string ucCode_, std::string classCode_, list<Lecture> lectures_) {
    this->ucCode=ucCode_;
    this->classCode=classCode_;
    this->lectures=lectures_;
    this->numberOfStudents = 0;
    this->capacity = 0;
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

int UcClass::getNumberOfStudents() const {
    return numberOfStudents;
}

int UcClass::getCapacity() const {
    return capacity;
}

void UcClass::setNumberOfStudents(int newNumberOfStudents) {
    numberOfStudents = newNumberOfStudents;
}

void UcClass::setCapacity(int newCapacity) {
    capacity = newCapacity;
}

void UcClass::addALecture(Lecture aLecture) {
    lectures.push_back(aLecture);
}

void UcClass::print() const {
    cout<<'\t'<<this->getUcCode()<<":\n";
    for(Lecture lecture_: lectures){
            cout<<"\t\t -> Weekday:"+lecture_.getWeekDay()+"|Start:"<<(int)lecture_.getLectureTime().first
                <<':'<< (lecture_.getLectureTime().first-(int)lecture_.getLectureTime().first)*6<<"0|End:"<<(int)lecture_.getLectureTime().second
                <<':'<< (lecture_.getLectureTime().second-(int)lecture_.getLectureTime().second)*6<<"0|Type:"+lecture_.getType()<<endl;
        }


}