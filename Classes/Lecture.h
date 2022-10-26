#include <string>

using namespace std;
#ifndef PROJETO_SCHEDULE_LECTURE_H
#define PROJETO_SCHEDULE_LECTURE_H


class Lecture {
public:
    Lecture(string weekDay_, float start_, float duration_, string type_);
    string getWeekDay()const;
    string getType()const;
    pair<float,float> getLectureTime()const;
    int getDuration()const;
    void print()const;
    string weekDay;
    pair<float,float> lectureTime;
    string type;



private:
    /*
    string weekDay;
    pair<float,float> lectureTime;
    string type;*/
};


#endif //PROJETO_SCHEDULE_LECTURE_H
