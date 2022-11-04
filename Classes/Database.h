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
    void setStudents(set<Student> students_);
    void setSchedule(vector<UcClass> schedule_);
    UcClass* getUcClass(int i);
    bool searchByUC(std::string ucCode)const;
    bool searchByUcClass(UcClass ucClass)const;
    bool searchByClass(string class_) const;
    bool searchStudent(int upCode)const;
    void printClassDiagramSchedule(string classCode_)const;
    void printClassGraphicSchedule(string classCode_)const;
    bool searchMoreThan(int n) const;
    bool searchByYear(int year)const;
    bool searchByYearAdmission(int year) const;
    int getNumberUcClasses() const;
    int findUc(string ucCode)const;
    void handleRequests();
    void pushRequestToQueue(Request request);
    queue<Request> getMainRequest() const;
    queue<Request> getArchiveRequest() const;
    void updateStudents()const;
    void updateArchive();
    void addStudent(int studentCode, string studentName);
    void removeStudent(int studentCode);

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
