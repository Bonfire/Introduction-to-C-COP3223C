/*

    Name: Baran Barut
    Date: 12/2/2016
    Description: Handles a series of runner and team registrations for a variety of events for a charity

    Header Specification:
        1. Individual Registration (Fully Function & Complete): This function scans the file for all runners (participants) and assigns to them the values given which include their name, their age, which event they'll be running, and the time it took to run said event. The function also makes sure to give each runner an actual "Event Name" corresponding to which event they'll be taking part in. After all that is done, the function adds one to the runnerCount pointer (current number of runners) and prints out that the runner has been registered.
        2. Team Registration (Fully Function & Complete): This function scans the file for each teams name and the number of members within each team. The team then registers the team as a whole, prints that it has been registered, stating its name and number of members, and proceeds to throw each member of the team into the Individual Registration function. By doing so, the function registers each runner individually along with the team. The function then adds one to the total number of teams.
        3. Run Events (Fully Function & Complete): This function scans the file for each runner's event time and assigns each runner their time. Then, to later calculate the max, the function throws the two last runners-of-each-event-type's event times into the shortest time variable for each event. The function then compares each and every runner's event times to the lowest event time of each event to see who has the lowest event time. If the runner ran a marathon, the function scans the file for each and every age group, categorizes them, then checks to see if each runner (based on their age) has qualified for their marathon based on their event time. If the runner has qualified, it prints so. Afterwards, the function prints who got the lowest time in each event and what time they had.
        4. Total Donations (Not Attempted): Ran into an issue with determining who got what money and seeing whether they were part of what team, did not attempt. This function still needs to calculate which team raised the most money and how much money, who raised the most money from each team and how much money, which individual raised the most money and how much, and the total number of donations raised by the charity.

*/

#include <stdio.h>
#include <string.h>

#define TEAMS 200
#define RUNNERS 10000
#define LENGTH 20
#define TEAMSIZE 50
#define NUMAGEGROUPS 10

struct person { // Our person structure to categorize all runners
    char name[LENGTH];
    int number;
    int age;
    int event;
    float money;
    float time;
};

struct team { // Our team structure to categorize all teams
    char name[LENGTH];
    int nummembers;
    float money;
    struct person members[TEAMSIZE];
};

struct agegroups { // Our agegroups structure to categorize all age groups (custom defined)
    int startAge;
    int endAge;
    int qualTime;
};

// FUNCTION PROTOTYPES

void indvReg(struct person * participant, FILE * ifp, float regCost, int * runnerCount);
void teamReg(struct person * participant, struct team * teams, FILE * ifp, float regCost, int * runnerCount, int * teamCount);
void runEvents(struct person * participant, struct team * teams, FILE * ifp, int * runnerCount, struct agegroups * group);

int main() {
    struct person * participant[RUNNERS]; // Declare our participants of type structure person with a limit of RUNNERS
    struct team * teams[TEAMSIZE]; // Declare our teams of type structure team with a limit of TEAMSIZE
    struct agegroups * group[NUMAGEGROUPS]; // Declare our group of type structure with a limit of NUMAGEGROUPS
    float earlyCost, lateCost, teamCost; // Declare some usable floats
    int numReg, numLateReg, i, runnerCount = 0, teamCount = 0; // Declare some usable ints

    char filename[30], regType[4]; // Declare some usable string (character arrays)

    printf("Please input the filename for the race: "); // Prompt the user for the file name to work with
    scanf("%s", &filename); // Scan it in
    FILE * ifp; // Declare a file pointer ifp
    ifp = fopen(filename, "r"); // Open our file

    fscanf(ifp, "%f %f %f", &earlyCost, &lateCost, &teamCost); // Scan the file for the early registration, late registration, and team registration costs
    fscanf(ifp, "%d", &numReg); // Scan the file for how many individuals/teams have registered early

    for(i = 0; i < numReg; i++){ // For each THING registered (INDV or TEAM)
        fscanf(ifp, "%s", &regType); // Scan to see what they registered as
        if(strcmp(regType, "INDV") == 0){ // If they registered as an individual..
            indvReg(participant, ifp, earlyCost, &runnerCount); // Call the indvReg function and pass our participant struct, file pointer, early cost, and address of runnerCount (total number of runners)

        }
        else if(strcmp(regType, "TEAM") == 0){ // If they registered as a team...
            teamReg(participant, teams, ifp, teamCost, &runnerCount, &teamCount); // Call the teamReg function and pass our participant struct, teams struct, file pointer, team cost, address of runnerCount (total number of runners), and address of teamCount (total number of teams)
        }
    }

    printf("\n"); // Newline for tidiness

    fscanf(ifp, "%d", &numLateReg); // Scan to see how many people registered late

    for(i = 0; i < numLateReg; i++){ // For every person (individual) that registered late...
        indvReg(participant, ifp, lateCost, &runnerCount); // Call the indvReg function and pass our participant struct, file pointer, early cost, and address of runnerCount (total number of runners)
    }

    runEvents(participant, teams, ifp, &runnerCount, group); // Call our runEvents function to run our events and pass our participant struct, file pointer, early cost, address of runnerCount (total number of runners), and group struct

    fclose(ifp); // Close our file just to be safe
    return 0; // Return a 0x0 a-ok
}

/*
    Function: indvReg
    Pre-Condition: Should take in participant of type person structure, ifp of type FILE, regCost (cost of registration) of type float, and runnerCount (total number of registered runners) of type int pointer
    Post-Condition: Should return nothing but print when an individual is registered and should add one to the number of registered runners
*/

void indvReg(struct person * participant, FILE * ifp, float regCost, int * runnerCount){ // Individual Registration Function

    char eventName[9]; // Declare a character array (string) to hold our event names
    int counter = *runnerCount; // Declare and Initialize a counter equal to pointer runnerCount (total number of runners) to work with

    if(counter <= RUNNERS){ // While our counter is less than the max number of runners (RUNNERS)

        fscanf(ifp, "%s", &participant[counter].name); // Scan for the runners name and assign it to them
        fscanf(ifp, "%d", &participant[counter].age); // Scan for the runners age and assign it to them
        fscanf(ifp, "%d", &participant[counter].event); // Scan for the runners event type and assign it to them
        fscanf(ifp, "%f", &participant[counter].money); // Scan for the runners donations raised and assign it to them

        if(participant[counter].event == 5){ // If the runner ran the 5k (event type of 5)
            strcpy(eventName, "5k"); // Call and assign their event type "5k"
        }else if(participant[counter].event == 10){ // If the runner the 10k (event type of 10)
            strcpy(eventName, "10k"); // Call and assign their event type "10k"
        }else if(participant[counter].event == 42){ // If the runner ran the marathon (event type of 42)
            strcpy(eventName, "marathon"); // Call and assign their event type "marathon"
        }

        *runnerCount += 1; // Add one to our runner count pointer after we've registered them

        printf("%s registered for the %s race! They have been assigned the number %d.\n", participant[counter].name, eventName, *runnerCount); // Print out who was registered, for what race, and what number they were assigned

    }
    else{ // If the number of registered runners is greater than 10,000
        printf("We can only have at most 10,000 runners, sorry!\n"); // Give them a nice little error
    }

}

/*
    Function: teamReg
    Pre-Condition: Should take in participant of type person structure, teams of type team structure, ifp of type FILE, regCost (cost of registration) of type float, runnerCount (total number of registered runners) of type int pointer, and teamCount (total number of registered teams) of type int pointer
    Post-Condition: Should return nothing but print when a team is registered, should register each runner in each team, and should add one to the number of registered teams
*/

void teamReg(struct person * participant, struct team * teams, FILE * ifp, float regCost, int * runnerCount, int * teamCount){ // Team Registration Function

    char teamName[LENGTH]; // Declare a character array (string) to hold our teamName with max length of LENGTH
    int numMembers, i; // Declare two integers to use

    if(*teamCount <= TEAMS){ // If the number of teams registered is less than our max (TEAMS)
        fscanf(ifp, "%s", &teamName); // Scan for our team name
        fscanf(ifp, "%d", &numMembers); // Scan for our number of members for the team

        for(i = 0; i < *teamCount; i++){ // For i is less than the number of teams
            strcpy(teams[i].name, teamName); // Assign each team their team name
            teams[i].nummembers = numMembers; // Assign each team their number of members
        }

        printf("\n"); // Newline for tidiness
        printf("%s team registered for the event. They have %d members:", teamName, numMembers); // Print that we've registered the team
        printf("\n"); // Newline for tidiness

        for(i = 0; i < numMembers; i++){ // For i < the number of members in the team
            indvReg(participant, ifp, regCost, runnerCount); // Call indvReg to register each teammate
        }

        *teamCount += 1; // Add one to our team count pointer
        printf("\n"); // Newline for tidiness

    }
    else{ // Else, if the number of teams is greater than 200
        printf("We can only have at most 200 teams registered, sorry!\n"); // Give them a nice little error
    }
}

/*
    Function: teamReg
    Pre-Condition: Should take in participant of type person structure, teams of type team structure, ifp of type FILE, regCost (cost of registration) of type float, runnerCount (total number of registered runners) of type int pointer, and group of type structure agegroup containing all age groups and qualifying times
    Post-Condition: Should return nothing but assign each runner their event time, start with a random "lowest event time" for each event, grab every age group and its qualifying time, see who got the lowest time in each event, print out who qualified for their marathons, and print who got the lowest event times in each event
*/

void runEvents(struct person * participant, struct team * teams, FILE * ifp, int * runnerCount, struct agegroups * group){ // Run Events Function

    int i, j, runnerNum, eventTime; // Declare some integers
    float short5k, short10k; // Declare some floats
    char winner5k[20], winner10k[20]; // Declare two strings

    // Assign the time everyone got for their event
    for(i = 0; i < *runnerCount; i++){ // For i is less than the number of total runners
        fscanf(ifp, "%d %d", &runnerNum, &eventTime); // Scan for each runner's number and their event time
        participant[i].time = eventTime; // Assign event times by runner's number
    }

    //Make sure that we have a number to start off our lowest time comparison
    for(i = 0; i < *runnerCount; i++){ // For i is less than the number of runners
        if(participant[i].event == 5){ // If the person ran a 5k
            short5k = participant[i].time; // Assign the shortest 5k time to them
        }
        else if(participant[i].event == 10){ // If the person ran a 10k
            short10k = participant[i].time; // Assign the shortests 10k time to them
        }
    }

    // Get every age group and their qualifying times
    for(i = 0; i < NUMAGEGROUPS; i++){ // For i is less than the number of age groups (NUMAGEGROUPS defined by the instructions as 10)
        fscanf(ifp,"%d %d %d", &group[i].startAge, &group[i].endAge, &group[i].qualTime); // Scan for the age group's starting age, ending age, and qualifying time
    }

    printf("\n"); // Newline for tidiness

    //See who got the lowest time in every event
    for(i = 0; i < *runnerCount; i++){ // For i is less than the number of runners
        if(participant[i].event == 5){ // If the person ran a 5k
            if(participant[i].time < short5k){ // If the person's 5k time is shorter than the shortest 5k time
                short5k = participant[i].time; // Make their time the new shortest 5k time
                strcpy(winner5k, participant[i].name); // Assign their name to the winner
            }
        }
        else if(participant[i].event == 10){ // If the person ran a 10k
            if(participant[i].time < short10k){ // If the person's 10k time is shorter than the shortest 10k time
                short10k = participant[i].time; // Make their time the new shortest 10k time
                strcpy(winner10k, participant[i].name); // Assign their name to the winner
            }
        }
        else if(participant[i].event == 42){ // If the person ran a marathon
            for(j = 0; j < NUMAGEGROUPS; j++){ // For j is less than the number of age groups (10)
                if((participant[i].age >= group[j].startAge) && (participant[i].age <= group[j].endAge)){ // Find which age group the person is
                    if(participant[i].time <= group[j].qualTime){ // If they qualified...
                        printf("%s qualified in the marathon run with a time of %.1f minutes!\n", participant[i].name, participant[i].time); // Say that they qualified
                    }
                }
            }
        }
    }

    printf("5k race: %s had the fastest time with %.1f minutes!\n", winner5k, short5k); // Print who got the shortest 5k time and what that time was
    printf("10k race: %s had the fastest time with %.1f minutes!\n", winner10k, short10k); // Print who got the shortest 10k time and what that time was

}

