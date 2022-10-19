//
// Created by franciscocardoso on 18-10-2022.
//
#include <string>

using namespace std;
#ifndef PROJETO_SCHEDULE_LECTURE_H
#define PROJETO_SCHEDULE_LECTURE_H


class Lecture {
    Lecture(string weekDay_, float start_, int duration, string type_);
    string getWeekDay()const;
    string getType()const;
    pair<float,float> getLectureTime()const;
    int getDuration()const;
    void print()const;


private:
    string weekDay;
    pair<float,float> lectureTime;
    string type;
};


#endif //PROJETO_SCHEDULE_LECTURE_H
