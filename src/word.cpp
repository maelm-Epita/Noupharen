#include "include/word.hpp"

std::string Word::GetString(){
  std::string word = "";
  for (Syllable syllable : syllables){
    for (Letter *letter : syllable.letters){
      word.append(letter->character);
    }
  }
  return word;
}

std::string Word::GetDebugString(){
  std::string wstr = GetString();
  std::string result = wstr + " | " + group->group_identifier + " (";
  for (WordAttribute *attr : attributes){
    result += attr->attribute_identifier;
  }
  result += ")\nSyllable patterns : ";
  for (Syllable syl : syllables){
    result += syl.GetDebugString();
    result += " ";
  }
  return result;
}

std::string Word::GetGroupString(){
    std::string group_string = group->group_identifier + " (";
    for (unsigned int i=0; i<attributes.size(); i++){
        group_string += attributes[i]->attribute_identifier;
        if (i!=attributes.size()-1){
            group_string += ", ";
        }
    }
    group_string += ")";
    return group_string;
}
