/*
 * Name: Baran Barut
 * Course: COP 3223C-16FALL
 * Assignment: Project 7
 * Date: 11/11/2016
 * Description: A mock "Gala Controller" for a gala event, handles all aspects of the auction, raffle, and tickets
 */

#include <stdio.h>
#include <string.h>

//Constants to be used.
//MAXSIZE is the maximum size of all strings
//MAXAUCTIONITEMS is the maximum number of items in the auction
//MAXRAFFLE is the maximum number of available raffle tickets
#define MAXSIZE 100
#define MAXAUCTIONITEMS 1000
#define MAXRAFFLE 1000

//Function prototypes - do not change these
void initRaffle(int raffles[MAXRAFFLE]);
void initAuction(float auction[2][MAXAUCTIONITEMS]);
void buyTickets(float * totalRevenue, int * ticketsSold, int numTickets, float price);
void buyRaffle(float * totalRevenue, int raffles[MAXRAFFLE], int availTickets, int numTickets, int person);
void bid(float auction[2][MAXAUCTIONITEMS], float bid, int auctionNumber, int person, int flag);
float awardAuction(float auction[2][MAXAUCTIONITEMS], int auctionNumber);
void awardRaffle(int raffles[MAXRAFFLE], int raffleNumber, int winner);

//Main function
int main() {
    FILE * ifp;
    char filename[MAXSIZE], event[MAXSIZE], item[MAXSIZE];
    float presale, dayOf, totalRevenue = 0;
    float auctions[2][MAXAUCTIONITEMS];
    int raffles[MAXRAFFLE];
    int numPresale, numAuctions, numRaffle, numPrizes, numEvents;
    int i, ticketsSold = 0, auctionFlag = 1;

    printf("Please enter the input file name.\n");
    scanf("%s", filename);

    ifp = fopen(filename, "r");

    fscanf(ifp, "%f%f%d", &presale, &dayOf, &numPresale);

    totalRevenue += numPresale * presale;
    ticketsSold = numPresale;

    fscanf(ifp, "%d", &numAuctions);
    fscanf(ifp, "%d%d", &numRaffle, &numPrizes);
    fscanf(ifp, "%d", &numEvents);

    initRaffle(raffles);
    initAuction(auctions);

    for (i=0; i<numEvents; i++) {
        fscanf(ifp, "%s", event);

        if (strcmp(event, "BUY") == 0) {
            fscanf(ifp, "%s", item);
            if (strcmp(item, "TICKET") == 0) {
                int numTickets;
                fscanf(ifp, "%d", &numTickets);
                buyTickets(&totalRevenue, &ticketsSold, numTickets, dayOf);
            }
            else if (strcmp(item, "RAFFLE") == 0){
                int numTickets, person;
                fscanf(ifp, "%d%d", &numTickets, &person);
                buyRaffle(&totalRevenue, raffles, numRaffle, numTickets, person);
            }
        }
        else if (strcmp(event, "BIDITEM") == 0) {
            int itemNumber, person;
            float amount;
            fscanf(ifp, "%d%d%f", &itemNumber, &person, &amount);
            bid(auctions, amount, itemNumber, person, auctionFlag);
        }
        else if (strcmp(event, "CLOSEAUCTION") == 0) {
            printf("CLOSE AUCTION.\n");
            auctionFlag = 0;
        }
        else if (strcmp(event, "AWARD") == 0) {
            fscanf(ifp, "%s", item);
            if (strcmp(item, "AUCTION") == 0) {
                int auctionNumber;
                fscanf(ifp, "%d", &auctionNumber);
                totalRevenue += awardAuction(auctions, auctionNumber);
            }
            else if (strcmp(item, "RAFFLE") == 0){
                int raffleNumber, winner;
                fscanf(ifp, "%d%d", &raffleNumber, &winner);
                awardRaffle(raffles, raffleNumber, winner);
            }
        }
        else {
            printf("TOTALREVENUE is $%.2lf.\n", totalRevenue);
        }
    }

    fclose(ifp);
    return 0;
}

// Pre-conditions: raffles is the collection of all possible raffle tickets
// Post-condition: Each raffle ticket should have a default owner number
//                      that indicates it has not been sold yet
//
// What to do in this function: Each index number represents a different
// ticket number for the Raffle.  The value in the array at that index is
// the ticket's owner (an index that represents a person at the Fundraising
// Gala).  Initialize all the values in the array to a integer that indicates
// the ticket has not been sold yet.
void initRaffle(int raffles[MAXRAFFLE]) {
    int i; // Declare i
    for(i = 0; i < MAXRAFFLE; i++){ // For i to MAXRAFFLE, incrementing i
        raffles[i] = -1; // Make every value -1 to start (this will be our flag)
    }
}

// Pre-conditions: auction is the collection of all possible auction items
// Post-condition: Each auction should have a default price of 0 and a default
//                 bidder number that indicates it has not been bid on yet
//
// What to do in this function: Each index number represents a different
// auction item for the Raffle.  Select one row of the two-dimensional
// array to be for bids; the other row will be for people (the current highest
// bidder).  Initialize all bids to zero and initialize all people to a number
// that indicates the item has not been bid on yet
void initAuction(float auction[2][MAXAUCTIONITEMS]) {
    int i; // Declare i
    for(i = 0; i < MAXAUCTIONITEMS; i++){ // Iterate from i to MAXAUCTIONITEMS, incrementing i
        auction[0][i] = -1; // Set all values of the first row and i column to -1 to work with
        auction[1][i] = -1; // Set all values of the second row and i column to -1 to work with
    }
}

// Pre-conditions: totalRevenue is a pointer to the total amount that the Gala has earned
//                 ticketsSold is a pointer to the current number of tickets sold
//                 numTickets is the number of tickets that the person would like to purchase
//                 price is the current cost of the tickets (the DayOf price)
// Post-condition: Sells numTickets to the current person at price and updates the number
//                      of tickets sold and the current total revenue
//
// What to do in this function: Calculate the cost of the tickets and add it to the total
// revenue.  Print out the ticket numbers that were sold to the screen.  Update the number
// of tickets that have been sold.
void buyTickets(float * totalRevenue, int * ticketsSold, int numTickets, float price) {
    int i; // Declare i
    int ticketsBefore = * ticketsSold; // Keep track of how many tickets sold we started with
    for(i = 0; i < numTickets; i++){ // For i is less than number of tickets requested, incrementing i
        * totalRevenue += price; // Add the price of ticket i to our total revenue pointer
        if(i > 0) { // As long as more than one ticket has been sold (this is so we don't miscalculate)
            * ticketsSold += 1.00; // Add one to the number of tickets sold pointer
        }
    }
    printf("SOLD TICKETS %d - %d\n", ticketsBefore, * ticketsSold); // Print which tickets we sold
    * ticketsSold += 1.00; // Make sure we sell at least one ticket (so we don't miscalculate)
}

// Pre-conditions: totalRevenue is a pointer to the total amount that the Gala has earned
//                 raffles is an array of all possible raffle tickets
//                 availTickets is the number of raffle tickets available to be sold
//                 numTickets is the number of raffle tickets that the person would like to purchase
//                 person is the numerical identifier of the person attempting to buy tickets
// Post-condition: Sells numTickets to the current person if tickets are available, or sells as
//                      as many as are left, or sells none if no tickets are left.  Updates totalRevenue
//                      if any tickets are sold.  Each ticket sells for $2
//
// What to do in this function: The value stored in each index of raffles should be the number of the
// person that bought that ticket.  For example if person 35 holds raffle tickets 11-15, then elements 11-15
// of raffles should all be equal to 35.
//
// Traverse to the next available ticket in the raffles array, if it exists.  If it does not exist, print
// out that no tickets will be given to this person.  If it does exist, check to see if there are enough
// tickets left for the person to get the full number they are looking for.  If there are not enough for
// the full amount, give them all the tickets that are left.  Print out which tickets they are given.
// Update totalRevenue with the number of tickets sold at $2 each.
void buyRaffle(float * totalRevenue, int raffles[MAXRAFFLE], int availTickets, int numTickets, int person) {
    int i; // Declare i
    int ticketCounter = 0; // Declare our ticket counter
    int startTickets = 0; // Declare our starting variable

    for(i = 0; i < availTickets; i++){ // For i is less than our available tickets
        if(raffles[i] == -1){ // If the ticket isnt taken (-1)
            startTickets = i; // That is our new ticket amount
            break; // THIS BREAK IS 100% REQUIRED OR YOU WILL GET WRONG VALUES
        }else{
            startTickets = 100; // If not, our starting tickets is 100 as none have been taken
        }
    }

    for(i = startTickets; i < availTickets; i++){ // For i is less than available tickets
        if(i < (numTickets + startTickets)){ // If i is less than our total tickets
            ticketCounter += 1; // Add one to our ticket counter
            raffles[i] = person; // Assign that ticket to that person
            * totalRevenue += 2; // Add $2 to our total revenue
        }
    }
    if(startTickets >= availTickets){ // If we have more tickets to start than available...
        printf("NO RAFFLE TICKETS given to PERSON %d\n", person); // Give no tickets
    }else{ // ELSE...
        printf("RAFFLE TICKETS %d - %d given to PERSON %d\n", startTickets, (ticketCounter+startTickets-1), person); // Give that person their tickets
    }
}

// Pre-conditions: auction is an 2D array that holds the current highest bid and the person with the highest bid
//                 bid is a new proposed bid
//                 auctionNumber is the numerical identifier for the item being bid on
//                 person is the numerical identifier of the person attempting to bid
//                 flag is a value that indicates whether or not bids are still being accepted
// Post-condition: Updates the auctions with a new high bid if present
//                      Will not accept new bids that are not higher than old bids
//                      Will not accept new bids if the auctions are closed
//
// What to do in this function: Check to see if the auctions are still open based on flag
//
// If bids are still being accepted, check to see if bid is higher than the current bid for
// the auction.  If it is higher, update the auction with the new bid and the new person number
// Print out the result of either accepted or rejected
void bid(float auction[2][MAXAUCTIONITEMS], float bid, int auctionNumber, int person, int flag) {
    if(flag == 1){ // If the auction is still open (Flag 1 as per line 75)
        if(bid > auction[0][auctionNumber]){ // If the bid is greater than the current highest bid...
            auction[0][auctionNumber] = bid; // Then our bid is the new highest bid
            auction[1][auctionNumber] = person; // Assign that bid to that person
            printf("BIDITEM %d ACCEPTED FOR PERSON %d at %.2f DOLLARS\n", auctionNumber, person, bid); // Print that the bid has been accepted
        }
        else { // ELSE...
            printf("BIDITEM %d REJECTED FOR PERSON %d at %.2f DOLLARS\n", auctionNumber, person, bid); // Their bid has been rejected due to it not being higher than the highest
        }
    }
    else{ // ELSE...
        printf("BIDITEM %d REJECTED FOR PERSON %d at %.2f DOLLARS\n", auctionNumber, person, bid); // Their bid has been rejected due to the auction being closed
    }
}

// Pre-conditions: auction is an 2D array that holds the current highest bid and the person with
//                 the highest bid
//                 auctionNumber is the numerical identifier for the item being awarded
// Post-condition: Returns the value of the highest bid for the auction specified by auction number
//
// What to do in this function: Check to see if the auction identified by auctionNumber has any
// bids.  If so, award the auction to the person with the highest bid.  If not, print out that
// there have been no bids for this item.  Return the appropriate value to be added to totalRevenue
float awardAuction(float auction[2][MAXAUCTIONITEMS], int auctionNumber) {
    if(auction[1][auctionNumber] != -1){ // If the auction has someone that has bid on it (is not an automatically assigned -1)
        printf("AUCTION ITEM %d WON BY PERSON %.0f FOR $%.2f\n", auctionNumber, auction[1][auctionNumber], auction[0][auctionNumber]); // Print that the auction has been won
        return auction[0][auctionNumber]; // Return the total of the highest bid to add to total revenue
    }
    else{ // ELSE...
        printf("NO BIDS FOR AUCTION ITEM %d\n", auctionNumber); // Print that the auction hasn't been bid on
        return 0.00; // Return $0.00 to add to our total revenue
    }
}

// Pre-conditions: raffles is an array of all possible raffle tickets
//                 winner is the winning ticket number
//                 raffleNumber is the current raffle being held
//
// Post-condition: prints out the numerical identifier of the person who
//                 holds the winning ticket number
void awardRaffle(int raffles[MAXRAFFLE], int raffleNumber, int winner) {
    if(raffles[winner] != -1){ // If the ticket has been claimed (is not a -1 flag)
        printf("RAFFLE %d WON BY PERSON %d\n", raffleNumber, raffles[winner]); // Print which raffle was won by which person
    }
    else{ // ELSE...
        printf("NO WINNER FOR RAFFLE %d\n", raffleNumber); // There was no raffle winner, print such
    }
}
