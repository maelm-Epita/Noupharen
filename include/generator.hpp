#pragma once

#include <noun.hpp>
#include <pattern.hpp>

// A generator is an object which holds a state, configured before generating words
class Generator{
  int nb_words;
  std::vector<Letter> availabe_letters;
  std::vector<Pattern> patterns;
  std::vector<Word> GenerateWords();
};
