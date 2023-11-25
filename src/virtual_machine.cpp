#include "virtual_machine.h"
#include <iostream>

using namespace std;


virtual_machine:: virtual_machine(): stack_pointer(-1), instruction_pointer(0) {}

int virtual_machine:: read_instruction_opcode() {

    if(instruction_pointer < byte_stream.size()) {

        return byte_stream[instruction_pointer++];

    }
    else return -1;

}

void virtual_machine:: load_instructions(vector<int> &byte_stream) {
    this->byte_stream = byte_stream;
}

void virtual_machine:: handle_operator(char m_operator) {
    int operand1 = stack_pop();
    int operand2 = stack_pop();
    int result = 0;
    switch(m_operator) {

    case '+':
        result = operand2 + operand1;
        break;
    case '-':
        result = operand2 - operand1;
        break;
    case '*':
        result = operand2 * operand1;
        break;
    case '/':
        result = operand2 / operand1;
        break;

    }
    stack_push(result);
}

void virtual_machine:: handle_push_opcode() {
    int operand = byte_stream[instruction_pointer++];
    stack_push(operand);
}

void virtual_machine:: stack_push(int operand1) {
    stack_pointer++;
    stack.push_back(operand1);
}


int virtual_machine:: stack_pop() {

    if(stack_pointer == -1) {
        throw "empty stack";
    }
    int top_element = stack[stack_pointer];
    stack.pop_back();
    stack_pointer--;
    return top_element;

}


void virtual_machine:: run() {

    while(1) {
        int current_instruction_opcode = read_instruction_opcode();
        switch(current_instruction_opcode) {

        case HALT:
            return;
        case PUSH:
            handle_push_opcode();
            break;
        case ADD:
            handle_operator('+');
            break;
        case SUB:
            handle_operator('-');
            break;
        case MULT:
            handle_operator('*');
            break;
        case DIV:
            handle_operator('/');
            break;
        case -1:
            return;

        }
    }



}


