#include "pch.h"
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>

extern "C" {
    __declspec(dllexport) std::string encrypt(std::string rawText, int key) {
        int length = rawText.length();
        std::stringstream encryptedStream;

        for (int i = 0; i < length; i++) {
            char character = rawText[i];
            int encryptedValue = (character + key) % 128;
            std::stringstream hexStream;
            hexStream << std::hex << std::setw(2) << std::setfill('0') << encryptedValue;
            encryptedStream << hexStream.str();
        }

        std::string encryptedString = encryptedStream.str();

        return encryptedString;
    }

    __declspec(dllexport) std::string decrypt(std::string rawText, int key) {
        int length = rawText.length() / 2;
        std::stringstream decryptedStream;

        for (int i = 0; i < length; i++) {
            std::string hex = rawText.substr(i * 2, 2);
            int decryptedValue = (std::stoi(hex, 0, 16) - key);
            if (decryptedValue < 0) {
                decryptedValue += 128;
            }
            decryptedStream << static_cast<char>(decryptedValue);
        }

        std::string decryptedString = decryptedStream.str();

        return decryptedString;
    }

}
