#pragma once

#include "syllable.hpp"
#include "wordattributefunctionpreset.hpp"
//#include "word.hpp"
#include <functional>
#include <string>
#include <variant>
#include <vector>


typedef std::variant<std::vector<Syllable>> AttributeFuncArgument;
// A word attribute is a collection of rules to be applied to words (this could be a gender or a verb group for example);
// The attribute function is set at run time by the user, with custom code or from a list of preset functions, capturing arguments
class WordAttribute{
public:
  std::string attribute_identifier;
  std::function<void(Word*)> attribute_function;
  std::vector<AttributeFuncArgument> attribute_func_arguments;
  WordAttributeFunctionPreset attribute_func_preset;

  static std::vector<WordAttribute> GetWordAttributesFromStr(std::string, std::vector<WordAttribute>);
};
