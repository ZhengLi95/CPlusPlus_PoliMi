#include "connection.h"
#include "request.h"

int main(){ 
    char data1[4] = {'0', 'Z', 'H', '2'};
    char data2[6] = {'4', 'V', 'F', 'O', 'Q', '1'};
    Connection c1(10);
    Connection c2(11);
    Connection c3 = c2;
    Request r1(data1, 4, c1);
    Request r2 = r1;
    r2.setElement(1, '8');
    r2 = r1;
    r2.setElement(2, '8');
    Request r3(data2, 6, c2);
    Request r4 = r3;
    c2 = c1;
    c1.setPriority(12);
    r1.setElement(0, '5');
    c3.setPriority(13);
    r3 = r1;
    r3.setElement(3, 'V');
    r4.setElement(3, 'V');
    r3.setElement(4, 'Z');
    r4.setElement(4, 'Z');
    
    r1.print();
    r2.print();
    r3.print();
    r4.print();
}