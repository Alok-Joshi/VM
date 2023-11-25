#include "virtual_machine.h"

using namespace std;

int main() {

    virtual_machine vm;
    vector<int> byte_code = {HALT};
    vm.load_instructions(byte_code);
    vm.run();

}
