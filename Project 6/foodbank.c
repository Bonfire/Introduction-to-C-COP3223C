/*
 * Name: Baran Barut
 * NID: ba211127
 * Course: COP3223C - Fall 2016
 * Description: Provides a "foodbank" program that accepts requests, donations, and fulfills orders as requested
 */

#include <stdio.h>

#define NUMTYPES 5 // Number of food types
#define CATEGORIES 2 // Number of categories (Requests & Donations)

int main() { // Main method

    int status[2][5], i = 0, j = 0, choice = 0, donationType = 0, donationAmt = 0, requestType = 0, requestAmt = 0, temp = 0, excessAmt = 0; // Declare our integer variables
    char TYPES[5][20] = {"Protein", "Dairy", "Grains", "Vegetables", "Fruits"}; // Declare our TYPES array of type string

    for(i = 0; i < CATEGORIES; i++){ // Make all values of our "status" array equal to 0 to start
        for(j = 0; j < NUMTYPES; j++){
            status[i][j] = 0;
        }
    }

    printf("Welcome to the Food Bank Management Program!\n"); // Welcome the user

    while(choice != 5){ // While the user has not chosen to quit...
        printf("What would you like to do?\n"); // Prompt the user with a menu
        printf("1. Enter a Donation\n");
        printf("2. Enter a Request\n");
        printf("3. Fulfill Requests\n");
        printf("4. Print status reports\n");
        printf("5. Exit\n");
        scanf("%d", &choice); // Ask for the user's input/choice


        switch(choice){ // Switch depending on the users choice

            case 1: // Case 1 - Donations
                printf("What donation type would you like to enter?\n"); // Ask which type of food they'd like to donate

                for(i = 0; i < NUMTYPES; i++){ // Print our food types
                    printf("%d. %s\n", i, TYPES[i]);
                }

                scanf("%d", &donationType); // Scan for the user's selected type

                if((donationType >= 0) && (donationType <= 4)){ // Make sure their choice is a valid choice
                    printf("How many would you like to enter? "); // Ask how many of that type they'd like to donate
                    scanf("%d", &donationAmt); // Scan for the users donation amount
                    if(donationAmt >= 0){ // Make sure the donation amount is greater than 0
                        printf("Donation Added.\n");
                        status[CATEGORIES - 2][donationType] += donationAmt; // Donate the selected amount to the selected type
                    }
                    else{
                        printf("Sorry, that was not a valid input.\n"); // If all else fails, let the user know
                        break; // Break if error
                    }
                }

                break; // Break out of our case

            case 2: // Case 2 - Requests

                printf("What would you like to request?\n"); // Prompt the user for what they'd like to request

                for(i = 0; i < NUMTYPES; i++){ // Print out food types for requests
                    printf("%d. %s\n", i, TYPES[i]);
                }

                scanf("%d", &requestType); // Scan for their food type

                if((requestType >= 0) && (requestType <= 4)){ // Validate their food type
                    printf("How many would you like to request?\n"); // Ask how many of aforementioned food type
                    scanf("%d", &requestAmt); // Scan for their amount

                    if(requestAmt > 0){ // Make sure they request above zero
                        status[CATEGORIES - 1][requestType] += requestAmt; // Add their requested amount of requested type to the request table
                        printf("Request Added.\n"); // Inform the user their request was added
                    }
                    else {
                        printf("Sorry, that is not a valid input.\n"); // Otherwise notify the user something went wrong
                    }
                }
                else{
                    printf("Sorry, that is not a valid input.\n"); // If their requested type does not exist, let them know
                }

                break; // Break out of our case

            case 3: // Case 3 - Fulfill

                for(j = 0; j < NUMTYPES; j++){ // Iterate 5 times, one for each food type
                    if((status[CATEGORIES - 1][j] > 0) && (status[CATEGORIES - 2][j] == 0)){ // If the amount of requests is greater than zero and there are no donations of that type we cannot do anything
                        printf("%s requests cannot be fulfilled\n", TYPES[j]); // Let the user know
                    }
                    if((status[CATEGORIES - 2][j] > 0) && (status[CATEGORIES - 1][j] > 0)){ // If we have donations and requests to work with, do so
                        if(status[CATEGORIES - 2][j] < status[CATEGORIES - 1][j]) { //  If Donations < Requests
                            printf("%s requests will be partially fulfilled\n", TYPES[j]); // Let the user know we can partially fill
                            status[CATEGORIES - 1][j] -= status[CATEGORIES - 2][j]; // Subtract the donated amount from requests (to fill orders)
                            status[CATEGORIES - 2][j] = 0; // Clear out our donation amount
                        }
                        if(status[CATEGORIES - 1][j] <= status[CATEGORIES - 2][j]){ // If Requests < Donations
                            printf("%s requests will be fulfilled\n", TYPES[j]); // Let the user know we can fully fulfill
                            status[CATEGORIES - 2][j] -= status[CATEGORIES - 1][j]; // Subtract the requested amount from the donations (to fill orders)
                            status[CATEGORIES - 1][j] = 0; // Clear out our request amount
                        }
                    }
                }

                // status[CATEGORIES - 1][j] = Requests
                // status[CATEGORIES - 2][j] = Donations

                break; // Break out of our case

            case 4: // Case 4 - Print Tables

                for(j = 0; j < NUMTYPES; j++){ // Iterate 5 times (as per our number of food types)
                    printf("%s   Donations: %d   Requests: %d\n", TYPES[j], status[CATEGORIES - 2][j], status[CATEGORIES - 1][j]); // Print our food types and the requests and donations of each type
                }

                break; // Break out of our case

            case 5: // Case 5 - Exit Case

                printf("Thank you for running our system!"); // Thank the user for running the system
                return 0; // End program 0x0 (No break needed as we are exiting)

            default: // Case Default - Fallback

                printf("Sorry, that was not a valid input.\n"); // Notify the user that their choice was not valid
        }
    }

    return 0; // End program 0x0
}
