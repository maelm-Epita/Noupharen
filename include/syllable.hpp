#pragma once

#include "letter.hpp"
#include "syllablepattern.hpp"
#include <vector>

class Syllable{
public:
  std::vector<Letter*> letters;
  SyllablePattern pattern;

  std::string GetDebugString();

  static bool SyllablesFromArgString(std::string, std::vector<LetterGroup>*, std::vector<Syllable>* res);
  static std::string ArgStringFromSyllables(std::vector<Syllable>);
};
