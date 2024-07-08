#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <unordered_map>
#include <cctype>
#include <string>
#include <numeric>

char getSoundexCode(char c);
bool isHW(char c);
bool shouldAppend(char code, char prevCode, char currentChar);
std::string accumulateSoundexCodes(const std::string& name);
std::string padSoundex(const std::string& soundex);
std::string generateSoundex(const std::string& name);

#endif // SOUNDEX_H
