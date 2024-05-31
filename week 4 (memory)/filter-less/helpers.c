#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all rows
    for (int i = 0; i < height; i++){
        // Loop through all rows
        for (int j = 0; j < width; j++){
            // get RGB values for each pixel
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            // Calculate average of RGB values
            double dblAverage = (float)(blue+green+red)/3;
            // round to nearest integer
            int average = round(dblAverage);


            // Set RGB values to average
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // Loop through all rows
    for (int i = 0; i < height; i++){
        // Loop through all rows
        for (int j = 0; j < width; j++){
            // get RGB values for each pixel
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            // Convert to sepia and round to nearest integer
            int sepiaRed = round((red * .393) + (green * .769) + (blue * .189));
            int sepiaGreen = round((red * .349) + (green * .686) + (blue * .168));
            int sepiaBlue = round((red * .272) + (green * .534) + (blue * .131));

            // Cap at 255
            if (sepiaRed > 255){
                sepiaRed = 255;
            }

            if (sepiaGreen > 255){
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255){
                sepiaBlue = 255;
            }

            // Set RGB values to average
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;

        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all rows
    for (int i = 0; i < height; i++){
        // Loop through all rows
        for (int j = 0; j < width; j++){
            int widthZeroBased = width - 1;

            if (j <= (widthZeroBased-j)){
                RGBTRIPLE tmp = image[i][j];
                image[i][j] = image[i][widthZeroBased-j];
                image[i][widthZeroBased-j] = tmp;
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop through all the pixels

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double averageRed = 0;
            double averageGreen = 0;
            double averageBlue = 0;
            int averageCounter = 0;

            // Get averages from current cell
            averageRed += copy[i][j].rgbtRed;
            averageGreen += copy[i][j].rgbtGreen;
            averageBlue += copy[i][j].rgbtBlue;
            averageCounter++;

            if (j-1 >= 0){
            // Get averages from cell in left column
            averageRed += copy[i][j-1].rgbtRed;
            averageGreen += copy[i][j-1].rgbtGreen;
            averageBlue += copy[i][j-1].rgbtBlue;
            averageCounter++;
            }

            if (j+1 <= width-1){
            // Get averages from cell in right column
            averageRed += copy[i][j+1].rgbtRed;
            averageGreen += copy[i][j+1].rgbtGreen;
            averageBlue += copy[i][j+1].rgbtBlue;
            averageCounter++;
            }

            if (i-1 >= 0){
            // Get averages from cell in top row
            averageRed += copy[i-1][j].rgbtRed;
            averageGreen += copy[i-1][j].rgbtGreen;
            averageBlue += copy[i-1][j].rgbtBlue;
            averageCounter++;
            }


            if(i+1 <= height-1){
            // Get averages from cell in bottom row
            averageRed += copy[i+1][j].rgbtRed;
            averageGreen += copy[i+1][j].rgbtGreen;
            averageBlue += copy[i+1][j].rgbtBlue;
            averageCounter++;
            }

            if(i-1 >= 0 && j-1 >= 0){
            // Get averages from cell in top left
            averageRed += copy[i-1][j-1].rgbtRed;
            averageGreen += copy[i-1][j-1].rgbtGreen;
            averageBlue += copy[i-1][j-1].rgbtBlue;
            averageCounter++;
            }

            if(i-1 >= 0 && j+1 <= width-1){
// Get averages from cell in top right
            averageRed += copy[i-1][j+1].rgbtRed;
            averageGreen += copy[i-1][j+1].rgbtGreen;
            averageBlue += copy[i-1][j+1].rgbtBlue;
            averageCounter++;
            }

            if(i+1 <= height-1 && j-1 >= 0){
// Get averages from cell in bottom left
            averageRed += copy[i+1][j-1].rgbtRed;
            averageGreen += copy[i+1][j-1].rgbtGreen;
            averageBlue += copy[i+1][j-1].rgbtBlue;
            averageCounter++;
            }

            if(i+1 <= height-1 && j+1 <= width-1){
// Get averages from cell in bottom right
            averageRed += copy[i+1][j+1].rgbtRed;
            averageGreen += copy[i+1][j+1].rgbtGreen;
            averageBlue += copy[i+1][j+1].rgbtBlue;
            averageCounter++;
            }


            // Calculate averages
            averageRed = averageRed / averageCounter;
            averageGreen = averageGreen / averageCounter;
            averageBlue = averageBlue / averageCounter;


            // Create new pixel
            image[i][j].rgbtRed = round(averageRed);
            image[i][j].rgbtGreen = round(averageGreen);
            image[i][j].rgbtBlue = round(averageBlue);



        }
    }


    return;
}
