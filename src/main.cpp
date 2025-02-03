#include <iostream>
#include <dictionnary.hpp>
#include <generator.hpp>

int main(){
  Generator generator;
  generator.min_word_size = 5;
  generator.max_word_size = 5;
  generator.nb_words = 10;
  Letter letter1, letter2, letter3, letter4, letter5, letter6;
  letter1.character = "A'";
  letter1.cv_type = CVTYPE_VOWEL;
  letter1.articulation_type = ARTICULATIONTYPE_VELAR;
  letter2.character = "o";
  letter2.cv_type = CVTYPE_VOWEL;
  letter2.articulation_type = ARTICULATIONTYPE_VELAR;
  letter3.character = "p'";
  letter3.cv_type = CVTYPE_VOWEL;
  letter3.articulation_type = ARTICULATIONTYPE_VELAR;
  letter4.character = "@";
  letter4.cv_type = CVTYPE_VOWEL;
  letter4.articulation_type = ARTICULATIONTYPE_VELAR;
  letter5.character = "j";
  letter5.cv_type = CVTYPE_VOWEL;
  letter5.articulation_type = ARTICULATIONTYPE_VELAR;
  letter6.character = "$";
  letter6.cv_type = CVTYPE_VOWEL;
  letter6.articulation_type = ARTICULATIONTYPE_VELAR;
  generator.letters.push_back(letter1);
  generator.letters.push_back(letter2);
  generator.letters.push_back(letter3);
  generator.letters.push_back(letter4);
  generator.letters.push_back(letter5);
  generator.letters.push_back(letter6);
  Dictionnary dictionnary;
  dictionnary.words = generator.GenerateWords();
  for (Word word : dictionnary.words){
    std::cout << word.GetString() << "\n";
  }
  return 0;
}
