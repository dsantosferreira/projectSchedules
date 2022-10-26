#include <iostream>
#include <fstream>
#include <sstream>
#include "Classes/Database.h"

using namespace std;
int main() {
    Database database;
    vector<UcClass> schedules = database.getSchedule();
    for (int i = 0; i < schedules.size(); i++) {
        UcClass curr = schedules[i];
        list<Lecture> currList = curr.lectures;
        cout << curr.classCode <<  ' ' << curr.ucCode << ':' << endl;
        for (auto itr = currList.begin(); itr != currList.end(); itr++) {
            cout << '\t' << (*itr).weekDay << ' ' << (*itr).lectureTime.first << ' ' << (*itr).lectureTime.second << ' ' << (*itr).type << endl;
        }
    }
    return 0;
}
