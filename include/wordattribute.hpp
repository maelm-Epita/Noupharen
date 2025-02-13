#pragma once

#include "syllable.hpp"
#include <functional>
#include <string>
#include <variant>
#include <vector>

struct Word;

enum ENUM_WATTR_PRESET{
    ENUM_WATTR_PRESET_DONOTHING,
    ENUM_WATTR_PRESET_ADD_SUFFIX,
    ENUM_WATTR_PRESET_ADD_PREFIX,
    ENUM_WATTR_PRESET_LAST
};

// A word attribute is a collection of rules to be applied to words (this could be a gender or a verb group for example);
// The attribute function is set at run time by the user, with custom code or from a list of preset functions, capturing arguments
class WordAttribute{
public:
  std::string attribute_identifier;
  std::function<void(Word*)> attribute_function;
  ENUM_WATTR_PRESET attribute_func_preset;
  std::vector<std::variant<std::vector<Syllable>>> attribute_func_arguments;
  // Preset functions that can be used
  static void WATTR_PRESET_DONOTHING(Word *word);
  static void WATTR_PRESET_ADD_SUFFIX(std::vector<Syllable> suff, Word *word);
  static void WATTR_PRESET_ADD_PREFIX(std::vector<Syllable> pref, Word *word);
  // Helper function to grab the text of the presets enum
  static std::string GetWattrPresetName(ENUM_WATTR_PRESET);
};
