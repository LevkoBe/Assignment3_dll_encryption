#include <iostream>
#include <windows.h>
#include <string>

typedef std::string (*encrypt_ptr_t)(std::string, int);
typedef std::string (*decrypt_ptr_t)(std::string, int);

void help() {
    std::cout << "For encryption, please, write: -e [k], where k is the key value;" << std::endl;
    std::cout << "For decryption, please, write: -d [k], where k is the key value;" << std::endl;
    std::cout << "For getting help, please, write: -h;" << std::endl;
    std::cout << "To exit the program, please, write: -x;" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string ar = argv[1];
    if (ar == "-h")
    {
        help();
    }
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


    std::string command, input;
    int key;
    while (true)
    {
        std::cout << "Enter a command ('-e', '-d', '-h', '-x') and a key (e.g., '-e 3'): ";
        std::cin >> command;

        if (command == "-h") {
            help();
        }
        else if (command == "-e" || command == "-d") {
            std::cin >> key;

            std::cout << "Enter your text: ";
            std::cin.ignore();
            std::getline(std::cin, input);
            key = key % 128;
            if (command == "-e") {
                std::string encrypted = encrypt_ptr(input, key);
                std::cout << "Encrypted text: ";
                for (int i = 0; i < encrypted.length(); i++)
                {
                    printf("%x", encrypted[i]);
                }
                std::cout << std::endl;
            }
            else if (command == "-d") {
                std::string decrypted = decrypt_ptr(input, key);
                std::cout << "Decrypted text: " << decrypted << std::endl;
            }
        }
        else if (command == "-x") {
            break;
        }
        else {
            std::cout << "Invalid command. Use '-h' for help." << std::endl;
        }
    }

    FreeLibrary(handle);

    return 0;
}
