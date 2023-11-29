#include "virtual_machine.h"

using namespace std;

int main() {

    virtual_machine vm;
    vector<int> byte_code = {PUSH,0,STORE,0, PUSH,10,LOAD,0, ISGT, NOT, JIF,25, LOAD,0,PUSH,2,MULT,PRINT,POP,LOAD,0,PUSH,1,ADD,STORE,0,JMP,4};
    vm.load_instructions(byte_code);
    vm.run();
}
