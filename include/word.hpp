#pragma once

#include "syllable.hpp"
#include "wordgroup.hpp"
#include <vector>

// A word is a collection of letter(s), it belongs to a "type" (such as noun, verb...) it can have attributes (like a gender, verb group, etc)
struct Word{
  std::vector<Syllable> syllables;
  std::vector<WordAttribute*> attributes;
  WordGroup *group;
  // Gets the string representation of the word
  std::string GetString();
  std::string GetGroupString();
  std::string GetDebugString();
};

