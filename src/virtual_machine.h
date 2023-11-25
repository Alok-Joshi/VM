#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H
#include <vector>

enum instruction_set{
    HALT, //0
    PUSH, //1
    POP, //2
};


class virtual_machine {

    private:
        std::vector<int> byte_stream;
        int instruction_pointer;
        std::vector<int> stack;
        int stack_pointer;

    public:
    virtual_machine();
    void run();
    int read_instruction_opcode();
    void load_instructions(std::vector<int>& byte_stream);

};






#endif
