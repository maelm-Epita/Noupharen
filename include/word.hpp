#pragma once

#include "syllable.hpp"
#include "wordattribute.hpp"
#include <vector>

// A word is a collection of letter(s)
struct Word{
  std::vector<Syllable> syllables;
  // Gets the string representation of the word
  std::string GetString();
};

// A noun is a word which has a gender which can apply rules onto it
struct Noun : Word{
  WordAttribute *gender;
};

// A verb is a word which belongs to a verb group
struct Verb : Word{
  WordAttribute *verb_group;
};
