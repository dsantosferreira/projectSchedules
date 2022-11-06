#include "Database.h"

#include <iostream>

/**
 * Constructs a database by reading the necessary files (classes file, students file and the archive)
 * @see readUcClasses()
 * @see readUcClassesFile()
 * @see readStudentClassesFile()
 * @see readArchive()
 * @brief Default constructor
 */
Database::Database() {
    readUcClasses();
    readUcClassesFile();
    readStudentClassesFile();
    readArchive();
}

/**
 * @brief Getter of main queue for requests
 * @return queue of requests
 */
 queue<Request> Database::getMainRequest() const {
    return this->mainQueue;
}

/**
 * @brief Getter of archive queue for requests
 * @return queue of requests
 */
queue<Request> Database::getArchiveRequest() const {
    return this->archive;
}

/**
 * @brief Getter for all the classes
 * @return vector of all the classes
 */
vector<UcClass> Database::getSchedule() const {
    return schedule;
}

/**
 * @brief Getter for all the students
 * @return set of all the students
 */
set<Student> Database::getStudents() const {
    return students;
}

/**
 * Getter of the set of all students by reference
 * @return pointer to set of all students
 */
set<Student>* Database::getStudentsReference() {
    return &students;
}

/**
 * Getter of the vector of classes by reference
 * @return pointer to vector of all classes
 */
vector<UcClass>* Database::getScheduleReference() {
    return &schedule;
}

/**
 * Complexity: O(1)
 * @brief Getter for a particular class
 * @param i - index in the classes vector
 * @return pointer to the ucClass
 */
UcClass* Database::getUcClass(int i) {
    return &schedule[i];
}

/**
 * @brief Setter for the set of students
 * @param students_ - set of students
 */
void Database::setStudents(set<Student> students_) {
    this->students = students_;
}

/**
 * @brief Setter for classes vector
 * @param schedule_ - classes vector
 */
void Database::setSchedule(vector<UcClass> schedule_) {
    this->schedule = schedule_;
}

/**
 * Requests that don't have a class to remove or add reads "-" in the space of the class in the file, initializing each request
 * with a dummy class if necessary \n
 * Complexity: O(l*(log(s) + w)) being l the number of lines of the file, s the number of student in the set of students
 * and w the number of words in each line of the file
 * @brief Reads the archive file and initializes its queue
 */
void Database::readArchive() {
    list<pair<UcClass, UcClass*>> pairs;
    ifstream file("../files/archive.csv");
    string line;
    UcClass ucClass1, *ucClass2;
    string studentCode, ucCode1, classCode1, ucCode2, classCode2;
    while(getline(file,line)){
        istringstream words(line);
        getline(words,studentCode,',');
        Student student = *(students.find(Student("Irrelevant", stoi(studentCode), {})));
        while(!words.eof()){
            getline(words, ucCode1, ',');
            getline(words, classCode1, ',');
            getline(words, ucCode2, ',');
            getline(words, classCode2, ',');
            if (ucCode1 == "-")
                ucClass1 = UcClass("-1", "-1", {});
            else
                ucClass1 = *(findUcClass(ucCode1, classCode1));
            if (ucCode2 == "-")
                ucClass2 = nullptr;
            else
                ucClass2 = findUcClass(ucCode2, classCode2);
            pairs.push_back({ucClass1, ucClass2});
        }
        Request request(student, pairs);
        archive.push(request);
    }
}

/**
 * Complexity: O(m + n) being m the number of lines of the file and n the number of classes
 * @brief Reads the classes file to create an ordered vector of classes without the lectures
 */
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

/**
 * Complexity: O(m * log(n)) being m the number of lines of the file and n the number of classes
 * @see findUcClass()
 * @brief Reads the classes file to create the lectures and insert them in each corresponding class
 */
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

/**
 * Besides adding the classes to each student, this function sets the correct capacity and current number of students of
 * each class \n
 * Complexity: O(m * log(n)) being m the number of lines of the file and n the number of classes in the classes vector
 * @brief Reads the students file and creates the students set of the database
 */
void Database::readStudentClassesFile() {
    ifstream in("../files/students_classes.csv");
    string stuCode, stuName, ucCode, classCode, aLine, prevStuCode = "";
    list<UcClass> emptyList;
    Student currStudent;
    UcClass* aUcClass = NULL;
    int maxCapacity=0;
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
        if(currStudentsUC>maxCapacity) maxCapacity=currStudentsUC;
        aUcClass->setCapacity(currStudentsUC);
        currStudent.addUcClass(aUcClass, currStudent.getUcClasses().size());
        prevStuCode = stuCode;
    }
    students.insert(currStudent);
    for(UcClass &ucClass_: schedule){
        ucClass_.setCapacity(maxCapacity);
    }

}

/**
 * This function uses binary search in the vector to search for the desired class efficiently \n
 * Complexity: O(log(n)) being n the number of classes in the classes vector \n
 * @brief Finds a certain class given its ucCode and classCode as input
 * @param ucCode - ucCode of the class to find
 * @param classCode - classCode of the class to find
 * @return pointer to the class that was found
 */
UcClass* Database::findUcClass(string ucCode, string classCode) {
    int i, j, middle;
    i = 0;
    j = schedule.size() - 1;
    UcClass* curr;
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
return curr;
}

/**
 * This function used a lower bound search (similar to binary search) to search for the first class of the desired
 * curricular unit. It is important to then traverse every class of a certain curricular unit
 * Complexity: O(log(n)) being n the number of classes in the classes vector
 * @brief Finds the first class from the curricular unit that is to be found given its ucCode as input
 * @param ucCode - ucCode of the curricular unit to be found
 * @return The index of the first occurrence of the curricular unit in the vector in the vector
 */
int Database::findUc(std::string ucCode)const {
    int begin=0, end= this->schedule.size()-1;
    int middle;
    while(begin<end){
        middle=begin+(end-begin)/2;
        if(schedule[middle].getUcCode()>=ucCode) end=middle;
        else begin=middle+1;

    }
    return begin;
}

/**
 * Given the classCode of the class, this function calls the function that prints the lectures of a class \n
 * Complexity: O(n) being n the number of classes in the classes vector
 * @brief Prints a class' schedule in the form of a diagram
 * @see UcClass::print()
 * @param classCode_ string with a class code
 */
void Database::printClassDiagramSchedule(string classCode_)const{
    cout<<classCode_<<":\n";
    for(UcClass ucClass_:schedule){
        if(ucClass_.getClassCode()==classCode_) ucClass_.print();
    }

}

/**
 * Complexity: O(m*n) being m the number of classes in the classes vector and n the number of lectures in each of the classes
 * @brief Print the class schedule in a more graphical structure similar to a timetable
 * @param classCode_ - classCode of the class
 */
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

/**
 * Complexity: O(m*n) being m the number of student in the set of students and n the numbers of classes each student is in
 * @see Student::hasUcClass()
 * @brief Searches students belonging to a class of a particular curricular unit
 * @param ucClass UcClass
 * @return vector of students in the class given as input
 */
vector<Student> Database::searchByUcClass(UcClass ucClass) const {
    vector<Student> result;
    for(Student student : students){
        if(student.hasUcClass(ucClass)){
            result.push_back(student);
        }
    }
    if(result.empty()) cout<<"No student belonging to the class "+ucClass.getClassCode()+" of "+ucClass.getUcCode()+'\n';
    return result;
}

/**
 * Complexity: O(n) being n the number of students in the set of students
 * @brief Search for a Student given its upCode
 * @param upCode - integer with the student's upCode
 * @return true if the student exists, false otherwise
 */
bool Database::searchStudent(int upCode) const {
    list<UcClass> empty;
    auto itr= this->students.find(Student("Irrelevant",upCode,empty));
    if(itr!=this->students.end()) {itr->print(); return true;}
    else cout<<"Student not found\n";
    return false;
}

/**
 * Complexity: O(m * n) being m the number of students in the set of students and n the number of classes the student is in
 * @brief Search Students of a curricular unit
 * @param ucCode_ - ucCode of the curricular unit
 * @return vector of students in the curricular unit
 */
vector<Student> Database::searchByUC(string ucCode_)const{
    vector<Student> result;
    for(Student student : students){
        if(student.hasUc(ucCode_)){
            result.push_back(student);
        }
    }
    if(result.empty()) cout<<"No student belonging to "+ ucCode_+" was found\n";
    return result;
}

/**
 * Complexity: O(m * n) being m the number of students in the set of students and n the number of classes that student is in
 * @brief Search students of a class
 * @param class_ - classCode of the class
 * @return vector of student that are in the class
 */
vector<Student> Database::searchByClass(string class_) const {
    vector<Student> result;
    for(Student student : students){
        if(student.hasClass(class_)){
            result.push_back(student);
        }
    }
    if(result.empty()) cout<<"No student belonging to "+ class_+" was found\n";
    return result;
}

/**
 * Complexity: O(n) being n the number of students in the set of students
 * @brief Search students with more than n curricular units
 * @param n - integer with the minimum of curricular units the student should have
 * @return vector of students that have n or more curricular units
 */
vector<Student> Database::searchMoreThan(int n) const {
    vector<Student> result;
    for (Student student: students) {
        if (student.getStudentName() == "Manuel Anibal Jose Anibal")
            cout << student.getUcClasses().size() << endl;
        if (student.getUcClasses().size() >= n) {
            result.push_back(student);
        }
        if (result.empty()) cout << "No student with " << n << " UCs or more\n";
    }
    return result;
}

/**
 * Complexity: O(m * n) being m the numbers of students in the set of students and n the numebrs of classes the student is in
 * @brief Search students of an academic year
 * @param year - integer with an academic year
 * @return vector of students that are enrolled in a class from the nth year
 */
vector<Student> Database::searchByYear(int year) const{
    vector<Student> result;
    for (Student student : students){
        int maxYear = 1;
        int classYear;
        for(UcClass ucClass : student.getUcClasses()){
            string classCode = ucClass.getClassCode();
            classYear = classCode.at(0) - '1' + 1;
            if(classYear > maxYear){
                maxYear = classYear;
            }
        }
        if(maxYear == year){
            result.push_back(student);
        }
    }
    if(result.empty()) cout << "No student in the " << year << " year\n";
    return result;
}

/**
 * Complexity: O(n) being n the number of students in the set of students
 * @brief Search Students who started studying in a certain year
 * @param year - integer with the year
 * @return vector of students that started sutdying in the year specified
 */
vector<Student> Database::searchByYearAdmission(int year) const{
    vector<Student> result;
    for (Student student : students){
        int upCode = student.getStudentCode();
        int studentYear = upCode/100000;
        if(studentYear == year){
            result.push_back(student);
        }
    }
    if(result.empty()) cout << "No student admitted in " << year << " was found\n";
    return result;
}

/**
 * Complexity: O(n) being n the number of students in the set of students
 * @brief Returns all the students in a vector
 * @return vector of all the students
 */
vector<Student> Database::allStudents() const{
    vector<Student> result;
    for(Student student : students){
        result.push_back(student);
    }
    return result;
}

/**
 * Complexity: O(n) being n the number of classes in the classes vector
 * @brief Returns all the curricular units
 * @return vector of all the curricular units
 */
vector<UcClass> Database::allUcs() const{
    set<string> alreadySeen;
    vector<UcClass> result;
    for(UcClass ucClass : schedule) {
        if (alreadySeen.find(ucClass.getUcCode()) == alreadySeen.end()){
            alreadySeen.insert(ucClass.getUcCode());
            result.push_back(ucClass);
        }
    }
    return result;
}

/**
 * Complexity: O(n) being n the number of classes in the vector of classes
 * @brief Returns a vector with all the classes
 * @return vector with all the classes
 */
vector<UcClass> Database::allClasses() const {
    set<string> alreadySeen;
    vector<UcClass> result;
    for(UcClass ucClass : schedule){
        if (alreadySeen.find(ucClass.getClassCode()) == alreadySeen.end()){
            alreadySeen.insert(ucClass.getClassCode());
            result.push_back(ucClass);
        }
    }
    return result;
}

/**
 * Pushes a request too the main queue of requests
 * @param request - request to be pushed
 */
void Database::pushRequestToQueue(Request request) {
    mainQueue.push(request);
}

void Database::handleRequests() {
    int sizeMain = mainQueue.size();
    int sizeArchive=archive.size();
    bool addStudent;
    list<pair<bool, bool>> changeNumberStudents;
    list<pair<UcClass, UcClass*>> ucPairs;
    pair<bool, bool> aChange;

    // Goes through all requests
    for (int i = 0; i < sizeMain+sizeArchive ; i++) {
        addStudent = true;
        Request request;
        if(i<sizeArchive){
            request=archive.front();
            archive.pop();
        }
        else {request = mainQueue.front(); mainQueue.pop();}// Loads next request

        ucPairs = request.getPairs();
        auto itrR = ucPairs.begin();
        changeNumberStudents = request.handleRequest(&students,schedule);
        if(changeNumberStudents.size()==0)
            addStudent=false;

        for (auto itrC = changeNumberStudents.begin(); itrC != changeNumberStudents.end(); itrC++) {
            aChange = *itrC;
            if(aChange.first==false && aChange.second==false){
                archive.push(request);
            }
            if (aChange.first == true) {
                UcClass removed = (*itrR).first;
                UcClass* originalUc = findUcClass(removed.getUcCode(), removed.getClassCode());
                originalUc->setNumberOfStudents(originalUc->getNumberOfStudents() - 1);
            }
            itrR++;
        }
        if (addStudent) {
            Student studentToAdd = request.getStudent();
            auto itr = students.find(studentToAdd);
            students.erase(itr);
            students.insert(studentToAdd);
        }

    }
}

/**
 * @brief Adds a student to the set of students
 * @param studentCode - student code of the student to be added
 * @param studentName - student name of the student to be added
 */
void Database::addStudent(int studentCode, string studentName) {
     students.insert(Student(studentName, studentCode, {}));
 }

 /**
  * @brief Removes a student of the set of students
  * @param studentCode -  student code of the student to be removed
  */
void Database::removeStudent(int studentCode) {
     students.erase(Student("Irrelevant", studentCode, {}));
 }

 /**
  * @brief Updates the students file for future use
  */
void Database::updateStudents() const {
     ofstream file("../files/students_classes.csv",ios::trunc);
     file<<"StudentCode,StudentName,UcCode,ClassCode"<<endl;
     for(Student student: students){
        for(UcClass ucClass: student.getUcClasses()){
            file<<student.getStudentCode()<<','<<student.getStudentName()<<','<<ucClass.getUcCode()<<','<<ucClass.getClassCode()<<endl;
        }
     }
     file.close();
 }

void Database::updateArchive() {
     ofstream file("../files/archive.csv",ios::trunc);
     while(!archive.empty()){
         Request request=archive.front();
         archive.pop();
         file<<request.getStudent().getStudentCode();
         for(pair<UcClass,UcClass*> p:request.getPairs()){
             file << ',';
             if(p.first.getUcCode()=="-1"){
                 file<<"-,-";
             }
             else{
                 file<<p.first.getUcCode()<<','<<p.first.getClassCode();
             }
             file<<",";
             if(p.second== nullptr){
                 file<<"-,-";
             }else{
                 file<<p.second->getUcCode()<<','<<p.second->getClassCode();
             }

         }
         file<<endl;

     }
     file.close();
 }