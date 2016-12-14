/*
    Name: Baran Barut
    Date: 8/31/2016
    Description/Purpose: This program asks the user for the number of balls of yarn they have and how many yards are in each ball. It then calculates how many hats and sweaters the user can make.
*/

// Include our standard library
#include <stdio.h>

// The main method wow!
int main(){

// Variables
int numBalls, numHats, numSweaters; // No need to make numHats and numSweaters floats, you can't "make" 1.77777 hats etc.
float yardsPerBall, totalYards;

// Give the user some information
printf("It takes 225 yards of yarn to make one (1) hat.\n");
printf("It takes 450 yards of yarn to make one (1) sweater.\n");

// Ask for user input and assign values to addresses of variables
printf("How many balls of yarn do you have?\n");
scanf("%d", &numBalls);
printf("How many yards of yarn are in each ball?\n");
scanf("%f", &yardsPerBall);

// Calculate how many yards in total
totalYards = (numBalls * yardsPerBall);

// Calculate the number of hats and sweaters one can make with the number of yards above
numHats = (totalYards / 225);
numSweaters = (totalYards / 450);

// Output results to the user
printf("You can make %d hats or %d sweaters.", numHats, numSweaters);

// Everything is A-OK boss! 0x0 away!
return 0;
}


