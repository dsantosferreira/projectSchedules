#ifndef PROJETO_SCHEDULE_LECTURE_H
#define PROJETO_SCHEDULE_LECTURE_H

#include <string>
#include <iostream>

using namespace std;

class Lecture {
public:
    Lecture(string weekDay_, float start_, float duration_, string type_);
    string getWeekDay()const;
    string getType()const;

    pair<float,float> getLectureTime()const;
    float getDuration()const;//changed to float because duration is a float
    void print()const;
    bool Overlaps(const Lecture aLecture) const;
    bool isOverlapableWith(const Lecture aLecture) const;
private:
    string weekDay;
    pair<float,float> lectureTime;
    string type;
};


#endif //PROJETO_SCHEDULE_LECTURE_H
