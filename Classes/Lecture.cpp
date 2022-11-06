#include <iostream>
#include <string>
#include "Lecture.h"

/**
 * Builds a lecture given its weekday, starting hout, duration and type (P, PL or T)
 * @brief Parameterized constructor
 * @param weekDay_
 * @param start_
 * @param duration_
 * @param type_
 */
Lecture::Lecture(string weekDay_, float start_, float duration_, string type_) {
    this->weekDay = weekDay_;
    this->lectureTime = pair<float, float>(start_,start_ + duration_);
    this->type = type_;
}

/**
 * @brief Getter for the type of lecture
 * @return type of lecture
 */
string Lecture::getType() const {
    return this->type;
}

/**
 * @brief Getter for start and end time of lecture
 * @return pair consisting of start and end time of lecture
 */
pair<float, float> Lecture::getLectureTime() const {
    return this->lectureTime;
}

/**
 * @brief Getter for lecture's duration
 * @return duration of lecture
 */
float Lecture::getDuration() const {
    return this->lectureTime.second - this->lectureTime.first;
}

/**
 * @brief Getter for lecture's weekday
 * @return lecture's weekday
 */
string Lecture::getWeekDay() const {
    return this->weekDay;
}

/**
 * @brief Checks if two lectures overlap
 * @param aLecture - second lecture to be compared with
 * @return true if lectures overlap, flase otherwise
 */
bool Lecture::Overlaps(const Lecture aLecture) const {
    if (this->weekDay == aLecture.weekDay) {
        if (this->lectureTime.first <= aLecture.lectureTime.first && aLecture.lectureTime.first < this->lectureTime.second)
            return true;
        else if (aLecture.lectureTime.first <= this->lectureTime.first && this->lectureTime.first < aLecture.lectureTime.second)
            return true;
    }
    return false;
}

/**
 * @brief Checks if two classes can overlap. Two classes can overlap if they aren't both practical classes
 * @param aLecture - second lecture to be compared
 * @return true if the lectures can overlap, false otherwise
 */
bool Lecture::isOverlapableWith(const Lecture aLecture) const {
    if (this->type.find('P') != string::npos && aLecture.type.find('P') != string::npos)
        return false;
    return true;
}