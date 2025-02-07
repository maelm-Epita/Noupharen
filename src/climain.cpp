#include <iostream>
#include "include/dictionary.hpp"
#include "include/generator.hpp"

int climain(){
  Letter letter1, letter2, letter3, letter4, letter5, letter6;
  letter1.character = "g";
  letter2.character = "a";
  letter3.character = "r";
  letter4.character = "p";
  letter5.character = "i";
  letter6.character = "t";
  LetterGroup lgroup1, lgroup2;
  lgroup1.group_identifier = "C";
  lgroup2.group_identifier = "V";
  lgroup1.letters.push_back(letter1);
  lgroup1.letters.push_back(letter3);
  lgroup1.letters.push_back(letter4);
  lgroup1.letters.push_back(letter6);
  lgroup2.letters.push_back(letter2);
  lgroup2.letters.push_back(letter5);
  SyllablePattern pat1, pat2, pat3;
  pat1.push_back(&lgroup1);
  pat1.push_back(&lgroup2);
  pat1.push_back(&lgroup2);
  pat1.push_back(&lgroup1);
  pat2.push_back(&lgroup1);
  pat2.push_back(&lgroup2);
  pat2.push_back(&lgroup1);
  pat3.push_back(&lgroup1);
  pat3.push_back(&lgroup2);
  Syllable wattr3syl, wattr4syl;
  std::vector<Syllable> wattr3suf, wattr4pref;
  wattr3syl.letters.push_back(&letter3);
  wattr3syl.letters.push_back(&letter2);
  wattr3syl.pattern.push_back(&lgroup1);
  wattr3syl.pattern.push_back(&lgroup2);
  wattr3suf = {wattr3syl};
  wattr4syl.letters.push_back(&letter1);
  wattr4syl.letters.push_back(&letter2);
  wattr4syl.pattern.push_back(&lgroup1);
  wattr4syl.pattern.push_back(&lgroup2);
  wattr4pref = {wattr4syl, wattr4syl};
  WordAttribute wattr1, wattr2, wattr3, wattr4;
  wattr1.attribute_identifier = "masculine";
  wattr2.attribute_identifier = "feminine";
  wattr3.attribute_identifier = "godan";
  wattr4.attribute_identifier = "ichidan";
  wattr1.attribute_function = WordAttribute::WATTR_PRESET_DONOTHING;
  wattr2.attribute_function = WordAttribute::WATTR_PRESET_DONOTHING;
  wattr3.attribute_function = [wattr3suf](Word *word) {WordAttribute::WATTR_PRESET_ADD_SUFFIX(wattr3suf, word);};
  wattr4.attribute_function = [wattr4pref](Word *word) {WordAttribute::WATTR_PRESET_ADD_PREFIX(wattr4pref, word);};
  WordGroup wgroup1, wgroup2;
  wgroup1.group_identifier = "Noun";
  wgroup2.group_identifier = "Verb";
  wgroup1.possible_attributes.push_back(wattr1);
  wgroup1.possible_attributes.push_back(wattr2);
  wgroup2.possible_attributes.push_back(wattr3);
  wgroup2.possible_attributes.push_back(wattr4);
  Generator generator;
  generator.min_syllable_count = 2;
  generator.max_syllable_count = 6;
  generator.nb_words = 10;
  generator.letter_groups.push_back(lgroup1);
  generator.letter_groups.push_back(lgroup2);
  generator.syllable_patterns.push_back(pat1);
  generator.syllable_patterns.push_back(pat2);
  generator.syllable_patterns.push_back(pat3);
  generator.word_groups.push_back(wgroup1);
  generator.word_groups.push_back(wgroup2);
  Dictionary dictionary;
  dictionary.words = generator.GenerateWords();
  for (Word word : dictionary.words){
    std::cout << word.GetDebugString() << "\n";
  }
  return 0;
}
