#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H
#include <vector>

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
};


class virtual_machine {

    private:
        std::vector<int> byte_stream;
        int instruction_pointer;
        std::vector<int> stack;
        int stack_pointer;

    void handle_push_opcode();
    void handle_pop_opcode();
    void handle_dup_opcode();
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
