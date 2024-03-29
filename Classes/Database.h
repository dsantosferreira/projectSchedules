#ifndef PROJETO_SCHEDULE_DATABASE_H
#define PROJETO_SCHEDULE_DATABASE_H

#include "Student.h"
#include "UcClass.h"
#include "Request.h"
#include <vector>
#include <set>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

class Database {
public:
    Database();
    set<Student> getStudents() const;
    set<Student>* getStudentsReference();
    vector<UcClass> getSchedule() const;
    vector<UcClass>* getScheduleReference();
    vector<Student> searchByUC(std::string ucCode)const;
    vector<Student> searchByUcClass(UcClass ucClass)const;
    vector<Student> searchByClass(string class_) const;
    void printClassDiagramSchedule(string classCode_)const;
    void printClassGraphicSchedule(string classCode_)const;
    vector<Student> searchMoreThan(int n) const;
    vector<Student> searchByYear(int year)const;
    vector<Student> searchByYearAdmission(int year) const;
    vector<UcClass> allUcs() const;
    int findUc(string ucCode)const;
    void handleRequests();
    void pushRequestToQueue(Request request);
    queue<Request> getMainRequest() const;
    queue<Request> getArchiveRequest() const;
    void updateStudents()const;
    void updateArchive();
    void addStudent(int studentCode, string studentName);
    void removeStudent(int studentCode);
    vector<Student> allStudents() const;

private:
    void readArchive();
    void readUcClasses();
    void readUcClassesFile();
    void readStudentClassesFile();
    UcClass* findUcClass(string ucCode, string classCode);
    set<Student> students;
    vector<UcClass> schedule;
    queue<Request> mainQueue;
    queue<Request> archive;
};


#endif //PROJETO_SCHEDULE_DATABASE_H
