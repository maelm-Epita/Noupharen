#include <word.hpp>

std::string Word::GetString(){
  std::string word = "";
  for (Syllable syllable : syllables){
    for (Letter *letter : syllable.letters){
      word.append(letter->character);
    }
  }
  return word;
}
