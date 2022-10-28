#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>

Database::Database() {
    readUcClasses();
    readUcClassesFile();
    readStudentClassesFile();
}

vector<UcClass> Database::getSchedule() const {
    return schedule;
}

set<Student> Database::getStudents() const {
    return students;
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
    UcClass* aUcClass = NULL;
    list<Lecture> lectureList;

    getline(in, aLine);

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

        aUcClass = findUcClass(ucCode, classCode);
        aUcClass->addALecture(Lecture(weekDay, stof(startTime), stof(duration), type));
    }
}

void Database::readStudentClassesFile() {
    int counter = 0;
    ifstream in("../files/students_classes.csv");
    string stuCode, stuName, ucCode, classCode, aLine, prevStuCode = "";
    list<UcClass> emptyList;
    Student currStudent;
    UcClass* aUcClass = NULL;

    getline(in, aLine);
    while(getline(in, aLine)) {
        // Read a line
        istringstream inn(aLine);
        getline(inn, stuCode, ',');
        getline(inn, stuName, ',');
        getline(inn, ucCode, ',');
        getline(inn, classCode, '\r');

        if (stuCode != prevStuCode) {
            if (prevStuCode != "") {
                students.insert(currStudent);
            }
            currStudent.setStudentName(stuName);
            currStudent.setStudentCode(stoi(stuCode));
            currStudent.setUcClasses(emptyList);
        }

        aUcClass = findUcClass(ucCode, classCode);
        currStudent.addUcClass(*aUcClass);
        prevStuCode = stuCode;
    }
    students.insert(currStudent);
}

UcClass* Database::findUcClass(string ucCode, string classCode) {
    int i, j, middle;
    i = 0;
    j = schedule.size() - 1;
    while (i <= j) {
        middle = i + (j - i)/2;
        UcClass* curr = &schedule[middle];
        if (ucCode < (*curr).getUcCode()) {
            j = middle - 1;
        }
        else if (ucCode == (*curr).getUcCode()) {
            if (classCode == (*curr).getClassCode()) {
                return curr;
            }
            else if (classCode < (*curr).getClassCode()) {
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
