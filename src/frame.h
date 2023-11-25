#ifndef FRAME_H
#define FRAME_H

#include<unordered_map>

class frame {

    private:
    std::unordered_map<int,int> variable_store;

    public:
    void set_variable(int variable_name, int variable_value);
    int get_variable_value(int variable_name);

};


#endif
