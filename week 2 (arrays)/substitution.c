#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Function prototypes
bool noNonAlphabeticCharacters(string key);
bool noRepeatedCharacters(string key);
string encipher(string plaintext,string key);

int main(int argc, string argv[]){

    // Check if exactly two command line arguments were provided (1 for the name of the program, 1 for the key)
    if(argc != 2){
        printf("Usage: ./substitution key");
        return 1; // error
    }

    string key = argv[1];

    // Check if the key is exactly 26 digits
    int length = strlen(key);

    if(length != 26){
        printf("Key length must be exactly 26\n");
        return 1; //error
    }

    // Check if any of the character is non-alphabetic
    if(!noNonAlphabeticCharacters(key)){
        // This means that there is at least 1 non-alphabetic character in the key
        printf("Use only alphabetic characters in the key \n");
        return 1; // Error
    }

    if(!noRepeatedCharacters(key)){
        // This means that the key includes repeated characters
        printf("Don't repeat a character more than once \n");
        return 1; // Error
    }

    // Key is valid
    // Request plaintext from user
    string plaintext = get_string("Plaintext:");

    // Encipher
    // Create array for ciphertext that is the same length as the key array
    // BUT plus 1, because we have to manually add the sentinel value (trailing 0 to signal the end of the string)

    char ciphertext[strlen(plaintext)+1];

    // Loop through all the characters in the plaintext array
    for(int i = 0; i < strlen(plaintext); i++){
        int newIndex = 0;

        // if the current character is not alphabetic (might be a space, or a question mark, etc), do nothing
        // Just add the character as-is to the ciphertext
        if(!isalpha(plaintext[i])){
            ciphertext[i] = plaintext[i];
        } else {
            // The character is an alphabetic character. Substitute it.
            // if uppercase, subtract 65 to get the index of the key array
        if(isupper(plaintext[i])){
            newIndex = plaintext[i] - 65;
            // Add the character to the ciphertext, but make sure to user toupper
            ciphertext[i] = toupper(key[newIndex]);
        } else if(islower(plaintext[i])){
            newIndex = plaintext[i] - 97;
            // Add the character to the ciphertext, but make sure to use tolower
            ciphertext[i] = tolower(key[newIndex]);
        }
        }
    }

    // Add the sentinel value (trailing 0) for the ciphertext to signal the end of the string
    ciphertext[strlen(plaintext)] = '\0';

    printf("ciphertext: %s\n",ciphertext);
    return 0; //all good
}

bool noNonAlphabeticCharacters(string key){
    // Check if there are non alphabetic characters
    bool result = true;

    for (int i = 0; i < strlen(key); i++){
        if(!isalpha(key[i])){
            // the current character does not belong to the alphabet
            result = false;
            // you don't have to proceed with the loop
            break;
        }
    }

    return result;
}

bool noRepeatedCharacters(string key){
    // Loop through all the characters in the array
    int charcounter = 0;
    bool result = true;


    for(int i = 0; i < strlen(key); i++){
        // Now do a second loop, so you can how often the current character appears in the string
        // Increment a counter whenever this happens
        // Always reset the charcounter for every loop
        charcounter = 0;
        // In the higher loop, check if the counter is higher than 1
        // If that's the case, the character appears more than once
        for (int j = 0; j < strlen(key); j++){
            if(key[i] == key[j]){
                charcounter++;
            }
        }

        if(charcounter > 1){
        // There are characters that appear more than once
        result = false;
        // exit the loop
        break;
    }
    }

return result;

}

