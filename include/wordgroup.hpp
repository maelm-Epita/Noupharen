#pragma once

#include "include/wordattribute.hpp"
#include <string>
#include <vector>

struct WordGroup{
  std::string group_identifier;
  std::vector<WordAttribute> possible_attributes;
};
