#include "Student.h"

/**
 * Initializes the student's name with an empty string, its code with the value 0 and its classes with an empty list.
 * @brief Student's default constructor
 */
Student::Student() {}

/**
 * Complexity: linear in the number of classes
 * @brief Removes the class given as input from the student's classes.
 * @param aUcClass - class to remove from student
 */
void Student::removeUcClass(UcClass aUcClass) {
    auto itr = ucClasses.begin();
    for (; itr != ucClasses.end(); itr++) {
        if (!(*itr < aUcClass) && !(aUcClass < *itr)) {
            ucClasses.erase(itr);
            break;
        }
    }
}


/**
* @brief Initializes the student's name, student code and classes with the given input
* @brief Student's parameterized constructor
* @param studentName_ - student's name
* @param studentCode_ - student's code
* @param ucClasses_ - student's list of classes
*/
Student::Student(string studentName_, int studentCode_, list<UcClass> ucClasses_){
    this->studentCode=studentCode_;
    this->studentName= studentName_;
    this->ucClasses=ucClasses_;
}

/**
 * @brief Student's copy constructor
 * @param student_ - student to be copied
 */
Student::Student(const Student &student_) {
    this->studentCode = student_.studentCode;
    this->studentName = student_.studentName;
    this->ucClasses = student_.ucClasses;
}

/**
 * Sets the student's code.
 * @param studentCode_ - student's code
 */
void Student::setStudentCode(int studentCode_) {
    studentCode = studentCode_;
}

/**
 * @brief Sets the student's name
 * @param studentName_ - student's name
 */
void Student::setStudentName(string studentName_) {
    studentName = studentName_;
}

/**
 * @brief Sets the student's classes
 * @param ucClasses_ - list of classes
 */
void Student::setUcClasses(list<UcClass> ucClasses_) {
    ucClasses = ucClasses_;
}

/**
 * Complexity: linear in pos
 * @brief Adds a UcClass to the student's classes before the UcClass in position "pos"
 * @param aUcClass - UcClass to add
 * @param pos - position of UcClass to which "aUcClass" is going to be inserted before
 */
void Student::addUcClass(UcClass* aUcClass, int pos) {
    auto itr = ucClasses.begin();
    advance(itr, pos);
    ucClasses.insert(itr, *aUcClass);
}

/**
 * Getter for student's name
 * @return student's name
 */
string Student::getStudentName() const {
    return this->studentName;
}

/**
 * Getter for student's code
 * @return student's code
 */
int Student::getStudentCode() const {
    return this->studentCode;
}

/**
 * Getter for student's classes
 * @return student's list of classes
 */
list<UcClass> Student::getUcClasses() const {
    return this->ucClasses;
}

/**
 * @brief Overloads '<' operator to order students by their student's code
 * @param student - second student to be compared
 * @return true if the first student's code is lower than second student's code
 */
bool Student::operator<(const Student &student) const {
    return this->studentCode < student.studentCode;
}

/**
 * Complexity: Linear in the number of classes of the student
 * @brief Checks if a certain student is part of a certain class
 * @param classCode_ - class to be checked
 * @return true if student is part of the class to be checked, false otherwise
 */
bool Student::hasClass(string classCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getClassCode()==classCode_) return true;
    }
    return false;
}

/**
 * Complexity: Linear in the number of classes of the student
 * @brief Checks if a certain student is enrolled in a certain curricular unit
 * @param ucCode_ - curricular unit to be checked
 * @return true if student is enrolled in the curricular unit, false otherwise
 */
bool Student::hasUc(string ucCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getUcCode()==ucCode_) return true;
    }
    return false;
}

/**
 * Complexity: O(classes*lectures) being "classes" the classes that the students is in and "lectures" the lectures of a
 * certain class
 * Goes through all the student's lectures and displays them in a format similar to a timetable
 * @brief Draw a graphical menu of the student
 */
void Student::printGraphicalSchedule() const {
    cout<<this->studentName<<" Schedule"<<endl;
    string schedule=" ________________________________________________________________________________________\n"
                    "|     Hour    |    Monday    |   Tuesday    |   Wednesday  |   Thursday   |    Friday    |\n"
                    "|________________________________________________________________________________________|\n";


    vector<string> periodOfTime;/*this vector will contain what has to be printed in each period of time
                                (24 periods of time each day 5 days of the week and each period has a sperating line so times two)*/
    for(int i=0;i<24*5*2;i+=2){
        periodOfTime.push_back("              |");
        periodOfTime.push_back("______________|");
    } //Initializing the vector with alternating lines;

    for(UcClass aux:this->ucClasses){
        for(Lecture lecture:aux.getLectures()){
            string weekday=lecture.getWeekDay();
            int weekDayPosition;
            if(weekday=="Monday") weekDayPosition=0;
            else if(weekday=="Tuesday") weekDayPosition=1;
            else if( weekday=="Wednesday") weekDayPosition=2;
            else if(weekday=="Thursday") weekDayPosition=3;
            else weekDayPosition=4;
            float duration=lecture.getDuration();

            int lectureStartPosition=24*2*weekDayPosition +(lecture.getLectureTime().first-8.00)*4;
            periodOfTime[lectureStartPosition]=" "+aux.getUcCode()+"("+lecture.getType()+")";
            if(lecture.getType().length()==1) periodOfTime[lectureStartPosition]+="  |";
            else  periodOfTime[lectureStartPosition]+=" |";
            periodOfTime[++lectureStartPosition]="   "+aux.getClassCode()+"    |";
            duration-=0.5;
            while(duration>0.5){
                duration-=0.5;
                periodOfTime[++lectureStartPosition]="              |";
                periodOfTime[++lectureStartPosition]="              |";
            }
            periodOfTime[++lectureStartPosition]="              |";
        }
    }
    float time=8.0;
    for(int i=0;i<24*2;i+=2) {

        if(time<10 ||(time+0.5<10)) schedule+="|  ";

        else schedule+="| ";
        schedule+=to_string((int)time)+':'+ to_string((int)((time-(int)time)*6))+"0-";
        time+=0.5;
        schedule+=to_string((int)time)+':'+ to_string((int)((time-(int)time)*6))+"0";
        if(time<10 &&(time-0.5<10)) schedule+=' ';
        schedule+=" |"+periodOfTime[i]+periodOfTime[48*1+i]+periodOfTime[48*2+i]+periodOfTime[48*3+i]+periodOfTime[48*4+i]+'\n';
        schedule+="|_____________|"+periodOfTime[i+1]+periodOfTime[48*1+i+1]+periodOfTime[48*2+i+1]+periodOfTime[48*3+i+1]+periodOfTime[48*4+i+1]+'\n';


    }
    cout<<schedule;
}

/**
 * Complexity: Linear in the number of classes of the student
 * @brief Verify if student belongs to a class for a certain curricular unit
 * @param ucClass_ - class of a certain curricular unit to be checked
 * @return true if the student is enrolled in the class of the certain curricular unit, false otherwise
 */
bool Student::hasUcClass(UcClass ucClass_) const {
    for (UcClass ucClass: ucClasses) {
        if (ucClass.getUcCode() == ucClass_.getUcCode() && ucClass.getClassCode() == ucClass_.getClassCode()) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Prints the student's name and student code
 */
void Student::print() const{
    int n = 4;
    int count = 1;
    for(char c : studentName){
        count++;
        if(count%8 == 0){
            n--;
        }
    }
    string t = "\t";
    for(int c = 0; c < n; c++){
        t = t + "\t";
    }
    std::cout << "|  Name: " + studentName << t <<"| Code: up" << studentCode << "\t|" << endl;
}

/**
 * @brief Prints a diagram schedule of the student's schedule
 */
void Student::printDiagramSchedule() const {
    cout<<this->studentName<<" Schedule"<<endl;
    for(UcClass ucClass_:this->ucClasses){
        cout<<"\tUc:"+ucClass_.getUcCode()+"|Class:"+ucClass_.getClassCode()+'\n';
        for(Lecture lecture_: ucClass_.getLectures()){
            cout<<"\t\t -> Weekday:"+lecture_.getWeekDay()+"|Start:"<<(int)lecture_.getLectureTime().first
            <<':'<< (lecture_.getLectureTime().first-(int)lecture_.getLectureTime().first)*6<<"0|End:"<<(int)lecture_.getLectureTime().second
            <<':'<< (lecture_.getLectureTime().second-(int)lecture_.getLectureTime().second)*6<<"0|Type:"+lecture_.getType()<<endl;
        }

    }
}
