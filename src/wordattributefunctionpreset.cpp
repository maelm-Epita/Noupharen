#include "include/word.hpp"
#include "include/wordattributefunctionpreset.hpp"

std::string WordAttributeFunctionPreset::GetWattrPresetName(WATTR_PRESET_FUNCTION preset){
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

WATTR_PRESET_FUNCTION WordAttributeFunctionPreset::GetWattrPresetEnum(std::string preset){
    if (preset == "Do nothing"){
        return ENUM_WATTR_PRESET_DONOTHING;
    }
    else if (preset == "Add prefix syllable(s)"){
        return ENUM_WATTR_PRESET_ADD_PREFIX;
    }
    else if (preset == "Add suffix syllable(s)"){
        return ENUM_WATTR_PRESET_ADD_SUFFIX;
    }
    else{
        return ENUM_WATTR_PRESET_LAST;
    }
}

void WordAttributeFunctionPreset::WATTR_PRESET_DONOTHING(Word *word){
  return;
}
void WordAttributeFunctionPreset::WATTR_PRESET_ADD_SUFFIX(std::vector<Syllable> suff, Word *word){
  for (Syllable syl : suff){
    word->syllables.push_back(syl);
  }
}
void WordAttributeFunctionPreset::WATTR_PRESET_ADD_PREFIX(std::vector<Syllable> pref, Word *word){
  std::vector<Syllable>::iterator it = word->syllables.begin();
  for (std::size_t i=0; i<pref.size(); i++){
    it = word->syllables.insert(it, pref[i]);
  }
}

WordAttributeFunctionPreset a = {ENUM_WATTR_PRESET_DONOTHING, {}};
WordAttributeFunctionPreset b = {ENUM_WATTR_PRESET_ADD_SUFFIX, {WATTR_PRESET_ARGTYPE_SYLLABLE_VEC}};
WordAttributeFunctionPreset c = {ENUM_WATTR_PRESET_ADD_PREFIX, {WATTR_PRESET_ARGTYPE_SYLLABLE_VEC}};
const std::vector<WordAttributeFunctionPreset> WordAttributeFunctionPreset::WordAttributeFunctionPresets {
    a,
    b,
    c
};
