#include "UcClass.h"

/**
 * Will initialize a class with an empty ucCode, classCode and an empty list of lectures
 * @brief Default constructor
 */
UcClass::UcClass() {}

/**
 * @brief Parameterized constructor
 * @param ucCode_
 * @param classCode_
 * @param lectures_
 */
UcClass::UcClass(std::string ucCode_, std::string classCode_, list<Lecture> lectures_) {
    this->ucCode=ucCode_;
    this->classCode=classCode_;
    this->lectures=lectures_;
    this->numberOfStudents = 0;
    this->capacity = 0;
}

/**
 * Makes comparison between classes possible, classes will be compared by their curricular unit and afterwards by their
 * class number
 * @brief Overloads '<' operator
 * @param secondUcClass - second class to be compared
 * @return true if the first class less comes first than the second class, regarding the specification above
 */
bool UcClass::operator<(const UcClass secondUcClass) const {
    if (this->ucCode < secondUcClass.ucCode)
        return true;
    else if (this->ucCode == secondUcClass.ucCode) {
        if (this->classCode < secondUcClass.classCode)
            return true;
        return false;
    }
    else
        return false;
}

/**
 * @brief Getter for ucCode
 * @return ucCode
 */
string UcClass::getUcCode() const {
    return this->ucCode;
}

/**
 * @brief Getter for classCode
 * @return classCode
 */
string UcClass::getClassCode() const {
    return this->classCode;
}

/**
 * @brief Getter for lectures
 * @return lectures
 */
list<Lecture> UcClass::getLectures() const {
    return this->lectures;
}

/**
 * @brief Getter for number of current student in class
 * @return current number of students in class
 */
int UcClass::getNumberOfStudents() const {
    return numberOfStudents;
}

/**
 * @brief Getter for class' capacity
 * @return class's capacity
 */
int UcClass::getCapacity() const {
    return capacity;
}

/**
 * Setter for current number of students
 * @param newNumberOfStudents
 */
void UcClass::setNumberOfStudents(int newNumberOfStudents) {
    numberOfStudents = newNumberOfStudents;
}

/**
 * Setter for class' capacity
 * @param newCapacity
 */
void UcClass::setCapacity(int newCapacity) {
    capacity = newCapacity;
}

/**
 * @brief Adds a lecture to the class
 * @param aLecture - Lecture to be added
 */
void UcClass::addALecture(Lecture aLecture) {
    lectures.push_back(aLecture);
}

/**
 * Complexity: Linear in the number of lectures of the class
 * @brief Prints the schedule from a class
 */
void UcClass::print() const {
    cout<<'\t'<<this->getUcCode()<<":\n";
    for(Lecture lecture_: lectures){
            cout<<"\t\t -> Weekday:"+lecture_.getWeekDay()+"|Start:"<<(int)lecture_.getLectureTime().first
                <<':'<< (lecture_.getLectureTime().first-(int)lecture_.getLectureTime().first)*6<<"0|End:"<<(int)lecture_.getLectureTime().second
                <<':'<< (lecture_.getLectureTime().second-(int)lecture_.getLectureTime().second)*6<<"0|Type:"+lecture_.getType()<<endl;
        }
}

/**
 * @brief Prints the ucCode of a class
 */
void UcClass::printUcCode() const{
    cout << "|\t" << ucCode << "\t|\n";
}

/**
 * @brief Prints the classCode of a class
 */
void UcClass::printClassCode() const{
    cout << "|\t" << classCode << "\t\t|\n";
}