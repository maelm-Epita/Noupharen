#include "include/word.hpp"
#include "include/wordattribute.hpp"

std::string WordAttribute::GetWattrPresetName(ENUM_WATTR_PRESET preset){
    switch (preset){
    case ENUM_WATTR_PRESET_DONOTHING:
        return "Do nothing";
    case ENUM_WATTR_PRESET_ADD_PREFIX:
        return "Add prefix syllable(s)";
    case ENUM_WATTR_PRESET_ADD_SUFFIX:
        return "Add suffix syllable(s)";
    default:
        return "invalid attribute function";
    }
}

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

