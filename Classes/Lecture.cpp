#include "Lecture.h"

Lecture::Lecture(std::string weekDay_, float start_, float duration_, std::string type_) {
    pair<float, float> startEnd(start_, start_ + duration_);
    this->weekDay = weekDay_;
    this->lectureTime = startEnd;
    this->type = type_;
}