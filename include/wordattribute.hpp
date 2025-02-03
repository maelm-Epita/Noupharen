#pragma once

#include "syllable.hpp"
#include <functional>
#include <string>
#include <vector>

struct Word;

// A word attribute is a collection of rules to be applied to words (this could be a gender or a verb group for example);
// The attribute function is set at run time by the user, with custom code or from a list of preset functions, capturing arguments
class WordAttribute{
public:
  std::string attribute_identifier;
  std::function<void(Word*)> attribute_function;
  // Preset functions that can be used
  static void WATTR_PRESET_DONOTHING(Word *word);
  static void WATTR_PRESET_ADD_SUFFIX(std::vector<Syllable> suff, Word *word);
  static void WATTR_PRESET_ADD_PREFIX(std::vector<Syllable> pref, Word *word);
};
