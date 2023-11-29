#include "virtual_machine.h"
#include <iostream>

using namespace std;


virtual_machine:: virtual_machine(): stack_pointer(-1), instruction_pointer(0) {
    frame new_frame(0);
    frames.push_back(new_frame);
}

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

void virtual_machine:: handle_call_opcode() {
    //saving the current address in the current frame
    frame& current_frame = frames[frames.size()-1];
    current_frame.return_address = instruction_pointer + 2; // you dont want it to execute the call instruction again. + 2 because ip +1 is the operand here, ip+2 is the next instruction

    //setting up the new frame in call stack
    instruction_pointer++; //to get the CALL operand: the address
    int function_start_address = byte_stream[instruction_pointer];
    frame new_frame(function_start_address);
    frames.push_back(new_frame);

    instruction_pointer = function_start_address;
}

void virtual_machine:: handle_ret_opcode() {
    frames.pop_back();
    frame& current_frame = frames[frames.size()-1];
    instruction_pointer = current_frame.return_address;
}

void virtual_machine:: handle_store_opcode() {
    int variable_name = byte_stream[instruction_pointer++];
    int variable_value = stack_pop();
    current_frame->set_variable(variable_name,variable_value);
}

void virtual_machine:: handle_load_opcode() {
    int variable_name = byte_stream[instruction_pointer++];
    int variable_value = current_frame->get_variable_value(variable_name);
    stack_push(variable_value);
}
void virtual_machine:: handle_jmp_opcode() {
    int jmp_address = byte_stream[instruction_pointer++];
    instruction_pointer = jmp_address;
}

void virtual_machine:: handle_jif_opcode() {

    if(stack_peek() > 0) {
        int jmp_address = byte_stream[instruction_pointer];
        instruction_pointer = jmp_address;
    }
    else
    {
        instruction_pointer++;
    }

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
    case ISEQ:
        result = (operand2  == operand1);
        break;
    case ISGT:
        result = (operand2 > operand1);
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
            handle_pop_opcode();
            break;
        case DUP:
            handle_dup_opcode();
            break;
        case ISEQ:
            handle_binary_operator_opcode(ISEQ);
            break;
        case ISGT:
            handle_binary_operator_opcode(ISGT);
            break;
        case PRINT:
            cout<<stack_peek()<<endl;
            break;
        case JMP:
            handle_jmp_opcode();
            break;
        case STORE:
            handle_store_opcode();
            break;
        case LOAD:
            handle_load_opcode();
            break;
        case JIF:
            handle_jif_opcode();
            break;
        case -1:  //instructions over
            return;

        }
    }


}


