#include "Classes/Database.h"
#include "Classes/Program.h"
using namespace std;
int main() {
    Program p=Program();
   // p.printSchedule();
    //p.printSchedule();//test the schedule
    p.run(); //test the menu
    Database data=p.getData();
    //data.searchByUC("L.EIC001");// teste de searchByUc
    //data.printClassDiagramSchedule("1LEIC01");
    //data.printClassGraphicSchedule("1LEIC01");
    system("clear");

    return 0;
}
