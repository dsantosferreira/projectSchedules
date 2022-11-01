#include "Student.h"

Student::Student() {}

void Student::setStudentCode(int studentCode_) {
    studentCode = studentCode_;
}

void Student::setStudentName(std::string studentName_) {
    studentName = studentName_;
}

void Student::setUcClasses(list<UcClass> ucClasses_) {
    ucClasses = ucClasses_;
}

void Student::addUcClass(UcClass aUcClass) {
    ucClasses.push_back(aUcClass);
}
/**/

Student::Student(string studentName_, int studentCode_, list<UcClass> ucClasses_){
    this->studentCode=studentCode_;
    this->studentName= studentName_;
    this->ucClasses=ucClasses_;
}

string Student::getStudentName() const {
    return this->studentName;
}

list<UcClass> Student::getUcClasses() const {
    return this->ucClasses;
}

bool Student::operator<(const Student &student) const {
    return this->studentCode < student.studentCode;
}

int Student::getStudentCode() const {
    return this->studentCode;
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

bool Student::hasClass(string classCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getClassCode()==classCode_) return true;
    }
    return false;
}

bool Student::hasUc(string ucCode_) const {
    for(UcClass ucClass: this->ucClasses){
        if(ucClass.getUcCode()==ucCode_) return true;
    }
    return false;
}

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

bool Student::hasUcClass(UcClass ucClass_) const {
    for (UcClass ucClass: ucClasses) {
        if (ucClass.getUcCode() == ucClass_.getUcCode() && ucClass.getClassCode() == ucClass_.getClassCode()) {
            return true;
        }
    }
    return false;
}

void Student::print() const{
    std::cout << "Name:" +studentName << " | Code:up" << studentCode << endl;
}

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
