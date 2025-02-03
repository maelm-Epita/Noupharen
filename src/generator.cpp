#include <cstdlib>
#include <ctime>
#include <generator.hpp>

Generator::Generator(){
  nb_words = 0;
  min_syllable_count= 0;
  max_syllable_count= 0;
  letter_groups = {};
  word_attributes = {};
  syllable_patterns = {};
  types = {};
}

Syllable Generator::GenerateSyllable(){
  Syllable new_syllable;
  // pick a random syllable pattern
  unsigned int syllable_pattern_index = rand() % syllable_patterns.size();
  new_syllable.pattern = syllable_patterns[syllable_pattern_index];
  // for every group in the pattern, randomly pick one letter from that group
  for (LetterGroup *group : new_syllable.pattern){
    unsigned int letter_index = rand() % group->letters.size();
    new_syllable.letters.push_back(&group->letters[letter_index]);
  }
  return new_syllable;
}

Verb Generator::GenerateVerb(){
  Verb new_verb;
  // choose random word size
  unsigned int syllable_count = rand() % (max_syllable_count-min_syllable_count+1) + min_syllable_count;
  for (unsigned int i=0; i<syllable_count; i++){
    new_verb.syllables.push_back(GenerateSyllable());
  }
  return new_verb;
}

Noun Generator::GenerateNoun(){
  Noun new_noun;
  // choose random word size
  unsigned int syllable_count = rand() % (max_syllable_count-min_syllable_count+1) + min_syllable_count;
  for (unsigned int i=0; i<syllable_count; i++){
    new_noun.syllables.push_back(GenerateSyllable());
  }
  return new_noun;
}

std::vector<Word> Generator::GenerateWords(){
  // seed rng
  srand(time(0));
  // generate requested number of words
  std::vector<Word> words {};
  for (unsigned int i=0; i<nb_words; i++){
    Word new_word = GenerateNoun();
    words.push_back(new_word);
  }
  return words;
};
