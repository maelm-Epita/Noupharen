#pragma once

#include "lettergroup.hpp"
#include "word.hpp"

// A generator is an object which holds a state, configured before generating words
class Generator{
public:
  // empty generator settings upon launching the application
  Generator();
  // load generator settings from a file
  Generator(std::string path);

  unsigned int nb_words;
  unsigned int min_syllable_count;
  unsigned int max_syllable_count;
  std::vector<LetterGroup> letter_groups;
  std::vector<WordGroup> word_groups;
  std::vector<SyllablePattern> syllable_patterns;

  // Generate words based on settings
  std::vector<Word> GenerateWords();
private:
  Syllable GenerateSyllable();
  Word GenerateWord();
};
