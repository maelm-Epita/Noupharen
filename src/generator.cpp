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
    File.close();
}

bool Generator::LoadFromFile(std::string path){
    std::ifstream File(path);
    if (!File.is_open()){
        return false;
    }
    std::string line;
    std::vector<std::string> tokens;
    bool end;
    std::getline(File, line);
    if (line != "[settings]"){
        return false;
    }
    unsigned int n_w, min_s, max_s;
    std::vector<LetterGroup> ltrg;
    std::vector<WordGroup> wgrp;
    std::vector<SyllablePattern> sylptn, e_isylptn;
    std::vector<Probability> sylptn_pb, wordgrp_pb;
    std::vector<std::vector<Probability>> letter_pb, wordattr_pb;
    std::getline(File, line);
    if (line != "[generator]"){
        return false;
    }
    std::getline(File, line);
    tokens = split(line, ',');
    if (tokens.size() < 3){
        return false;
    }
    n_w = std::stoi(tokens[0]);
    min_s = std::stoi(tokens[1]);
    max_s = std::stoi(tokens[2]);
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
            std::vector<Probability> grppbs;
            tokens = split_last(line, ':');
            if (tokens.size()!=2){
                return false;
            }
            tokens = split(tokens[1], ' ');
            for (std::string tok : tokens){
                Probability pb;
                pb.value = 1;
                grppbs.push_back(pb);
            }
            letter_pb.push_back(grppbs);
        }
    }
    ltrg = LetterGroup::LetterGroupsFromLGString(ltrstr);
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
            Probability pb;
            pb.value = 1;
            sylptn_pb.push_back(pb);
        }
    }
    if (!LetterGroup::SyllablePatternsFromSPString(sylstr, &ltrg, &sylptn)){
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
    if (!LetterGroup::SyllablePatternsFromSPString(e_isylstr, &ltrg, &e_isylptn)){
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
            Probability pb;
            pb.value = 1;
            wordgrp_pb.push_back(pb);
            std::vector<Probability> grppbs;
            for (unsigned int i=0; i<tokens.size(); i++){
                if (i==0){
                    grp.group_identifier = tokens[i];
                }
                else{
                    WordAttribute attr;
                    attr.attribute_identifier = tokens[i];
                    grp.possible_attributes.push_back(attr);
                    Probability pb;
                    pb.value = 1;
                    grppbs.push_back(pb);
                }
            }
            wgrp.push_back(grp);
            wordattr_pb.push_back(grppbs);
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
                if (!Syllable::SyllablesFromArgString(tokens[2], &ltrg, &arg1)){
                    return false;
                }
                attr.attribute_func_arguments.push_back(arg1);
                attr.attribute_function = [arg1](Word *word) {WordAttributeFunctionPreset::WATTR_PRESET_ADD_PREFIX(arg1, word);};
            }
            else if (attr.attribute_func_preset.func_preset == ENUM_WATTR_PRESET_ADD_SUFFIX){
                std::vector<Syllable> arg1;
                    if (!Syllable::SyllablesFromArgString(tokens[2], &ltrg, &arg1)){
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
            for (WordGroup grp : wgrp){
                for (WordAttribute groupattr : grp.possible_attributes){
                    if (groupattr.attribute_identifier == attr.attribute_identifier){
                        groupattr = attr;
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
    if (line != "{syllable patterns"){
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
            tokens = split_last(line, ':');
            if (tokens.size() != 2){
                return false;
            }
            // you could remove this search by just relying on the order of sylptns which should
            // be made correct by the save function however i want the user to be free to modify
            // the save file and potentially change the order of syllable patterns
            for (unsigned int i=0; i<sylptn.size(); i++){
                if (LetterGroup::SPStringFromSyllablePattern(sylptn[i]) == tokens[0]){
                    sylptn_pb[i].value = std::stof(tokens[1]);
                }
            }
        }
    }
    if (line != "{letters")
    nb_words = n_w;
    min_syllable_count = min_s;
    max_syllable_count = max_s;
    letter_groups = ltrg;
    word_groups = wgrp;
    syllable_patterns = sylptn;
    excluded_intersylpatterns = e_isylptn;
    sylptn_probabilities = sylptn_pb;
    wordgrp_probabilities = wordgrp_pb;
    letter_probabilities = letter_pb;
    wordattr_probabilities = wordattr_pb;
    File.close();
    return true;
}
