//
// Created by franciscocardoso on 18-10-2022.
//
#include <iostream>
#include <string>
#include "Lecture.h"

Lecture::Lecture(std::string weekDay_, float start_, int duration, std::string type_) {
    this->weekDay = weekDay_;
    this->lectureTime = pair<float, float>(start_,start_ + duration);
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
    cout << this->weekDay << " " << this->lectureTime.first << " " << this->lectureTime.first + this->lectureTime.second << " " << this->type;
}