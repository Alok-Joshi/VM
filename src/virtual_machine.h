#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H
#include <vector>
#include "frame.h"

enum instruction_set{
    HALT, //0
    PUSH, //1

    //arithmetic
    ADD, //3
    SUB, //4
    MULT, //5
    DIV, //6

    //logical operators
    NOT, //7
    AND, //8

    //Stack management opcodes
    POP, //9
    DUP, //10

    //comparison operators
    ISEQ, //11
    ISGT, //12

    //display
    PRINT, //13

    //variables
    LOAD, //14
    STORE, //15

    //branching
    JMP, //16
    JIF, //17
};



class virtual_machine {

    private:
        std::vector<int> byte_stream;
        int instruction_pointer;
        std::vector<int> stack;
        int stack_pointer;
        frame* current_frame;

    void handle_push_opcode();
    void handle_pop_opcode();
    void handle_dup_opcode();
    void handle_jmp_opcode();
    void handle_jif_opcode();
    void handle_load_opcode();
    void handle_store_opcode();
    void handle_binary_operator_opcode(instruction_set opcode);
    void handle_unary_operator_opcode(instruction_set opcode);
    void stack_push(int operand);
    int stack_pop();
    int stack_peek();
    public:
    virtual_machine();
    void run();
    int read_instruction_opcode();
    void load_instructions(std::vector<int>& byte_stream);

};






#endif
