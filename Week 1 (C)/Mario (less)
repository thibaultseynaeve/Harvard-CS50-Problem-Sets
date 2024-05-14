#include <cs50.h>
#include <stdio.h>

void print_row(int spaces,int bricks);

int main(void){

    // Get the height of the pyramid
    // This is also the width of the bottom row
    // If the height is 3, the bottom row is 3 bricks
    // Reprompt the user if the input is not greater than 0 or not an int altogether
    int height;
    do{
        height = get_int("Height: ");
    } while (height <= 0);

    // If the height is 3, print 3 rows
    for (int i = 1; i <= height; i++){
        // We need to calculate the required spaces and bricks before we print the row
        // Spaces = the height of the pyramid minus the counter (i)
        // Bricks = the height of the pyramid minus the spaces
        int spaces = height - i;
        int bricks = height - spaces;
        print_row(spaces,bricks);
    }

}

void print_row(int spaces,int bricks){
    // first print spaces in the row (if any)
    for (int i = 0; i < spaces; i++){
        printf(" ");
    }

    // Now print bricks
    for (int i = 0; i < bricks; i++){
        printf("#");
    }

    // The row is now done, make a new line
    printf("\n");
}
