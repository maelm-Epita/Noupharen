#include "include/wordattribute.hpp"
#include "include/helpers.h"


bool FindAttrWithId(std::string id, std::vector<WordAttribute> attrs, WordAttribute* res){
    for (WordAttribute wattr : attrs){
        if (wattr.attribute_identifier == id){
            *res = wattr;
            return 0;
        }
    }
    return 1;
}

bool WordAttribute::GetWordAttributesFromStr(std::string str, std::vector<WordAttribute> attrs, std::vector<WordAttribute> *res){
    std::vector<std::string> ids = split(str, ',');
    for (std::string id : ids){
        WordAttribute w;
        if (FindAttrWithId(id, attrs, &w)){
            return 1;
        }
        res->push_back(w);
    }
    return 0;
}
