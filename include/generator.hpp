#pragma once

#include <noun.hpp>

// A generator is an object which holds a state, configured before generating words
class Generator{
  int nb_words;
  std::vector<Word> GenerateWords();
};
