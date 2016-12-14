/*
    Name: Baran Barut
    Course: COP3223-C
    Date: 9/20/2016
    Description: Project 4 - Asks the user for the initial fund amount, allows them to make donations and investments, and prints the final balance when done
*/

#include <stdio.h>

int main() {
    // Declare our variables and initialize them to zero for good measure
    float initBalance = 0, curBalance = 0;
    int menuChoice = 0, donateAmt = 0, investAmt = 0, numDonate = 0, numInvest = 0;
    // Ask the user for the initial balance of the fund
    printf("Welcome!\nWhat is the initial balance of the fund?\n");
    scanf("%f", &initBalance);
    // Set the current balance amount to work with for later
    curBalance = initBalance;
    // While the user has NOT selected "4", run the following
    while(menuChoice != 4){
            // Print the menu and ask for menu input
            printf("What would you like to do?\n");
            printf("1 - Make a donation\n");
            printf("2 - Make an investment\n");
            printf("3 - Print balance of fund\n");
            printf("4 - Quit\n");

            scanf("%d", &menuChoice);
            // If the user wants to donate...
            if(menuChoice == 1){
                // Ask the user how much they want to donate
                printf("How much would you like to donate?\n");
                scanf("%d", &donateAmt);
                // Make sure the donate amount is greater than zero
                while(donateAmt <= 0){
                    printf("Donation amount must be greater than $0.");
                    scanf("%d", &donateAmt);
                }
                // Add donation amount to current balance and add one to the total donations tally
                curBalance += donateAmt;
                numDonate++;
                printf("\n");
            }
            // If the user wants to invest...
            else if(menuChoice == 2){
                // Ask how much they'd like to invest
                printf("How much would you like to invest?\n");
                scanf("%d", &investAmt);
                // While the invest amount is not zero...
                while(investAmt <= 0){
                    printf("Investment amount must be greater than $0.");
                    scanf("%d", &investAmt);
                }
                // Make sure current balance minus invest amount is not less than our starting amount
                if((curBalance - investAmt) < initBalance){
                    printf("You cannot make an investment of that amount.\n");
                }
                else {
                // If everything is ok, deduct amount from current balance and add one to the investment amount tally
                    curBalance -= investAmt;
                    numInvest++;
                }
                printf("\n");
            }
            // If the user wants to print the current balance and total donations and investments
            else if(menuChoice == 3){
                // Print aforementioned items
                printf("The current balance is $%.2f.\n", curBalance);
                printf("There have been %d donations and %d investments.\n", numDonate, numInvest);
                printf("\n");
            }
            // Make sure the menu selection is not less than or equal to zero as per the input specifications
            else if(menuChoice <= 0){
                printf("Incorrect menu selection, value must be 1-4\n");
                printf("\n");
            }
    }
    // Print our final balance after quitting and final donation and investment amount
    printf("The final balance is $%.2f\n", curBalance);
    printf("There were %d donations and %d investments.\n", numDonate, numInvest);
    // Return a 0x0, a-ok!
    return 0;
}
