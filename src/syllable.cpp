#include "include/syllable.hpp"
#include "include/lettergroup.hpp"
#include "include/helpers.h"

bool SingleSyllableFromArgString(std::string str, std::vector<LetterGroup> *groups, Syllable* res){
    std::vector<std::string> l_strings = split(str, '_');
    for (std::string letter : l_strings){
        bool found = false;
        for (unsigned int i=0; i<groups->size() && !found; i++){
            LetterGroup* g = &(*groups)[i];
            for (unsigned int j=0; j<g->letters.size(); j++){
                Letter* l = &g->letters[j];
                if (l->character == letter){
                    found = true;
                    res->letters.push_back(l);
                    res->pattern.push_back(g);
                }
            }
        }
        if (!found){
            return 1;
        }
    }
    return 0;
}

std::string Syllable::GetDebugString(){
    std::string res;
    for (unsigned int i=0; i<letters.size(); i++){
        res += letters[i]->character + "[" + pattern[i]->group_identifier + "]";
    }
    return res;
}

bool Syllable::SyllablesFromArgString(std::string str, std::vector<LetterGroup>* groups, std::vector<Syllable>* res){
    std::vector<std::string> syl_strings = split(str, ' ');
    for (std::string s : syl_strings){
        Syllable syl;
        if (SingleSyllableFromArgString(s, groups, &syl)){
            return 1;
        }
        res->push_back(syl);
    }
    return 0;
}

std::string Syllable::ArgStringFromSyllables(std::vector<Syllable> syls){
    std::string res;
    for (unsigned int i=0; i<syls.size(); i++){
        Syllable syl = syls[i];
        for (unsigned int j=0; j<syl.letters.size(); j++){
            Letter* let = syl.letters[j];
            res += let->character;
            if (j!=syl.letters.size()-1){
                res += "_";
            }
        }
        if (i!=syls.size()-1){
            res += " ";
        }
    }
    return res;
}
