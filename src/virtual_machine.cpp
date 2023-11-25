#include "virtual_machine.h"
#include <iostream>

using namespace std;


virtual_machine:: virtual_machine(): stack_pointer(0), instruction_pointer(0) {}

int virtual_machine:: read_instruction_opcode() {

    if(instruction_pointer < byte_stream.size()) {

        return byte_stream[instruction_pointer++];

    }
    else return -1;

}

void virtual_machine:: load_instructions(vector<int> &byte_stream) {
    this->byte_stream = byte_stream;
}

void virtual_machine:: run() {

    int current_instruction_opcode = read_instruction_opcode();

    switch(current_instruction_opcode) {

    case HALT:
        cout<<"PROGRAM HALTED"<<endl;
        return;
    case PUSH:
        break;
    case POP:
        break;
    case -1:
        return;

    }



}
