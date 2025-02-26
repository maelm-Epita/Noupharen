#include <cstdlib>
#include <ctime>
#include <random>
#include "include/generator.hpp"

Generator::Generator(){
  nb_words = 0;
  min_syllable_count= 0;
  max_syllable_count= 0;
  letter_groups = {};
  word_groups = {};
  syllable_patterns = {};
  letter_probabilities = {};
  wordgrp_probabilities = {};
  wordattr_probabilities = {};
  sylptn_probabilities = {};
  std::mt19937 rd(std::random_device{}());
  random = rd;
}

Syllable Generator::GenerateSyllable(){
    Syllable new_syllable;
    std::discrete_distribution<size_t> sylptn_d = Probability::GetDiscreteDistribution(sylptn_probabilities);
    unsigned int sylptn_index = sylptn_d(random);
    new_syllable.pattern = syllable_patterns[sylptn_index];
    for (LetterGroup *group : new_syllable.pattern){
        std::discrete_distribution<size_t> ltr_d = Probability::GetDiscreteDistribution(letter_probabilities[sylptn_index]);
        unsigned int ltr_index = ltr_d(random);
        new_syllable.letters.push_back(&group->letters[ltr_index]);
    }
    return new_syllable;
}

Word Generator::GenerateWord(){
    Word new_word;
    std::discrete_distribution<size_t> wgrp_d = Probability::GetDiscreteDistribution(wordgrp_probabilities);
    unsigned int wgroup_index = wgrp_d(random); // random word group
    new_word.group = &word_groups[wgroup_index];
    std::discrete_distribution<size_t> wattr_d = Probability::GetDiscreteDistribution(wordattr_probabilities[wgroup_index]);
    unsigned int wattr_index = wattr_d(random); // random attr from group
    new_word.attributes.push_back(&new_word.group->possible_attributes[wattr_index]);
    unsigned int syllable_count = rand() % (max_syllable_count-min_syllable_count+1) + min_syllable_count; // random word size
    //
    for (unsigned int i=0; i<syllable_count; i++){
        new_word.syllables.push_back(GenerateSyllable());
    }
    // THIS LINE WILL CAUSE A CRASH IF NEW LETTER GROUPS ARE CREATED WHILE ATTRIBUTES DON'T CHANGE BECAUSE
    // OBVIOUSLY THE ATTRIBUTE FUNCTIONS LETTER POINTERS POINT TO LETTERS FROM GROUPS THAT DONT EXISTE ANYMORE LOL
    for (WordAttribute *attr : new_word.attributes){
        //attr->attribute_function(&new_word); // apply attr
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

Probability Generator::GetSylPtnProbability(SyllablePattern ptn){
    for (unsigned int i=0; i<syllable_patterns.size(); i++){
        if (syllable_patterns[i] == ptn){
            return sylptn_probabilities[i];
        }
    }
}
Probability Generator::GetWordGrpProbability(WordGroup grp){
    for (unsigned int i=0; i<word_groups.size(); i++){
        if (word_groups[i].group_identifier == grp.group_identifier){
            return wordgrp_probabilities[i];
        }
    }
}
Probability Generator::GetLetterProbability(Letter ltr, LetterGroup grp){
    for (unsigned int i=0; i<letter_groups.size(); i++){
        if (letter_groups[i].group_identifier == grp.group_identifier){
            for (unsigned int j=0; j<letter_groups[i].letters.size(); j++){
                if (letter_groups[i].letters[j].character == ltr.character){
                    return letter_probabilities[i][j];
                }
            }
        }
    }
}
Probability Generator::GetWordAttrProbability(WordAttribute atr, WordGroup grp){
    for (unsigned int i=0; i<word_groups.size(); i++){
        if (word_groups[i].group_identifier == grp.group_identifier){
            for (unsigned int j=0; j<word_groups[i].possible_attributes.size(); j++){
                if (word_groups[i].possible_attributes[j].attribute_identifier== atr.attribute_identifier){
                    return wordattr_probabilities[i][j];
                }
            }
        }
    }
}

void Generator::SetSylPtnProbability(SyllablePattern ptn, Probability prob){
    for (unsigned int i=0; i<syllable_patterns.size(); i++){
        if (syllable_patterns[i] == ptn){
            sylptn_probabilities[i] = prob;
        }
    }
}
void Generator::SetWordGrpProbability(WordGroup grp, Probability prob){
    for (unsigned int i=0; i<word_groups.size(); i++){
        if (word_groups[i].group_identifier == grp.group_identifier){
            wordgrp_probabilities[i] = prob;
        }
    }
}
void Generator::SetLetterProbability(Letter ltr, LetterGroup grp, Probability prob){
    for (unsigned int i=0; i<letter_groups.size(); i++){
        if (letter_groups[i].group_identifier == grp.group_identifier){
            for (unsigned int j=0; j<letter_groups[i].letters.size(); j++){
                if (letter_groups[i].letters[j].character == ltr.character){
                    letter_probabilities[i][j] = prob;
                }
            }
        }
    }
}
void Generator::SetWordAttrProbability(WordAttribute atr, WordGroup grp, Probability prob){
    for (unsigned int i=0; i<word_groups.size(); i++){
        if (word_groups[i].group_identifier == grp.group_identifier){
            for (unsigned int j=0; j<word_groups[i].possible_attributes.size(); j++){
                if (word_groups[i].possible_attributes[j].attribute_identifier== atr.attribute_identifier){
                    wordattr_probabilities[i][j] = prob;
                }
            }
        }
    }
}
