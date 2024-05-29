// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Header is always 44 bytes long
    uint8_t buffer[HEADER_SIZE];
    // Read first 44 bytes of input file, and put it into the buffer
    fread(buffer,HEADER_SIZE,1,input);
    // Now write the buffer to the output file
    fwrite(buffer,HEADER_SIZE,1,output);


    // TODO: Read samples from input file and write updated data to output file
    // Fread is now pointing to byte 45 (since we already read the first 44)
    // Create a new buffer, this time with the int16_t datetype since we'll handle two bytes at a time (2 bytes make up 1 sample)
    int16_t buffer2;
    // Load the next 2 bytes from the input file into the buffer variable
    // The buffer has to be a POINTER (use ampersand!) otherwise "incompatible integer to pointer conversion"
    while(fread(&buffer2,sizeof(int16_t),1,input)!=0){
        // Adjust buffer with factor
        buffer2 = buffer2 * factor;
        // Now write this to the output file
        fwrite(&buffer2,sizeof(int16_t),1,output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
