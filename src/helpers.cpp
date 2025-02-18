#include "include/helpers.h"
#include <sstream>

std::vector<std::string> split(std::string str, char tok){
    std::string s;
    std::stringstream ss(str);
    std::vector<std::string> v;
    while (getline(ss, s, tok)){
        v.push_back(s);
    }
    return v;
};
