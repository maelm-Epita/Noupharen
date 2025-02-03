#pragma once

#include <string>

struct Word;

enum ATTRIBUTETYPE{
  ATTRIBUTETYPE_VERBGROUP,
  ATTRIBUTETYPE_GENDER
};

// A word attribute is a collection of rules to be applied to words (this could be a gender or a verb group for example);
class WordAttribute{
public:
  ATTRIBUTETYPE type;
  std::string name;
  Word ApplyModification(Word *word);
};
