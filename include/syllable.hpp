#pragma once

#include "letter.hpp"
#include "syllablepattern.hpp"
#include <vector>

struct Syllable{
  std::vector<Letter*> letters;
  SyllablePattern pattern;
};
