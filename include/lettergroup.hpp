#pragma once

#include "letter.hpp"
#include <string>
#include <vector>

struct LetterGroup{
  std::string group_identifier;
  std::vector<Letter> letters;
};
