#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

// Memory card stores data in blocks of 512 bytes
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
 // Counter for jpg filenames
 int jpgcounter = -1;

 //If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1
 if(argc != 2){
    printf("Usage: ./recover <filename>\n");
    return 1;
 }

 // Open memory card file
 FILE *card = fopen(argv[1],"r");

 // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1
 if (card == NULL){
    printf("Image could not be read\n");
    return 1;
 }

 // Memory card stores data in blocks of 512 bytes
 uint8_t buffer[BLOCK_SIZE];

 // fread returns the amount of bytes that it read
 // when this isn't 512 anymore, we've reached the end of the memory card
 FILE *file = NULL;

 while(fread(buffer,1,BLOCK_SIZE,card) == BLOCK_SIZE){
    // Buffer now contains 512 bytes

    // Check if the four first bytes indicate the start of a JPG

    // Use bitwise operator to check if buffer[3] is 0xe0, 0xe1, 0xe2 ... 0xef
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
        // Currently loaded chunk of data in buffer is a new jpeg
        // Close current file (if there is already one)
        if(file != NULL){
            fclose(file);
        }

        // Increment counter
        jpgcounter++;
        // create new filename
        char filename[8];
        sprintf(filename,"%03i.jpg",jpgcounter);
        // Create new jpeg file
        file = fopen(filename,"w");
        // Write buffer to jpeg file
        fwrite(buffer,1,BLOCK_SIZE,file);


    } else {
        // Not a new jpg
        // It's the remaining data of a current jpg
        // Add the buffer to the wile
        // If the file is still NULL, we haven't yet found the first jpg yet so we don't need to write any data
        if (file != NULL){
            fwrite(buffer,1,BLOCK_SIZE,file);
        }

    }

 }
 fclose(file);
 // Close the memory card file
 fclose(card);
}
