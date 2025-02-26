#pragma once

#include "lettergroup.hpp"
#include "word.hpp"
#include "include/probability.hpp"

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
  std::vector<Probability> sylptn_probabilities;
  std::vector<Probability> wordgrp_probabilities;
  std::vector<std::vector<Probability>> letter_probabilities;
  std::vector<std::vector<Probability>> wordattr_probabilities;
  // Generate words based on settings
  std::vector<Word> GenerateWords();
  // Helpers for probabilities;
  Probability GetSylPtnProbability(SyllablePattern);
  Probability GetWordGrpProbability(WordGroup);
  Probability GetLetterProbability(Letter, LetterGroup);
  Probability GetWordAttrProbability(WordAttribute, WordGroup);
  // unused
  void SetSylPtnProbability(SyllablePattern, Probability);
  void SetWordGrpProbability(WordGroup, Probability);
  void SetLetterProbability(Letter, LetterGroup, Probability);
  void SetWordAttrProbability(WordAttribute, WordGroup, Probability);
private:
  Syllable GenerateSyllable();
  Word GenerateWord();
};
