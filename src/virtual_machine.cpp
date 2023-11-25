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

void virtual_machine:: handle_pop_opcode() {
    stack_pop();
}

void virtual_machine:: handle_dup_opcode() {
    int value = stack_peek();
    stack_push(value);
}

void virtual_machine:: handle_unary_operator_opcode(instruction_set opcode) {
    int operand1 = stack_pop();
    int result = 0;

    switch(opcode) {
    case NOT:
        result = !operand1;
        break;
    }

    stack_push(result);
}

void virtual_machine:: handle_binary_operator_opcode(instruction_set opcode) {
    int operand1 = stack_pop();
    int operand2 = stack_pop();
    int result = 0;
    switch(opcode) {

    case ADD:
        result = operand2 + operand1;
        break;
    case SUB:
        result = operand2 - operand1;
        break;
    case MULT:
        result = operand2 * operand1;
        break;
    case DIV:
        result = operand2 / operand1;
        break;
    case AND:
        result = operand2 & operand1;
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


int virtual_machine:: stack_peek() {

    if(stack_pointer == -1) {
        throw "empty stack";
    }
    int top_element = stack[stack_pointer];
    return top_element;

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
            handle_binary_operator_opcode(ADD);
            break;
        case SUB:
            handle_binary_operator_opcode(SUB);
            break;
        case MULT:
            handle_binary_operator_opcode(MULT);
            break;
        case DIV:
            handle_binary_operator_opcode(DIV);
            break;
        case AND:
            handle_binary_operator_opcode(AND);
            break;
        case NOT:
            handle_unary_operator_opcode(NOT);
            break;
        case POP:
            handle_unary_operator_opcode(NOT);
            break;
        case DUP:
            handle_unary_operator_opcode(NOT);
            break;
        case -1:
            return;

        }
    }



}


