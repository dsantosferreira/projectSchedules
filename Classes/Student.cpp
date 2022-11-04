#include "Student.h"

/** Functionality: Student's default constructor
 * Description: Initializes the student's name with an empty string, its code with the value 0 and its classes with an empty list.
 */
Student::Student() {}



void Student::removeUcClass(UcClass aUcClass) {
    auto itr = ucClasses.begin();
    for (; itr != ucClasses.end(); itr++) {
        if (!(*itr < aUcClass) && !(aUcClass < *itr)) {
            ucClasses.erase(itr);
            break;
        }
    }
}


/** Functionality: Student's parameterized constructor
* Description: Initializes the student's name, student code and classes with the given input
* @param studentName_ student's name
* @param studentCode_ student's code
* @param ucClasses_ student's classes
*/
Student::Student(string studentName_, int studentCode_, list<UcClass> ucClasses_){
    this->studentCode=studentCode_;
    this->studentName= studentName_;
    this->ucClasses=ucClasses_;
}

/** Functionality: Student's copy constructor
 * Description: Creates a copy of the student that was given as input.
 * @param student_ student to be copied
 */
Student::Student(const Student &student_) {
    this->studentCode = student_.studentCode;
    this->studentName = student_.studentName;
    this->ucClasses = student_.ucClasses;
}

/**
 * Setter for student's code
 * @param studentCode_
 */
void Student::setStudentCode(int studentCode_) {
    studentCode = studentCode_;
}

/**
 * Setter for student's name
 * @param studentName_
 */
void Student::setStudentName(string studentName_) {
    studentName = studentName_;
}

/**
 * Setter for student's classes
 * @param ucClasses_
 */
void Student::setUcClasses(list<UcClass> ucClasses_) {
    ucClasses = ucClasses_;
}

/** Functionality: Adds certain UcClass to student's classes
 * Description: Adds a UcClass to student's classes before the UcClass in position "pos"
 * @param aUcClass UcClass to add
 * @param pos position of UcClass to which "aUcClass" is going to be inserted before
 */
void Student::addUcClass(UcClass* aUcClass, int pos) {
    auto itr = ucClasses.begin();
    advance(itr, pos);
    ucClasses.insert(itr, *aUcClass);
}

/**
 * Getter for student's name
 * @return
 */
string Student::getStudentName() const {
    return this->studentName;
}

/**
 * Getter for student's code
 * @return
 */
int Student::getStudentCode() const {
    return this->studentCode;
}

/**
 * Getter for student's classes
 * @return
 */
list<UcClass> Student::getUcClasses() const {
    return this->ucClasses;
}

/** Functionality: < operator overload
 * Description: Overloads '<' operator to order students by their student's code
 * @param student second student to be compared
 * @return true if first student's code is lower than second student's code
 */
bool Student::operator<(const Student &student) const {
    return this->studentCode < student.studentCode;
}

string Student::classOfUc(string ucCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getUcCode()==ucCode_) return ucClass.getClassCode();
    }
    string s=0;
    return s;
}

string Student::ucOfClass(std::string classCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getClassCode()==classCode_) return ucClass.getUcCode();
    }
    string s=0;
    return s;
}

/** Functionality: Checks if a certain student is part of a certain class
 * Description: Checks student's classes to find out if the student is in the class given as input
 * @param classCode_ class to be checked
 * @return true if student is part of the class to be checked. Return false otherwise
 */
bool Student::hasClass(string classCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getClassCode()==classCode_) return true;
    }
    return false;
}

/** Functionality: Checks if a certain student has a certain UC
 * Description: Checks student's classes to find out if it has the Uc if it has return ture otherwise return false
 * @param ucCode_
 * @return
 */
bool Student::hasUc(string ucCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getUcCode()==ucCode_) return true;
    }
    return false;
}

/**Functionality: Draw a graphical menu of the student
 * Description: The function will go through all the Students lectures which are going to be converted in form of a string and them displayed,
 * forming that way a schedule
 *
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

/**Functionality: Verify if student belongs to a class for a certain UC
 *
 * Description: The function will receive as parameters a UcClass which contains a Uc and a Class, then it will go through all the Students
 * UcClasses (which contain all the Students Ucs and its respective classes) and will check if for that Uc the Student has that class, if so
 * it will return true, otherwise it will return false.
 *
 * @param ucClass_
 * @return true if it has the class for the Uc, false otherwise
 */
bool Student::hasUcClass(UcClass ucClass_) const {
    for (UcClass ucClass: ucClasses) {
        if (ucClass.getUcCode() == ucClass_.getUcCode() && ucClass.getClassCode() == ucClass_.getClassCode()) {
            return true;
        }
    }
    return false;
}

/**Functionality:Print the student name and the student code
 * Description: Gives cout of the Student code and the student name
 */
void Student::print() const{
    std::cout << "Name:" +studentName << " | Code:up" << studentCode << endl;
}

/**
 * Functionality: print a diagram schedule of the student schedule
 * Description: it will go through all the students lectures and print them giving cout of the Uc,Class, type of the lecture starting time
 * and ending time
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
