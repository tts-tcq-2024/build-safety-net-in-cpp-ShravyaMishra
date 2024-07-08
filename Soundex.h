#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <string>

class Soundex {
public:
    static char getSoundexCode(char c);
    static bool isHW(char c);
    static bool shouldAppend(char currentCode, char lastCode, char nextChar);
    static std::string accumulateSoundexCodes(const std::string& name);
    static std::string padSoundex(const std::string& soundex);
    static std::string generateSoundex(const std::string& name);
};

#endif // SOUNDEX_H
