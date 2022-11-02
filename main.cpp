#include "Classes/Database.h"
#include "Classes/Program.h"
using namespace std;
int main() {

    Program p=Program();
    p.run() ; //test the menu


    /*
    Database database = Database();
    vector<UcClass> ucClasses = database.getSchedule();
    for (auto itr = ucClasses.begin(); itr != ucClasses.end(); itr++) {
        list<Lecture> lectures = itr->getLectures();
        cout << itr->getUcCode() << ' ' << itr->getClassCode() << ":" << endl;
        for (auto itr2 = lectures.begin(); itr2 != lectures.end(); itr2++) {
            cout << '\t' << itr2->getWeekDay() <<  ' ' << itr2->getType() << endl;
        }
    }
    */
    return 0;
}
