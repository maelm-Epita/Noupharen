#pragma once

#include <gender.hpp>
#include <word.hpp>

// A noun is a word which has a gender which can apply rules onto it
struct Noun : Word{
  Gender *gender;
};
