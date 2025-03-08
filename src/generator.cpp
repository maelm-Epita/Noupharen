#include <cstdlib>
#include <ctime>
#include <random>
#include "include/generator.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include "include/helpers.h"

Generator::Generator(){
  nb_words = 0;
  min_syllable_count= 0;
  max_syllable_count= 0;
  letter_groups = {};
  word_groups = {};
  syllable_patterns = {};
  excluded_intersylpatterns = {};
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
    // should be group index not sylptn index
    for (LetterGroup *group : new_syllable.pattern){
        int lgrp_index = GetLetterGroupProbabilityIndex(group);
        std::discrete_distribution<size_t> ltr_d = Probability::GetDiscreteDistribution(letter_probabilities[lgrp_index]);
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
        Syllable newsyl = GenerateSyllable();
        if (i!=0){
            unsigned int limit=0;
            while (!CheckIntersyllablePatternExclusionValid(new_word.syllables[i-1], newsyl)){
                if (limit == 100){
                    i=0;
                    new_word.syllables.clear();
                }
                newsyl = GenerateSyllable();
                limit++;
            }
        }
        new_word.syllables.push_back(newsyl);
    }
    // THIS LINE WILL CAUSE A CRASH IF NEW LETTER GROUPS ARE CREATED WHILE ATTRIBUTES DON'T CHANGE BECAUSE
    // OBVIOUSLY THE ATTRIBUTE FUNCTIONS LETTER POINTERS POINT TO LETTERS FROM GROUPS THAT DONT EXISTE ANYMORE LOL
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

bool Generator::CheckIntersyllablePatternExclusionValid(Syllable syla, Syllable sylb){
    LetterGroup* gra = syla.pattern[syla.pattern.size()-1];
    LetterGroup* grb = sylb.pattern[0];
    for (SyllablePattern ptn : excluded_intersylpatterns){
        if (ptn[0] == gra && ptn[1] == grb){
            return false;
        }
    }
    return true;
}

int Generator::GetLetterGroupProbabilityIndex(LetterGroup* grp){
    for (unsigned int i=0; i<letter_groups.size(); i++){
        if (&letter_groups[i] == grp){
            return i;
        }
    }
    return -1;
}

void Generator::ClearSettings(){
    letter_groups.clear();
    word_groups.clear();
    syllable_patterns.clear();
    excluded_intersylpatterns.clear();
    letter_probabilities.clear();
    wordattr_probabilities.clear();
    sylptn_probabilities.clear();
    wordgrp_probabilities.clear();
    max_syllable_count = 0;
    min_syllable_count = 0;
    nb_words = 0;
}

void Generator::SaveToFile(std::string path){
    std::ofstream File(path);
    if (!File.is_open()){
        return;
    }
    std::string lgstr = LetterGroup::LGStringFromLetterGroups(letter_groups);
    std::string spstr = LetterGroup::SPStringFromSyllablePatterns(syllable_patterns);
    std::string isepstr = LetterGroup::SPStringFromSyllablePatterns(excluded_intersylpatterns);
    std::set<std::string> added_attrs = {};
    File << "[settings]\n";
    File << "[generator]\n";
    File << std::to_string(nb_words) + "," +
            std::to_string(min_syllable_count) + "," +
            std::to_string(max_syllable_count) + ",\n";
    File << "[letter groups]\n";
    File << lgstr + "\n";
    File << "[syllable patterns]\n";
    File << spstr + "\n";
    File << "[excluded intersyllabic patterns]\n";
    File << isepstr + "\n";
    File << "[word groups]\n";
    for (WordGroup grp : word_groups){
        std::string gstr = grp.group_identifier + ",";
        for (WordAttribute attr: grp.possible_attributes){
            gstr += attr.attribute_identifier + ",";
        }
        File << gstr + "\n";
    }
    File << "[word group attributes]\n";
    for (WordGroup grp : word_groups){
        for (WordAttribute attr: grp.possible_attributes){
            // if not attr already added
            if (added_attrs.find(attr.attribute_identifier) == added_attrs.end()){
                added_attrs.insert(attr.attribute_identifier);
                std::string pstr = WordAttributeFunctionPreset::GetWattrPresetName(attr.attribute_func_preset.func_preset);
                std::string atrstr = attr.attribute_identifier + "," + pstr + ",";
                std::string argstr;
                if (attr.attribute_func_preset.func_preset == ENUM_WATTR_PRESET_ADD_PREFIX ||
                    attr.attribute_func_preset.func_preset == ENUM_WATTR_PRESET_ADD_SUFFIX){
                    argstr += (Syllable::ArgStringFromSyllables(std::get<std::vector<Syllable>>(attr.attribute_func_arguments[0]))) + ",";
                }
                atrstr += argstr;
                File << atrstr + "\n";
            }
        }
    }
    File << "[probabilities]\n";
    File << "{syllable patterns}\n";
    for (unsigned int i=0; i<syllable_patterns.size(); i++){
        File << LetterGroup::SPStringFromSyllablePattern(syllable_patterns[i]) + ":";
        File << std::to_string(GetSylPtnProbability(syllable_patterns[i]).value) + "\n";
    }
    File << "{letters}\n";
    for (unsigned int i=0; i<letter_groups.size(); i++){
        LetterGroup grp = letter_groups[i];
        std::string grpltrstr;
        for (unsigned int j=0; j<grp.letters.size(); j++){
            grpltrstr += grp.letters[j].character + ":";
            grpltrstr += std::to_string(GetLetterProbability(grp.letters[j], grp).value) + ",";
        }
        File << grpltrstr + "\n";
    }
    File << "{word groups}\n";
    for (unsigned int i=0; i<word_groups.size(); i++){
        WordGroup grp = word_groups[i];
        File << grp.group_identifier + ":";
        File << std::to_string(GetWordGrpProbability(grp).value) + "\n";
    }
    File << "{word group attributes}\n";
    for (unsigned int i=0; i<word_groups.size(); i++){
        WordGroup grp = word_groups[i];
        std::string grpattrstr;
        for (unsigned int j=0; j<grp.possible_attributes.size(); j++){
            WordAttribute attr = grp.possible_attributes[j];
            grpattrstr += attr.attribute_identifier + ":";
            grpattrstr += std::to_string(GetWordAttrProbability(attr, grp).value) + ",";
        }
        File << grpattrstr + "\n";
    }
    File << "[end]";
    File.close();
}

// holy shit, this is unclean, this is unsanitary, this is unholy
bool Generator::LoadFromFile(std::string path){
    std::ifstream File(path);
    if (!File.is_open()){
        return false;
    }
    ClearSettings();
    std::string line;
    std::vector<std::string> tokens;
    bool end;
    std::getline(File, line);
    if (line != "[settings]"){
        return false;
    }
    std::getline(File, line);
    if (line != "[generator]"){
        return false;
    }
    std::getline(File, line);
    tokens = split(line, ',');
    if (tokens.size() < 3){
        return false;
    }
    nb_words = std::stoi(tokens[0]);
    min_syllable_count = std::stoi(tokens[1]);
    max_syllable_count = std::stoi(tokens[2]);
    std::getline(File, line);
    if (line != "[letter groups]"){
        return false;
    }
    std::string ltrstr;
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '['){
            end = true;
        }
        else{
            ltrstr += line + "\n";
        }
    }
    letter_groups = LetterGroup::LetterGroupsFromLGString(ltrstr);
    if (line != "[syllable patterns]"){
        return false;
    }
    std::string sylstr;
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '['){
            end = true;
        }
        else{
            sylstr += line + "\n";
        }
    }
    if (LetterGroup::SyllablePatternsFromSPString(sylstr, &letter_groups, &syllable_patterns) == 1){
        return false;
    }
    if (line != "[excluded intersyllabic patterns]"){
        return false;
    }
    std::string e_isylstr;
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '['){
            end = true;
        }
        else{
            e_isylstr += line + "\n";
        }
    }
    if (LetterGroup::SyllablePatternsFromSPString(e_isylstr, &letter_groups, &excluded_intersylpatterns) == 1){
        return false;
    }
    if (line != "[word groups]"){
        return false;
    }
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '['){
            end = true;
        }
        else{
            tokens = split(line, ',');
            if (tokens.empty()){
                return false;
            }
            WordGroup grp;
            for (unsigned int i=0; i<tokens.size(); i++){
                if (i==0){
                    grp.group_identifier = tokens[i];
                }
                else{
                    WordAttribute attr;
                    attr.attribute_identifier = tokens[i];
                    grp.possible_attributes.push_back(attr);
                }
            }
            word_groups.push_back(grp);
        }
    }
    if (line != "[word group attributes]"){
        return false;
    }
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '['){
            end = true;
        }
        else{
            tokens = split(line,',');
            if (tokens.size() < 2){
                return false;
            }
            WordAttribute attr;
            attr.attribute_identifier = tokens[0];
            attr.attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[
                WordAttributeFunctionPreset::GetWattrPresetEnum(tokens[1])];
            if (attr.attribute_func_preset.func_preset == ENUM_WATTR_PRESET_ADD_PREFIX){
                std::vector<Syllable> arg1;
                if (Syllable::SyllablesFromArgString(tokens[2], &letter_groups, &arg1) == 1){
                    return false;
                }
                attr.attribute_func_arguments.push_back(arg1);
                attr.attribute_function = [arg1](Word *word) {WordAttributeFunctionPreset::WATTR_PRESET_ADD_PREFIX(arg1, word);};
            }
            else if (attr.attribute_func_preset.func_preset == ENUM_WATTR_PRESET_ADD_SUFFIX){
                std::vector<Syllable> arg1;
                if (Syllable::SyllablesFromArgString(tokens[2], &letter_groups, &arg1) == 1){
                    return false;
                }
                attr.attribute_func_arguments.push_back(arg1);
                attr.attribute_function = [arg1](Word *word) {WordAttributeFunctionPreset::WATTR_PRESET_ADD_SUFFIX(arg1, word);};
            }
            else if (attr.attribute_func_preset.func_preset == ENUM_WATTR_PRESET_DONOTHING){
                attr.attribute_func_arguments = {};
                attr.attribute_function = WordAttributeFunctionPreset::WATTR_PRESET_DONOTHING;
            }
            else {
                break;
            }
            for (unsigned int i=0; i<word_groups.size(); i++){
                for (unsigned int j=0; j<word_groups[i].possible_attributes.size(); j++){
                    if (word_groups[i].possible_attributes[j].attribute_identifier == attr.attribute_identifier){
                        word_groups[i].possible_attributes[j] = attr;
                    }
                }
            }
        }
    }
    // this following code relies on line order therefore the user should not modify the save file
    if (line != "[probabilities]"){
        return false;
    }
    std::getline(File, line);
    if (line != "{syllable patterns}"){
        return false;
    }
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '{'){
            end = true;
        }
        else{
            tokens = split(line, ':');
            if (tokens.size() != 2){
                return false;
            }
            Probability pb;
            pb.value = std::stof(tokens[1]);
            sylptn_probabilities.push_back(pb);
        }
    }
    if (line != "{letters}"){
        return false;
    }
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '{'){
            end = true;
        }
        else{
            std::vector<Probability> grppbs;
            std::vector<std::string> grptoks = split(line, ',');
            for (std::string grptok : grptoks){
                tokens = split(grptok, ':');
                if (tokens.size() != 2){
                    return false;
                }
                Probability pb;
                pb.value = std::stof(tokens[1]);
                grppbs.push_back(pb);
            }
            letter_probabilities.push_back(grppbs);
        }
    }
    if (line != "{word groups}"){
        return false;
    }
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '{'){
            end = true;
        }
        else{
            tokens = split(line, ':');
            if (tokens.size() != 2){
                return false;
            }
            Probability pb;
            pb.value = std::stof(tokens[1]);
            wordgrp_probabilities.push_back(pb);
        }
    }
    if (line!= "{word group attributes}"){
        return false;
    }
    end = false;
    while (!end){
        if (!std::getline(File, line)){
            return false;
        }
        if (line[0] == '['){
            end = true;
        }
        else{
            std::vector<Probability> grppbs;
            std::vector<std::string> grptoks = split(line, ',');
            for (std::string grptok : grptoks){
                tokens = split(grptok, ':');
                if (tokens.size() != 2){
                    return false;
                }
                Probability pb;
                pb.value = std::stof(tokens[1]);
                grppbs.push_back(pb);
            }
            wordattr_probabilities.push_back(grppbs);
        }
    }
    if (line != "[end]"){
        return false;
    }
    File.close();
    return true;
}
