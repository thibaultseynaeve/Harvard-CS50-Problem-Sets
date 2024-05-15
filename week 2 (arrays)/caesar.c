#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
bool checkIfDigit(string stringToCheck);

int main(int argc, string argv[]){


    // Check if argc is exactly 2 (1 for the name of the program, 1 for the key)
    // If that isn't the case, print an error and return 1 to signal the error
    if(argc != 2){
        printf("You need to specify a key. Run the program again and enter a key on the command line.\n");
        return 1;
    }

    string commandlinevalue = argv[1];

    // The argument that the user provided must be a digit
    // The function will return 'false' if one of the characters in the string isn't a digit
    if(!checkIfDigit(commandlinevalue)){
        // Not a digit, return an error
        printf("Usage: ./caesar key");
        return 1;
    }

    // Input is valid. This will be the key
    int key = atoi(commandlinevalue);

    // Get the plaintext from the user
    string plaintext = get_string("plaintext:  ");
    // Get length of string to use in loop
    int length = strlen(plaintext);

    // Declare a variable for the ciphertext
    // Make sure that this variable has enough room (the same length as the original string)
    // reserve one space for the trailing 0 to signal the end of the array
    char ciphertext[length+1];

    // Loop through every digit in the string
    for(int i = 0; i < length; i++){
        char character = plaintext[i];

        // Check if uppercase
        if(character >= 'a' && character <= 'z'){
            // It's a lowercase letter
            // Now subtract 97 to get the position of the letter in the array of letters
            int index = character - 97;
            // Now add x positions to the index (where x is the key)
            // Module 26 so that you don't end up out of bounds when the key is too high or when you're nearing the end of the alphabet (the end of the letters array)
            int encryptedIndex = (index + key)%26;
            int newCharacter = encryptedIndex + 97;
            ciphertext[i] = newCharacter;
        } else if(character >= 'A' && character <= 'Z'){
            // It's an uppercase letter
            int index = character - 65;
            // Now add x positions to the index (where x is the key)
            // Module 26 so that you don't end up out of bounds when the key is too high or when you're nearing the end of the alphabet (the end of the letters array)
            int encryptedIndex = (index + key)%26;
            int newCharacter = encryptedIndex + 65;
            ciphertext[i] = newCharacter;

        } else {
            // It's not a letter (possible a question mark, exclamation mark, period, etc)
            // Don't encrypt, just add the character to the ciphertext as-is
            ciphertext[i] = character;
        }


    }

    // Add the trailing zero to signal the end of the array so we don't get unexpected output
    ciphertext[length] = '\0';

    // Print the result
    printf("ciphertext: %s\n",ciphertext);

    // Return with 0 (all good)
    return 0;


}

bool checkIfDigit(string stringToCheck){
    // We use the isdigit() function, but we have to pass a character
    // So we'll have to loop through the string, and check if every character is a digit
    // if one of them isn't a digit, we return an error
    int length = strlen(stringToCheck);
    bool result = true;
    for(int i = 0; i < length; i++){
        if(!isdigit(stringToCheck[i])){
            // The current character is not a digit
            // Change value of result
            result = false;
            // Exit this loop
            break;
        }
    }

    // Return the result
    return result;
}
