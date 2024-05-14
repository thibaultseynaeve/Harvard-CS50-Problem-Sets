#include <cs50.h>
#include <stdio.h>

int main(void){
    // Get integer (cents) from user
    // Repeat this prompt until the user enters a value higher than 0
    int change;
    do{
        change = get_int("Change owed: ");
    } while (change < 0);

    // Define possible coints
    int coincounter = 0;

    // We use module, this will calculate the remainder
    // If the remainder is the same as the starting value, this means that we starting value is higher than the coin
    // So we need to move to a lower coin

    // We need to repeat this loop until the change is 0

    while (change != 0){

        if(change % 25 != change){
            // The remainder is not equal to the starting value
            // So we can use the coin!
            change = change - 25;
            // Increment the coin counter
            coincounter++;
        } else if(change % 10 != change){
            // The remainder is not equal to the starting value
            // So we can use the coin!
            change = change - 10;
            // Increment the coin counter
            coincounter++;
        } else if(change % 5 != change){
            // The remainder is not equal to the starting value
            // So we can use the coin!
            change = change - 5;
            // Increment the coin counter
            coincounter++;
        } else if(change % 1 != change){
            // The remainder is not equal to the starting value
            // So we can use the coin!
            change = change - 1;
            // Increment the coin counter
            coincounter++;
        }


    } // End while loop

    // Display the number of coins needed
    printf("%i\n",coincounter);


}
