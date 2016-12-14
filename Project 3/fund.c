/*
    Name: Baran Barut
    Course: COP3223C
    Date: 9/7/2016
    Description/Purpose: Asks the user for the current amount of funds, calculate yearly interest, then doles out scholarships according to requirements set by the assignment instructions.
*/

// Include our standard input and output library
#include <stdio.h>

// The main (and only) method
int main() {

    // Declare some variables and make sure they're initialized at 0
    int currentFund = 0, yearlyRate = 0;
    int num1000 = 0, num500 = 0, num250 = 0;
    float yearTotal;

    // Ask the user how much money is currently in the fund
    printf("How much money is in the fund?\n");
    scanf("%d", &currentFund);

    // Ask the user what the interest rate is as an integer
    printf("What is the yearly percent rate? (As an integer)\n");
    scanf("%d", &yearlyRate);

    // Check to make sure the fund isn't less than zero
    while(currentFund < 0){
        printf("The current fund must be greater than or equal to zero\n");
        scanf("%d", &currentFund);
    }

    // Check to make sure the interest rate isn't less than or equal to zero
    while(yearlyRate <= 0){
        printf("The yearly rate must be greater than zero\n");
        scanf("%d", &yearlyRate);
    }

    // Calculate the amount of money earned from interest
    yearTotal = (currentFund * yearlyRate * .01);

    // Find out how many times 250 goes into the amount earned
    num250 = yearTotal / 250;

    // If we can make 4 250 scholarships into a 1000 scholarsip, do so
    while((num250 >= 4) && (num1000 < 5)){
        num1000++;
        num250-=4;
    }
    // If we can make 2 250 scholarships into a 500 scholarship, do so
    while((num250 >= 2) && (num500 < 10)){
        num500++;
        num250-=2;
    }

    // Print how many of each scholarship will be awarded
    printf("%d $1000 scholarships will be awarded\n", num1000);
    printf("%d $500 scholarships will be awarded\n", num500);
    printf("%d $250 scholarships will be awarded\n", num250);

    // Return a 0x0, everything's ok!
    return 0;

}
