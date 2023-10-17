#include "pch.h"
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>

extern "C" {
    __declspec(dllexport) char* encrypt(char* rawText, int key) {
        int length = strlen(rawText);
        std::stringstream encryptedStream;

        for (int i = 0; i < length; i++) {
            char character = rawText[i];
            int encryptedValue = (character + key) % 128;
            std::stringstream hexStream;
            hexStream << std::hex << std::setw(2) << std::setfill('0') << encryptedValue;
            encryptedStream << hexStream.str();
        }

        std::string encryptedString = encryptedStream.str();
        char* encryptedText = new char[encryptedString.length() + 1];

        strcpy_s(encryptedText, encryptedString.length() + 1, encryptedString.c_str());

        return encryptedText;
    }

    __declspec(dllexport) char* decrypt(char* rawText, int key) {
        int length = strlen(rawText) / 2;
        std::stringstream decryptedStream;

        for (int i = 0; i < length; i++) {
            std::string hex = std::string(rawText + i * 2, 2);
            int decryptedValue = (std::stoi(hex, 0, 16) + 128 - key) % 128;
            decryptedStream << static_cast<char>(decryptedValue);
        }

        std::string decryptedString = decryptedStream.str();
        char* decryptedText = new char[decryptedString.length() + 1];

        strcpy_s(decryptedText, decryptedString.length() + 1, decryptedString.c_str());

        return decryptedText;
    }
}
