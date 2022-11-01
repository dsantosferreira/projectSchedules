#include <iostream>
#include <string>
#include "Lecture.h"

Lecture::Lecture(string weekDay_, float start_, float duration_, string type_) {
    this->weekDay = weekDay_;
    this->lectureTime = pair<float, float>(start_,start_ + duration_);
    this->type = type_;
}

string Lecture::getType() const {
    return this->type;
}

pair<float, float> Lecture::getLectureTime() const {
    return this->lectureTime;
}

int Lecture::getDuration() const {
    return this->lectureTime.second - this->lectureTime.first;
}

/*
int Lecture::endTime() const{
    return this->lectureTime.second;
 }
*/

void Lecture::print() const {
    cout << this->weekDay << " " << this->lectureTime.first << " " << this->lectureTime.first + this->lectureTime.second
         << " " << this->type;
}
string Lecture::getWeekDay() const {
    return this->weekDay;
}

bool Lecture::Overlaps(const Lecture aLecture) const {
    if (this->weekDay == aLecture.weekDay) {
        if (this->lectureTime.first <= aLecture.lectureTime.first && aLecture.lectureTime.first < this->lectureTime.second)
            return true;
        else if (aLecture.lectureTime.first <= this->lectureTime.first && this->lectureTime.first < aLecture.lectureTime.second)
            return true;
    }
    return false;
}

bool Lecture::isOverlapableWith(const Lecture aLecture) const {
    if (this->type.find('P') != string::npos && aLecture.type.find('P') != string::npos)
        return false;
    return true;
}