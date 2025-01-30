#pragma once

#include <string>

class Noun;

// A gender is a collection of rules to be applied to nouns
struct Gender{
  std::string name;
  Noun ApplyGender(Noun noun);
};
