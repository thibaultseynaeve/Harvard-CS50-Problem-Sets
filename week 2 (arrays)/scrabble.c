#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Prototypes
int getPoints(string word);

// Global variables

// declare array with all the points and initialize it
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void){

    // Get word from player 1
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Declare variable for the points and initialize it by running the getPoints function
    int word1Points = getPoints(word1);
    int word2Points = getPoints(word2);

    // Decide who won
    if(word1Points > word2Points){
        // Player 1 won
        printf("Player 1 wins!\n");
    } else if(word2Points > word1Points){
        // Player 2 won
        printf("Player 2 wins!\n");
    } else {
        // Only other possible outcome is that it's a tie
        printf("Tie!\n");
    }

}

int getPoints(string word){
    int pointsEarned = 0;

    // Get length of string so we can loop through it
    int length = strlen(word);

    // Loop through all the digits in the word
    for (int i = 0; i < length; i++){
        // store current letter in variable
        char letter = word[i];
        // Transform the letter to lowercase
        letter = tolower(letter);
        // Now we need to find the index for the points array
        // This is the ASCII value of the current letter minus 97 (since that's the ASCII value for a lowercase a)
        int indexForPointsArray = letter - 97;
        // Assign the points and store them in a variable
        // But check if the 0 or higher
        // Otherwise it may have been en exclamation point for example
        if(indexForPointsArray >= 0){
            pointsEarned += points[indexForPointsArray];
        }

    }

    // Return the points
    return pointsEarned;
}
