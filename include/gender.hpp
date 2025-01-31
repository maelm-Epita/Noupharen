#pragma once

#include <string>

struct Noun;

// A gender is a collection of rules to be applied to nouns
class Gender{
public:
  std::string name;
  Noun ApplyGender(Noun *noun);
};
