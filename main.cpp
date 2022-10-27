#include <iostream>
#include <fstream>
#include <sstream>
#include "Classes/Database.h"

using namespace std;
int main() {
    Database database;
    vector<UcClass> schedules = database.getSchedule();
    set<Student> students = database.getStudents();


    for (int i = 0; i < schedules.size(); i++) {
        UcClass curr = schedules[i];
        list<Lecture> currList = curr.getLectures();
        cout << curr.getClassCode() <<  ' ' << curr.getUcCode() << ':' << endl;
        for (auto itr = currList.begin(); itr != currList.end(); itr++) {
            cout << '\t' << (*itr).weekDay << ' ' << (*itr).lectureTime.first << ' ' << (*itr).lectureTime.second << ' ' << (*itr).type << endl;
        }
    }

    /*
    for (auto itr = students.begin(); itr != students.end(); itr++) {
        Student aStudent = *itr;
        list<UcClass> ucClasses = aStudent.getUcClasses();
        cout << aStudent.getStudentCode() << ' ' << aStudent.getStudentName() << endl;
        for (auto itrL = ucClasses.begin(); itrL != ucClasses.end(); itrL++) {
            UcClass curr = *itrL;
            list<Lecture> currList = curr.getLectures();
            cout << '\t' << curr.getClassCode() << ' ' << curr.getUcCode() << ':' << endl;
            for (auto itr = currList.begin(); itr != currList.end(); itr++) {
                cout << "\t\t" << (*itr).weekDay << ' ' << (*itr).lectureTime.first << ' ' << (*itr).lectureTime.second
                     << ' ' << (*itr).type << endl;
            }
        }
    }*/
    return 0;
}
