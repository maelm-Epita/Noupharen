#ifndef WORDATTRIBUTEFUNCTIONPRESET_H
#define WORDATTRIBUTEFUNCTIONPRESET_H

#include <string>
#include <vector>

struct Word;
struct Syllable;

enum WATTR_PRESET_ARGTYPE{
    WATTR_PRESET_ARGTYPE_SYLLABLE_VEC
};

enum WATTR_PRESET_FUNCTION{
    ENUM_WATTR_PRESET_DONOTHING,
    ENUM_WATTR_PRESET_ADD_SUFFIX,
    ENUM_WATTR_PRESET_ADD_PREFIX,
    ENUM_WATTR_PRESET_LAST
};


class WordAttributeFunctionPreset{
public:
    WATTR_PRESET_FUNCTION func_preset;
    std::vector<WATTR_PRESET_ARGTYPE> func_argtypes;
    // Preset functions that can be used
    static void WATTR_PRESET_DONOTHING(Word *word);
    static void WATTR_PRESET_ADD_SUFFIX(std::vector<Syllable> suff, Word *word);
    static void WATTR_PRESET_ADD_PREFIX(std::vector<Syllable> pref, Word *word);
    static std::string GetWattrPresetName(WATTR_PRESET_FUNCTION);
    static WATTR_PRESET_FUNCTION GetWattrPresetEnum(std::string);

    const static std::vector<WordAttributeFunctionPreset> WordAttributeFunctionPresets;
};

#endif // WORDATTRIBUTEFUNCTIONPRESET_H
