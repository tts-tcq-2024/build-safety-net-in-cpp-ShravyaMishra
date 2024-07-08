#include "Soundex.h"

char Soundex::getSoundexCode(char c) {
    switch (std::tolower(c)) {
        case 'b':
        case 'f':
        case 'p':
        case 'v':
            return '1';
        case 'c':
        case 'g':
        case 'j':
        case 'k':
        case 'q':
        case 's':
        case 'x':
        case 'z':
            return '2';
        case 'd':
        case 't':
            return '3';
        case 'l':
            return '4';
        case 'm':
        case 'n':
            return '5';
        case 'r':
            return '6';
        default:
            return '0';
    }
}

bool Soundex::isHW(char c) {
    return std::tolower(c) == 'h' || std::tolower(c) == 'w';
}

bool Soundex::shouldAppend(char currentCode, char lastCode, char nextChar) {
    if (currentCode == '0')
        return true;
    if (currentCode == lastCode)
        return false;
    if (isHW(nextChar))
        return false;
    return true;
}

std::string Soundex::accumulateSoundexCodes(const std::string& name) {
    if (name.empty())
        return "0000";

    std::string soundexCodes;
    soundexCodes += std::toupper(name[0]);
    char lastCode = getSoundexCode(name[0]);

    for (size_t i = 1; i < name.length() && soundexCodes.length() < 4; ++i) {
        char code = getSoundexCode(name[i]);
        if (shouldAppend(code, lastCode, name[i])) {
            soundexCodes += code;
            lastCode = code;
        }
    }

    while (soundexCodes.length() < 4)
        soundexCodes += '0';

    return soundexCodes;
}

std::string Soundex::padSoundex(const std::string& soundex) {
    std::string paddedSoundex = soundex;
    while (paddedSoundex.length() < 4)
        paddedSoundex += '0';
    return paddedSoundex.substr(0, 4);
}

std::string Soundex::generateSoundex(const std::string& name) {
    std::string accumulatedCodes = accumulateSoundexCodes(name);
    return padSoundex(accumulatedCodes);
}


