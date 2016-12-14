/*
    Name: Baran Barut
    Date: 8/31/2016
    Description/Purpose: This program asks the user for the amount of people knitting squares at the beginning of the week and how many new people are knitting per day. Then it calculates how many blankets can be made form the squares and the remainder of squares.
*/

// Include our library
#include <stdio.h>
#include <math.h>

// The main method!
int main(){

    //Variable declarations
    int initialPeople, blanketsMade, squaresMade, remainderSquares;
    float newPeople;

    // Ask the user for information
    printf("How many people are knitting squares at the beginning of the week?\n");
    scanf("%d", &initialPeople);

    // Checks to make sure there aren't "negative people"
    while(initialPeople <= 0){
        printf("Initial people must be positive, please enter how many initial people are knitting blanket squares each day.\n");
        scanf("%d", &initialPeople);
    }

    printf("How many new people are knitting blanket squares each day?\n");
    scanf("%f", &newPeople);

    // Checks to make sure there aren't "negative people"
    while(newPeople <= 0){
        printf("New people must be positive, please enter how many new people are knitting blanket squares each day.\n");
        scanf("%f", &newPeople);
    }

    // Calculations
    squaresMade = (initialPeople * pow((1 + newPeople), 7)); // Exp equation
    blanketsMade = (squaresMade / 60); // Amount of blankets from squares (1 per 60)
    remainderSquares = (squaresMade % 60); // Remainder of squares after blankets (modulus operator)

    // Output results
    printf("%d blanket squares will be made this week!\n", squaresMade);
    printf("You'll be able to make %d blankets and start next week with %d squares.", blanketsMade, remainderSquares);

    // Return statement
    return 0;

}
