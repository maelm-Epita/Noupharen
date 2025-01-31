#pragma once

#include <gender.hpp>
#include <word.hpp>

// A noun is a word which has a gender which can apply rules onto it
class Noun : Word{
  struct Gender *gender;
};
