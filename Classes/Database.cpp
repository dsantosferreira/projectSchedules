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

set<Student>* Database::getStudentsReference() {
    return &students;
}

vector<UcClass>* Database::getScheduleReference() {
    return &schedule;
}

UcClass* Database::getUcClass(int i) {
    return &schedule[i];
}

void Database::setStudents(set<Student> students_) {
    this->students = students_;
}

void Database::setSchedule(vector<UcClass> schedule_) {
    this->schedule = schedule_;
}

int Database::getNumberUcClasses() const {
    int counter = 0;
    set<string> alreadySeen;
    for(UcClass ucClass : schedule) {
        string ucCode = ucClass.getUcCode();
        if (alreadySeen.find(ucCode) == alreadySeen.end()) {
            alreadySeen.insert(ucCode);
            counter++;
        }
    }
    return counter;
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
    ifstream in("../files/students_classes.csv");
    string stuCode, stuName, ucCode, classCode, aLine, prevStuCode = "";
    list<UcClass> emptyList;
    Student currStudent;
    UcClass* aUcClass = NULL;

    int currStudentsUC;


    getline(in, aLine);
    while(getline(in, aLine)) {
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
        currStudentsUC = aUcClass->getNumberOfStudents();
        aUcClass->setNumberOfStudents(++currStudentsUC);
        aUcClass->setCapacity(currStudentsUC);
        currStudent.addUcClass(aUcClass, currStudent.getUcClasses().size());
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

int Database::findUc(string ucCode) {
    int low = 0, high = schedule.size() - 1;
    int middle;
    while (low != high) {
        middle = low + (high - low)/2;
        if (schedule[middle].getUcCode() >= ucCode) {
            high = middle;
        }
        else {
            low = middle + 1;
        }
    }
    return low;
}

bool Database::searchByUC(std::string ucCode_)const{
    bool cond=false;
    for(Student student_ : students){
        if(student_.hasUc(ucCode_)){
            student_.print();
            cond=true;
        }
    }
    if(cond) return cond;
    else{
        cout<<"No student belonging to "+ ucCode_+" was found\n";
        return false;
    }
}
bool Database::searchByUcClass(UcClass ucClass) const {
    bool cond=false;
    for(Student student : students){
        if(student.hasUcClass(ucClass)){
            student.print();
            cond =true;
        }
    }
    if(cond) return cond;
    else cout<<"No student belonging to the class "+ucClass.getClassCode()+" of "+ucClass.getUcCode()+'\n';
}

bool Database::searchStudent(int upCode) const {
    list<UcClass> empty;
    auto itr= this->students.find(Student("Irrelevant",upCode,empty));
    if(itr!=this->students.end()) {itr->print(); return true;}
    else cout<<"Student not found\n";
    return false;
}
void Database::printClassDiagramSchedule(string classCode_)const{
    cout<<classCode_<<":\n";
    for(UcClass ucClass_:schedule){
        if(ucClass_.getClassCode()==classCode_) ucClass_.print();
    }

}

void Database::printClassGraphicSchedule(std::string classCode_) const {
    cout << classCode_ + " schedule\n";
    string schedule_ = " ________________________________________________________________________________________\n"
                       "|     Hour    |    Monday    |   Tuesday    |   Wednesday  |   Thursday   |    Friday    |\n"
                       "|________________________________________________________________________________________|\n";


    vector<string> periodOfTime;/*this vector will contain what has to be printed in each period of time
                                (24 periods of time each day 5 days of the week and each period has a sperating line so times two)*/
    for (int i = 0; i < 24 * 5 * 2; i += 2) {
        periodOfTime.push_back("              |");
        periodOfTime.push_back("______________|");
    } //Initializing the vector with alternating lines;

    for (UcClass ucClass_: schedule) {
        if (ucClass_.getClassCode() == classCode_) {
            for (Lecture lecture: ucClass_.getLectures()) {
                string weekday = lecture.getWeekDay();
                int weekDayPosition;
                if (weekday == "Monday") weekDayPosition = 0;
                else if (weekday == "Tuesday") weekDayPosition = 1;
                else if (weekday == "Wednesday") weekDayPosition = 2;
                else if (weekday == "Thursday") weekDayPosition = 3;
                else weekDayPosition = 4;
                float duration = lecture.getDuration();

                int lectureStartPosition = 24 * 2 * weekDayPosition + (lecture.getLectureTime().first - 8.00) * 4;
                periodOfTime[lectureStartPosition] = " " + ucClass_.getUcCode() + "(" + lecture.getType() + ")";
                if (lecture.getType().length() == 1) periodOfTime[lectureStartPosition] += "  |";
                else periodOfTime[lectureStartPosition] += " |";
                periodOfTime[++lectureStartPosition] = "   " + ucClass_.getClassCode() + "    |";
                duration -= 0.5;
                while (duration > 0.5) {
                    duration -= 0.5;
                    periodOfTime[++lectureStartPosition] = "              |";
                    periodOfTime[++lectureStartPosition] = "              |";
                }
                periodOfTime[++lectureStartPosition] = "              |";
            }

        }
    }
        float time = 8.0;
        for (int i = 0; i < 24 * 2; i += 2) {

            if (time < 10 || (time + 0.5 < 10)) schedule_ += "|  ";
            else schedule_ += "| ";
            schedule_ += to_string((int) time) + ':' + to_string((int) ((time - (int) time) * 6)) + "0-";
            time += 0.5;
            schedule_ += to_string((int) time) + ':' + to_string((int) ((time - (int) time) * 6)) + "0";
            if (time < 10 && (time - 0.5 < 10)) schedule_ += ' ';
            schedule_ += " |" + periodOfTime[i] + periodOfTime[48 * 1 + i] + periodOfTime[48 * 2 + i] +
                         periodOfTime[48 * 3 + i] + periodOfTime[48 * 4 + i] + '\n';
            schedule_ += "|_____________|" + periodOfTime[i + 1] + periodOfTime[48 * 1 + i + 1] +
                         periodOfTime[48 * 2 + i + 1] + periodOfTime[48 * 3 + i + 1] + periodOfTime[48 * 4 + i + 1] +
                         '\n';
        }

    
    cout << schedule_;
}
bool Database::searchByClass(std::string class_) const {
    bool cond=false;
    for(Student student : students){
        if(student.hasClass(class_)){
            student.print();
            cond=true;
        }
    }
    if(cond) return cond;
    else{
        cout<<"No student belonging to "+ class_+" was found\n";
        return false;
    }
}

/*bool*/ void Database::searchByYear(int year) const{
    //bool flag = false;
    for (Student student : students){
        int maxYear = 1;
        int classYear;
        for(UcClass ucclass : student.getUcClasses()){
            string classCode = ucclass.getClassCode();
            classYear = classCode.at(0) - '1' + 1;
            if(classYear > maxYear){
                maxYear = classYear;
            }
        }
        if(maxYear == year){
            student.print();
            //flag = true;
        }
    }
    //return flag;
 }

/*bool*/ void Database::searchByYearAdmission(int year) const{
    //bool flag = false;
    for (Student student : students){
        int upCode = student.getStudentCode();
        int studentYear = upCode/100000;
        if(studentYear == year){
            student.print();
            //flag = true;
        }
    }
    //return flag;
}

void Database::pushRequestToQueue(Request request) {
    mainQueue.push(request);
}

void Database::handleRequests() {
    for (int i = 0; i < schedule.size(); i++) {
        schedule[i].setCapacity(50);
    }
    int size = mainQueue.size();
    bool addStudent;
    list<pair<bool, bool>> changeNumberStudents;
    list<pair<UcClass, UcClass*>> ucPairs;
    pair<bool, bool> aChange;

    // Goes through all requests
    for (int i = 0; i < size; i++) {
        addStudent = true;
        Request request = mainQueue.front(); // Loads next request
        ucPairs = request.getPairs();
        auto itrR = ucPairs.begin();
        changeNumberStudents = request.handleRequest(&students,schedule);
        if(changeNumberStudents.size()==0)
            addStudent=false;

        for (auto itrC = changeNumberStudents.begin(); itrC != changeNumberStudents.end(); itrC++) {
            aChange = *itrC;
            if (aChange.first == false && aChange.second == false) {
                addStudent = false;
                break;
            }
            if (aChange.first == true) {
                UcClass removed = (*itrR).first;
                UcClass* originalUc = findUcClass(removed.getUcCode(), removed.getClassCode());
                originalUc->setNumberOfStudents(originalUc->getNumberOfStudents() - 1);
            }
            if (aChange.second == true) {
                UcClass* added = (*itrR).second;
                UcClass* originalUc = findUcClass(added->getUcCode(), added->getClassCode());
                originalUc->setNumberOfStudents(originalUc->getNumberOfStudents() + 1);
            }
            itrR++;
        }
        if (addStudent) {
            Student studentToAdd = request.getStudent();
            auto itr = students.find(studentToAdd);
            students.erase(itr);
            students.insert(studentToAdd);
        }
        mainQueue.pop();
    }
}
