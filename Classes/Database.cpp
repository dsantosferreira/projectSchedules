#include "Database.h"

#include <iostream>

Database::Database() {
    readUcClasses();
    readUcClassesFile();
    readStudentClassesFile();
    readArchive();
}

 queue<Request> Database::getMainRequest() const {
    return this->mainQueue;
}

queue<Request> Database::getArchiveRequest() const {
    return this->archive;
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




/**Functionality: Find the lowerbound of an Uc in the vector of UcClasses and return its index
 *
 * Description: This Function is going to receive as parameter a string which will be a UC code, and then will search for the first occurrence of the UC
 * in the vector, returning when finding it the index of that Uc in the vector.
 *
 * @param ucCode string with the code of the UC
 * @return The index of the first occurrence of the Uc in the vector
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

/**Functionality: Print the class schedule in the form of a Diagram
 *
 * Description: This Function will receive as a parameter a string which will have a class code, then it will search for all the lectures of this class and
 * print them with the use of the UcClass method print, forming a pleasant schedule.
 *
 * @param classCode_ string with a class code
 */
void Database::printClassDiagramSchedule(string classCode_)const{
    cout<<classCode_<<":\n";
    for(UcClass ucClass_:schedule){
        if(ucClass_.getClassCode()==classCode_) ucClass_.print();
    }

}

/**Functionality: Print the class schedule in a more graphical way
 *
 * Description: This Function will receive as a parameter a string which will have a class code, then it will search for all the lectures of this class and
 * format them in a string, then printing them forming a pleasant schedule.
 *
 * @param classCode_ string with a class code
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

/**Functionality: search Students belonging to a class of an UC
 *
 * Description:This function will receive as a parameter an UcClass, then it will search for all the Students that belong to the class of that UC
 * displaying them using Student method print. the function will give a warning if no student was found as well as returning false,otherwise it
 * will return true.
 *
 * @param ucClass UcClass
 * @return return false if no student was found and true if at least one student was found
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

/**Functionality: Search for a Student
 *
 * Description: This function will receive as a parameter an int with a up code of a student,then it will search for the Student and display him
 * using Student method print.The function will give a warning if no student was found as well as returning false,otherwise it
 * will return true.
 *
 * @param upCode int with the Students up code
 * @return return false if no student was found and true otherwise
 */
bool Database::searchStudent(int upCode) const {
    list<UcClass> empty;
    auto itr= this->students.find(Student("Irrelevant",upCode,empty));
    if(itr!=this->students.end()) {itr->print(); return true;}
    else cout<<"Student not found\n";
    return false;
}

/**Functionality: Search Students of an UC
 * Description: This function will receive as a parameter a string with an Uc code, then it will search for the Students of that Uc and display them
 * using the Student method print.The function will give a warning if no student was found as well as returning false,otherwise it
 * will return true.
 *
 * @param ucCode_ string with UC code
 * @return return false if no student was found and true otherwise
 */
vector<Student> Database::searchByUC(std::string ucCode_)const{
    vector<Student> result;
    for(Student student : students){
        if(student.hasUc(ucCode_)){
            result.push_back(student);
        }
    }
    if(result.empty()) cout<<"No student belonging to "+ ucCode_+" was found\n";
    return result;
}

/**Function: Search students of a class
 *
 * Description: This function will receive as a parameter a string with an class code, then it will search for the Students of that class and display them
 * using the Student method print.The function will give a warning if no student was found as well as returning false,otherwise it
 * will return true.
 *
 * @param class_ string with class code
 * @return return false if no student was found and true otherwise
 */
vector<Student> Database::searchByClass(std::string class_) const {
    vector<Student> result;
    for(Student student : students){
        if(student.hasClass(class_)){
            result.push_back(student);
        }
    }
    if(result.empty()) cout<<"No student belonging to "+ class_+" was found\n";
    return result;
}


/**Function: Search Students with more than N UCs
 *
 * Description: This function will receive as a parameter an int with a number of minimum UCs the Students should have, then it will search for the
 * Students that met that condition and display them using the Student method print.The function will give a warning if no student was found as well as
 * returning false,otherwise it will return true.
 *
 * @param n int with the minimum of Ucs the Student should have
 * @return return false if no student was found and true otherwise
 */
vector<Student> Database::searchMoreThan(int n) const {
    vector<Student> result;
    for(Student student:students){
        if(student.getUcClasses().size()>=n){
            result.push_back(student);
        }
    }
    if(result.empty()) cout << "No student with " << n << " UCs or more\n";
    return result;
}

/**Functionality: Search Students of an academic year
 *
 * Description: This function will receive as a parameter an int with an academic year, then it will search for the Students which belong to that
 * academic year and display them using the Student method print.The function will return false if no Student was found,otherwise it will return true.
 *
 * @param year int with an academic year
 * @return  return false if no student was found and true otherwise
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

/**Functionality: Search Students who entered in a year
 *
 * Description: This function will receive as a parameter an int with a year, then it will search for the Students which entered the university
 * that year and display them using the Student method print.The function will return false if no Student was found,otherwise it will return true.
 *
 * @param year int with a year
 * @return  return false if no student was found and true otherwise
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

void Database::addStudent(int studentCode, string studentName) {
     students.insert(Student(studentName, studentCode, {}));
 }

void Database::removeStudent(int studentCode) {
     students.erase(Student("Irrelevant", studentCode, {}));
 }

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