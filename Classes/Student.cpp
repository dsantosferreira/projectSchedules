#include "Student.h"

bool Student::operator<(const Student &student) {
    return this->studentCode < student.studentCode;
}

int Student::getstudentCode() const {
    return this->studentCode;
}