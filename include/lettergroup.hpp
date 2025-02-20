#pragma once

#include "letter.hpp"
#include "syllablepattern.hpp"
#include <string>
#include <vector>

class LetterGroup{
public:
  std::string group_identifier;
  std::vector<Letter> letters;

  static std::string LGStringFromLetterGroups(std::vector<LetterGroup>);
  static std::string SPStringFromSyllablePatterns(std::vector<SyllablePattern>);
  static std::vector<LetterGroup> LetterGroupsFromLGString(std::string);
  static bool SyllablePatternsFromSPString(std::string, std::vector<LetterGroup>*, std::vector<SyllablePattern>*);
};
