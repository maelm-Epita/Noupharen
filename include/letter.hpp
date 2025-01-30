#pragma once

#include <string>

enum CVTYPE{
  VOWEL,
  CONSONANT
};
enum ARTICULATIONTYPE{
  BILABIAL,
  LABIODENTAL,
  DENTAL,
  ALVEOLAR,
  PALATAL,
  VELAR,
  GLOTAL
};

// A letter is a single unit in the language, it is represented by one or multiple characters and has different attributes which are used for rule making during generation
struct Letter{
  std::string character;
  enum CVTYPE cv_type;
  enum ARTICULATIONTYPE articulation_type;
};
