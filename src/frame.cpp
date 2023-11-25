#include "frame.h"

using namespace std;

int frame:: get_variable_value(int variable_name) {
    return variable_store[variable_name];
}
void frame:: set_variable(int variable_name, int variable_value) {
    variable_store[variable_name] = variable_value;
}
