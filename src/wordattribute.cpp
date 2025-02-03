#include "word.hpp"
#include "wordattribute.hpp"

void WordAttribute::WATTR_PRESET_DONOTHING(Word *word){
  return;
}

void WordAttribute::WATTR_PRESET_ADD_SUFFIX(std::vector<Syllable> suff, Word *word){
  for (Syllable syl : suff){
    word->syllables.push_back(syl);
  }
}

void WordAttribute::WATTR_PRESET_ADD_PREFIX(std::vector<Syllable> pref, Word *word){
  std::vector<Syllable>::iterator it = word->syllables.begin();
  for (int i=0; i<pref.size(); i++){
    it = word->syllables.insert(it, pref[i]);
  }
}

