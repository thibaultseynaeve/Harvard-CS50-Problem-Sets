#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Create a new candidate for every name in the command line
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Ask the user how many people will vote
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop through the array of candidates
    for (int i = 0; i < candidate_count; i++){
        // Remember, we use strcmp to compare strings!
        if(strcmp(name,candidates[i].name) == 0){
            // The name is found
            // Add a vote for this candidate
            candidates[i].votes++;
            // End function
            return true;
        }
    }

    // There isn't a candidate with that name
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // create variable where we will store the highest number of votes we can find in the candidates array
    int highestnumber = 0;

    // Loop through all the candidates
    for (int i = 0; i < candidate_count; i++){
        // Check if it's the highest number we've encountered
        if(candidates[i].votes > highestnumber){
            // Change the value of the highestnumber variable
            highestnumber = candidates[i].votes;
        }
    }

    // Now we know what the highest number of votes is
    // Multiple people could have this amount of votes.
    // So loop through the candidates again, and check if the value of the highestnumber variable is the same as the amount of votes for the current candidate
    for (int i = 0; i < candidate_count; i++){
        if(candidates[i].votes == highestnumber){
            // This candidate is (one of) the winner(s)
            printf("%s\n",candidates[i].name);
        }
    }

}
