#include "include/lettergroup.hpp"

std::string LetterGroup::LGStringFromLetterGroups(std::vector<LetterGroup> groups){
    std::string res;
    for (unsigned int i=0; i<groups.size(); i++){
        LetterGroup lg = groups[i];
        res += lg.group_identifier + ":";
        for (unsigned int j=0; j<lg.letters.size(); j++){
            Letter l = lg.letters[j];
            res += l.character;
            if (j!=lg.letters.size()-1){
                res += " ";
            }
        }
        if (i!=groups.size()-1){
            res += "\n";
        }
    }
    return res;
}

std::string LetterGroup::SPStringFromSyllablePatterns(std::vector<SyllablePattern> patterns){
    std::string res;
    for (unsigned int i=0; i<patterns.size(); i++){
        SyllablePattern sp = patterns[i];
        for (unsigned int j=0; j<sp.size(); j++){
            LetterGroup* lg = sp[j];
            res += lg->group_identifier;
            if (j!=sp.size()-1){
                res += " ";
            }
        }
        if (i!=patterns.size()-1){
            res += "\n";
        }
    }
    return res;
}
