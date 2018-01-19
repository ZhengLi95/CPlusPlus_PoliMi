#include <iostream>

#include "user.hh"
#include "place.hh"

int main(int argc, char* argv[]){
    
    user usr1("Zheng", "Li");
    user usr2("Andrea", "Prugna");
    
    place plc1("Fontana Treve", "Roma, Italia");
    place plc2("Castello Sforzesco", "Milano, Italia");

    usr1.leave_a_comment("Allagando le citta' di lacrime...", plc1);
    usr1.leave_a_comment("Il castello dei destini incrociati...", plc2);
    usr2.leave_a_comment("Chi sta con lo zoppo, impara a zoppicare...", plc1);

    usr1.print_comments();
    usr2.print_comments();

    plc1.print_comments();
    plc2.print_comments();

    return 0;
}