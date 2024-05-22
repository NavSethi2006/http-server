#include "tcp.h"

/*
    HTTP SERVER FOR QUICK USES
    START WITH A TCP AND GO FROM THERE

*/

int main() {

    tcp ihatethisshit = setup_tcp();

    run_tcp(ihatethisshit);

}