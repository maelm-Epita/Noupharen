#pragma once

#include "wordattribute.hpp"
#include <vector>

struct WordGroup{
  std::string group_identifier;
  std::vector<WordAttribute> possible_attributes;
};
