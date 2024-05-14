#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Prototypes
int getNumberOfSentences(string textToCheck);
int getNumberOfWords(string textToCheck);
double getReadabilityIndex(string textToCheck);
int lengthWithoutMarks(string textToCheck);

int main(void){
    string userinput = get_string("Text: ");
    int readabilityIndex = round(getReadabilityIndex(userinput));

    if(readabilityIndex < 1){
        printf("Before Grade 1\n");
    } else if(readabilityIndex >= 16){
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n",readabilityIndex);
    }

}

int getNumberOfWords(string textToCheck){
    // Look for spaces and increment a counter
    int numberOfWords = 0;
    int length = strlen(textToCheck);

    // Loop through every character
    for(int i = 0; i < length; i++){
        // Check for a space
        if(textToCheck[i] == ' '){
            // increment the counter
            numberOfWords++;
        }
    }

    // Increment the counter with 1, because the last word won't end with a space. it will end with an ending mark or with nothing at all
    numberOfWords++;

    return numberOfWords;

}

int getNumberOfSentences(string textToCheck){
    // A sentence ends with a period, an exclamation mark or a question mark
    // Loop through every character in the string
    // If you encounter one of these ending marks, increment the counter
    int numberOfSentences = 0;
    int length = strlen(textToCheck);

    // Loop through every character
    for(int i = 0; i < length; i++){
        // Check for an ending mark (period, question mark, exclamation mark)
        if(textToCheck[i] == '.' || textToCheck[i] == '!' || textToCheck[i] == '?'){
            // increment the counter
            numberOfSentences++;
        }
    }
    return numberOfSentences;
}

double getReadabilityIndex(string textToCheck){
    // Get the number of sentences
    int numberOfSentences = getNumberOfSentences(textToCheck);
    // Get the number of words
    int numberOfWords = getNumberOfWords(textToCheck);
    // Get the length without spaces
    int length = lengthWithoutMarks(textToCheck); // should be 65

    // Calculate average letters per word
    // length of string array / numbers of words
    double averageLettersPerWord = (float) length / (float) numberOfWords;

    double l = (double) averageLettersPerWord * 100;
    double s = ((double)numberOfSentences/(double)numberOfWords)*100;

    double index = 0.0588 * l - 0.296 * s - 15.8;

    return index;
}

int lengthWithoutMarks(string textToCheck){
    // This function returns the length of the array, but excluding spaces, exclamation marks, question marks, etc
    int length = strlen(textToCheck);

    int markscounter = 0;

    // Loop through every char
    for(int i = 0; i < length; i++){
        // check if the current char is a space
        // first convert it to lowercase
        char currentchar = tolower(textToCheck[i]);

        if(currentchar >= 'a' && currentchar <= 'z'){
            // all good! the current char is a-z or A-Z
        } else {
            // no good! the current char does not belong to the alphabet.
            // increment the counter
            markscounter++;
        }
    }

    // return length of string minus the spaces
    return length - markscounter;
}


