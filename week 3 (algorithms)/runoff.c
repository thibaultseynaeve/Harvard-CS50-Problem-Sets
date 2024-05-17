#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check if the name appears in the array of candidates
    for (int i = 0; i < candidate_count; i++){
        // Remember, use strcmp to compare string, don't use == !!!!!!
        if(strcmp(name,candidates[i].name)==0){
            // The candidate has been found
            // Add the vote to the preferences array
            preferences[voter][rank] = i;
            return true;
        }

        // The candidate has not been found
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
// This function updates the number of votes each candidate has at this stage in the runoff
void tabulate(void)
{
    // Loop through the preferences array (use the total voter count as index)

    for (int i = 0; i < voter_count; i++){
        // Write another loop that takes the total amount of candidates as counter
        // Using r for 'rank'
        for (int r = 0; r < candidate_count; r++){
            // Check if the candidate on the first place (index o) is still in the running
            // If that is true, add 1 vote to their votes field
            int currentCandidate = preferences[i][r];
            if(candidates[currentCandidate].eliminated == false){
                // Add 1 vote to their votes field
                candidates[currentCandidate].votes += 1;
                // The vote has been assigned, so exit the loop and continue with the preferences of the next voter
                break; // Don't exit the function yet by using return, because you still need to count the votes from other voters
            }
        }
    }

    // If the candidate is already eliminated, the loop continues
    // So now we check the second preference of the voter
    // Check if eliminated, and repeat process (probably use recursion here for extra kudos)

}

// Print the winner of the election, if there is one
// If any candidate has more than half of the votes, their name sould be printed and the function should return true
// If nobody has won the election yet, the function should return false
bool print_winner(void)
{
    // Go through all the candidates
    // Check if someone has the majority (their votes are higher than the total amount of voters divided by 2)

    // Calculate the majority (the total number of votes required to win the election)
    // This is the total amount of voters divided by 2, plus 1.
    int majority = (voter_count/2)+1;
    printf("Majority votes needed: %i\n",majority);

    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].votes >= majority){
            // This candidate has the majority and has won the election
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Loop through all the candidates THAT ARE STILL IN THE RACE
    // Store the lowest amount of votes in a variable
    // We start with the total amount of votes (the max)
    int lowestvotes = voter_count;

    for (int i = 0; i < candidate_count; i++){
        // Check if candidate is still in the race
        if(candidates[i].eliminated == false){
            // Candidate is still in the race
            // Check the votes for this candidate
            // If it's lower than the value stored in the variable, replace the value
            if(candidates[i].votes < lowestvotes){
                lowestvotes = candidates[i].votes;
            }
        }
    }

    // We now hold the lowest votes in the variable
    // Return this value

    return lowestvotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    bool tie = true;

    // A tie happens when every REMAINING candidate has the same amount of votes, namely the lowest votes
    for (int i = 0; i < candidate_count; i++){
        // Check if candidate is still in the race
        if(candidates[i].eliminated == false){
            // Still in the race
            // Now check if the amount of votes for this candidate is DIFFERENT from the lowest amount of votes
            // If that's the case, there can't possibly be a tie
            if(candidates[i].votes != min){
                // Can't be a tie
                tie = false;
            }
        }
    }

    // Our boolean value 'tie' gets overwritten in our loop when there can't be a tie
    return tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loop through all candidates THAT ARE STILL IN THE RACE
    for (int i = 0; i < candidate_count; i++){
        // if candidate is still in the race
        // AND if the votes for this candidate is equal to the min
        if(candidates[i].eliminated == false && candidates[i].votes == min){
            // Eliminate this candidate
            candidates[i].eliminated = true;
        }
    }

}
