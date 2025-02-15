#pragma once

#include "letter.hpp"
#include "syllablepattern.hpp"
#include <vector>

class Syllable{
public:
  std::vector<Letter*> letters;
  SyllablePattern pattern;

  std::string GetDebugString();

  static std::vector<Syllable> SyllablesFromArgString(std::string, std::vector<LetterGroup>*);
  static std::string ArgStringFromSyllables(std::vector<Syllable>);
};
