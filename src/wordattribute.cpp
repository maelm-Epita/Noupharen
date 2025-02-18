#include "include/wordattribute.hpp"
#include "include/helpers.h"


WordAttribute FindAttrWithId(std::string id, std::vector<WordAttribute> attrs){
    for (WordAttribute wattr : attrs){
        if (wattr.attribute_identifier == id){
            return wattr;
        }
    }
}

std::vector<WordAttribute> WordAttribute::GetWordAttributesFromStr(std::string str, std::vector<WordAttribute> attrs){
    std::vector<WordAttribute> res;
    std::vector<std::string> ids = split(str, ',');
    for (std::string id : ids){
        res.push_back(FindAttrWithId(id, attrs));
    }
    return res;
}
