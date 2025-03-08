#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <string>

// splits the string with a token and skips the last bit
std::vector<std::string> split(std::string str, char tok);
// splits the string with a token and doesnt skip the last bit
std::vector<std::string> split_last(std::string str, char tok);

#endif // HELPERS_H
