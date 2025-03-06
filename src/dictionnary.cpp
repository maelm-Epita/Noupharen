#include "include/dictionary.hpp"
#include <iostream>
#include <fstream>
#include "include/helpers.h"

Dictionary::Dictionary(){
  words = {};
}

void Dictionary::AddWords(std::vector<Word> new_words){
    for (Word word : new_words){
        DictWord wrd;
        wrd.word = word.GetString();
        wrd.group = word.GetGroupString();
        wrd.meaning = "";
        words.push_back(wrd);
    }
}

void Dictionary::SaveToFile(std::string path){
    std::ofstream File(path);
    if (!File.is_open()){
        return;
    }
    File << "[words]\n";
    for (DictWord wrd : words){
        File << wrd.word + "," + wrd.group + "," + wrd.meaning + ",\n";
    }
}

bool Dictionary::LoadFromFile(std::string path){
    std::ifstream File(path);
    if (!File.is_open()){
        return false;
    }
    std::string line;
    std::getline(File, line);
    if (line != "[words]"){
        return false;
    }
    words.clear();
    while (std::getline(File, line)){
        if (line != ""){
            std::vector<std::string> tokens = split(line, ',');
            // the size will be 2 only if no meaning
            if (tokens.size() == 3){
                DictWord wrd;
                wrd.word = tokens[0];
                wrd.group = tokens[1];
                wrd.meaning = tokens[2];
                words.push_back(wrd);
            }
        }
    }
    return true;
}
