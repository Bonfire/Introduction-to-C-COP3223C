/*
    Name: Baran Barut
    Course: COP3223-C
    Date: 10/14/2016
    Description: Reads a list of auctions and determines the highest bid for each auction and the amount raised for charity in total.
*/

#include <stdio.h>

int main() {

    int numAuct = 0, i = 0, numBids = 0, j = 0, bidAmt = 0, maxBid = 0;
    char fileName[30];
    float totalAmt = 0.0;

    printf("Please enter the name of the auction file: ");
    scanf("%s", &fileName);

    FILE *ifp;
    ifp = fopen(fileName, "r");

    fscanf(ifp, "%d", &numAuct);

    for(i = 0; i < numAuct; i++){
        fscanf(ifp, "%d", &numBids);

        for(j = 0; j < numBids; j++){
            fscanf(ifp, "%d", &bidAmt);

            if(bidAmt > maxBid){
                maxBid = bidAmt;
            }
        }

        totalAmt += maxBid;
        printf("Auction #%d was sold for $%.2f\n", i + 1, (float)maxBid);
        maxBid = 0;
    }

    printf("The silent auction raised $%.2f for charity!", totalAmt);

    fclose(ifp);
    return 0;
}
