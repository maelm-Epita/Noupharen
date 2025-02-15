#include "include/syllable.hpp"
#include "include/lettergroup.hpp"
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


Syllable SingleSyllableFromArgString(std::string str, std::vector<LetterGroup> *groups){
    Syllable res;
    std::vector<std::string> l_strings = split(str, '_');
    for (std::string letter : l_strings){
        bool found = false;
        for (unsigned int i=0; i<groups->size() && !found; i++){
            LetterGroup* g = &(*groups)[i];
            for (unsigned int j=0; j<g->letters.size(); j++){
                Letter* l = &g->letters[j];
                if (l->character == letter){
                    found = true;
                    res.letters.push_back(l);
                    res.pattern.push_back(g);
                }
            }
        }
    }
    return res;
}

std::string Syllable::GetDebugString(){
    std::string res;
    for (unsigned int i=0; i<letters.size(); i++){
        res += letters[i]->character + "[" + pattern[i]->group_identifier + "]";
    }
    return res;
}

std::vector<Syllable> Syllable::SyllablesFromArgString(std::string str, std::vector<LetterGroup> *groups){
    std::vector<Syllable> res;
    std::vector<std::string> syl_strings = split(str, ' ');
    for (std::string s : syl_strings){
        res.push_back(SingleSyllableFromArgString(s, groups));
    }
    return res;
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
