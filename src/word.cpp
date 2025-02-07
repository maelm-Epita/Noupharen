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
    for (unsigned int i=0; i<syl.letters.size(); i++){
      result += syl.letters[i]->character + "[" + syl.pattern[i]->group_identifier + "]";
    }
    result += " ";
  }
  return result;
}
