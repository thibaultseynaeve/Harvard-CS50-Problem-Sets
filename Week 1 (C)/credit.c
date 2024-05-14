#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getAmountOfDigits(long number);
int getFirstDigit(long numberToCheck);
int getFirstTwoDigits(long numberToCheck);
bool isChecksumValid(int checksum);

int main(void){
    int sumOfUnevenDigits = 0;
    int sumOfEvenDigits = 0;

   // Get credit card number and store in long
   long creditcardnumber = get_long("Credit card number: ");
   int amountOfDigits = getAmountOfDigits(creditcardnumber);


   // Loop through all the seperate digits in the number (from right to left)
   // Do this until you have looped through all digits (we can check this because the amount of digits is stored in amountOfDigits)
   for(int i = 0; i < amountOfDigits;i++){
    long power = pow(10,i);
    long digit = (creditcardnumber / power) % 10;

    // we can use the counter to check if it's an even or uneven number
    if ((i%2)==0){
        // It's an even number
        // It starts at the last number
        // We just need to add this digit to the variable sumOfEvenDigits;
        sumOfEvenDigits += digit;

    } else {
        // It's an uneven number
        // It starts at the second to last number

         // We need to multiply every other digit by 2, and then add those products digits together (not the products, but their digits!)
         int digitTimesTwo = digit * 2;

         // Now take each digit of the result, and add it to the global variable
         for(int j = 0; j < getAmountOfDigits(digitTimesTwo);j++){
            // Now we can use module and power again to loop through all the digits
            long unevenPower = pow(10,j);
            long unevenDigit = (digitTimesTwo / unevenPower) % 10;
            // Add this digit to the global variable
            sumOfUnevenDigits += unevenDigit;
         }

    }
   }

   // Now, add the two variables together
   int result = sumOfUnevenDigits + sumOfEvenDigits;

   // Check the type of creditcard based on the amount of digits

   int firstDigit = getFirstDigit(creditcardnumber);
   int firstTwoDigits = getFirstTwoDigits(creditcardnumber);

   // Check if checksum is valid
   if(isChecksumValid(result)){
    // Valid checksum
    // Check for the type of creditcard

    if((amountOfDigits == 15) && (firstTwoDigits == 34 || firstTwoDigits == 37)){
        // Valid AMEX card
        printf("AMEX\n");
    }
    else if((amountOfDigits == 16) && (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55)){
        // Valid Mastercard
        printf("MASTERCARD\n");
    } else if((amountOfDigits == 13 || amountOfDigits == 16) && firstDigit == 4 ){
        // Valid VISA
        printf("VISA\n");
    } else {
        // INVALID
        printf("INVALID\n");
    }
   } else {
     // INVALID
    printf("INVALID\n");
   }

}

int getAmountOfDigits(long numberToCheck){
    // This function returns the number of digits in a specific number

    // Count the amount of digits
   // Divide by 10 until the result is 0

   int amountOfDigits = 0;
   long helper = numberToCheck;

   while(helper > 0){
    helper = helper / 10;
    amountOfDigits++;
   }

   return amountOfDigits;
}

bool isChecksumValid(int checksum){
    // If the last digit of the checksum is 0 (the checksum module 10 is 0), the creditcard is valid
    if((checksum % 10) == 0){
       return true;
    } else {
        return false;
    }
}

int getFirstDigit(long numberToCheck){
    // Return the first digit in a long number
    long firstDigit = numberToCheck;

    // If we keep dividing the number by 10, we keep removing 1 digit
    // Eventually, 1 digit will be left, that's the first digit
    while(firstDigit >= 10){
        firstDigit = firstDigit / 10;
    }

    return firstDigit;
}

int getFirstTwoDigits(long numberToCheck){
    // Return the first two digits in a long number
    // Same principle as getFirstDigit, but here we divide by 100
    long firstTwoDigits = numberToCheck;

    while(firstTwoDigits >= 100){
        firstTwoDigits = firstTwoDigits / 10;
    }

    return firstTwoDigits;
}

