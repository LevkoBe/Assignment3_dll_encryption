#include <iostream>
#include <windows.h>

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);

int main() {
    HINSTANCE handle = LoadLibrary(TEXT("LibraryCode.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        std::cout << "Library not found" << std::endl;
        return 1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
    if (encrypt_ptr == nullptr) {
        std::cout << "Encrypt function not found" << std::endl;
        FreeLibrary(handle);
        return 1;
    }

    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");
    if (decrypt_ptr == nullptr) {
        std::cout << "Decrypt function not found" << std::endl;
        FreeLibrary(handle);
        return 1;
    }


    char text[] = "Hello, World!";
    int key = 3;
    char* encryptedText = encrypt_ptr(text, key);
    std::cout << "Encrypted: " << encryptedText << std::endl;

    char* decryptedText = decrypt_ptr(encryptedText, key);
    std::cout << "Decrypted: " << decryptedText << std::endl;

    FreeLibrary(handle);

    delete[] encryptedText;
    delete[] decryptedText;

    return 0;
}
