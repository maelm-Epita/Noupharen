#include <cstdlib>
#include <ctime>
#include "include/generator.hpp"

Generator::Generator(){
  nb_words = 0;
  min_syllable_count= 0;
  max_syllable_count= 0;
  letter_groups = {};
  word_groups = {};
  syllable_patterns = {};
}

Syllable Generator::GenerateSyllable(){
  Syllable new_syllable;
  unsigned int syllable_pattern_index = rand() % syllable_patterns.size(); // random syllable pattern
  new_syllable.pattern = syllable_patterns[syllable_pattern_index];
  for (LetterGroup *group : new_syllable.pattern){
    unsigned int letter_index = rand() % group->letters.size(); // random letter from current group
    new_syllable.letters.push_back(&group->letters[letter_index]);
  }
  return new_syllable;
}

Word Generator::GenerateWord(){
  Word new_word;
  unsigned int wgroup_index = rand() % (word_groups.size()); // random word group
  new_word.group = &word_groups[wgroup_index];
  unsigned int wattr_index = rand() % (new_word.group->possible_attributes.size()); // random attr from group
  new_word.attributes.push_back(&new_word.group->possible_attributes[wattr_index]);
  unsigned int syllable_count = rand() % (max_syllable_count-min_syllable_count+1) + min_syllable_count; // random word size
  //
  for (unsigned int i=0; i<syllable_count; i++){
    new_word.syllables.push_back(GenerateSyllable());
  }
  for (WordAttribute *attr : new_word.attributes){
    attr->attribute_function(&new_word); // apply attr
  }
  return new_word;
}

std::vector<Word> Generator::GenerateWords(){
  srand(time(0)); // seed rng
  //
  std::vector<Word> words {};
  for (unsigned int i=0; i<nb_words; i++){
    Word new_word = GenerateWord();
    words.push_back(new_word);
  }
  return words;
};
