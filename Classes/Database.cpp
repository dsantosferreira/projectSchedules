#include "Database.h"
#include <fstream>
#include <sstream>

Database::Database() {
    readUcClasses();
    readUcClassesFile();
}

vector<UcClass> Database::getSchedule() const {
    return schedule;
}

void Database::readUcClasses() {
    vector<UcClass> ucClasses;
    set<UcClass> aux;
    ifstream in("../files/classes.csv");
    string aLine, ucCode, classCode;
    getline(in, aLine);
    while (getline(in, aLine)) {
        list<Lecture> emptyList;
        istringstream inn(aLine);
        getline(inn, classCode, ',');
        getline(inn, ucCode, ',');
        if (ucCode[0] == 'U')
            break;
        aux.insert(UcClass(ucCode, classCode, emptyList));
    }
    for (auto itr = aux.begin(); itr != aux.end(); itr++) {
        schedule.push_back(*itr);
    }
}

void Database::readUcClassesFile() {
    ifstream in("../files/classes.csv");
    string aLine, ucCode, classCode, weekDay, type, startTime, duration;
    getline(in, aLine);
    int i, j, middle;

    while(getline(in, aLine)) {
        istringstream inn(aLine);
        getline(inn, classCode, ',');
        getline(inn, ucCode, ',');
        getline(inn, weekDay, ',');
        getline(inn, startTime, ',');
        getline(inn, duration, ',');
        getline(inn, type, '\r');

        if (ucCode[0] == 'U')
            break;

        i = 0;
        j = schedule.size() - 1;
        while (i <= j) {
            middle = i + (j - i)/2;
            UcClass* curr = &schedule[middle];
            if (ucCode < (*curr).ucCode) {
                j = middle - 1;
            }
            else if (ucCode == (*curr).ucCode) {
                if (classCode == (*curr).classCode) {
                    (*curr).lectures.push_back(Lecture(weekDay, stof(startTime), stof(duration), type));
                    break;
                }
                else if (classCode < (*curr).classCode) {
                    j = middle - 1;
                }
                else {
                    i = middle + 1;
                }
            }
            else {
                i = middle + 1;
            }
        }
    }
}

