#include "Classes/Database.h"
#include "Classes/Program.h"
using namespace std;
int main() {
    Program p=Program();
    p.run() ; //test the menu

    /*
    Database database = Database();
    set<Student> students = database.getStudents();
    for (auto itr = students.begin(); itr != students.end(); itr++) {
        list<UcClass> ucClasses = itr->getUcClasses();
        cout << itr->getStudentCode() << ' ' << itr->getStudentName() << ":" << endl;
        for (auto itr2 = ucClasses.begin(); itr2 != ucClasses.end(); itr2++) {
            cout << '\t' << itr2->getUcCode() << ' ' << itr2->getClassCode() << endl;
        }
    }*/
    return 0;
}
