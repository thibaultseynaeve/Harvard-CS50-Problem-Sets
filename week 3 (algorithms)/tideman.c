#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isCycle (int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if the chose name is a valid candidate
    for(int i = 0; i < candidate_count; i++){
        // Loop through the array and check if the name is a hit
        // make sure to use strcmp to compare two strings!! This will return 0 if the strings match
        if(strcmp(name,candidates[i])==0){
            // This is a valid vote
            // Add the candidate to the ranks array
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // When a voter is done voting, this function gets called and you get the ranks[] array as the argument
    // The ranks[] array could look something like this
    // ranks[0] = 1 which means that the voter's first choice is bob
    // ranks[1] = 0 which means that the voter's second choice is alice
    // ranks [2] = 2 which means that the voter's third (and last) choice is charlie

    // Update the preferences array to add the current voter's preferences
    // preferences[i][j] should represent the number of voters who prefer candidate i over candidate j


    // Loop through the voter's preferences
    for (int i = 0; i < candidate_count; i++){
        // ranks[i] now holds the candidate index of the prefered choice for the user
        // 0 alice
        // this candidate prefers alice over 1 bob
        // this candidate prefers alice over 2 charlie

        // Go the the ranks array another time
        // But this time, use the i as starting position, because you only want to look at the items to the right of the current element
        for(int j = i; j < candidate_count; j++){

            // If i and j is the same, do nothing
            // Because that would mean: the user prefers charlie over charlie
            // Or bob over bob
            // etc

            if(i != j){
                // Add 1 vote
                preferences[ranks[i]][ranks[j]]++;
            }
        }

    }

    // Check the output for the preferences array
    for(int i = 0; i < candidate_count; i++){
        for (int j = 0; j < candidate_count; j++){
            printf("preferences[%i][%i]=%i\n",i,j,preferences[i][j]);
        }
    }

    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{



    // We need two for loops
    // We need to compare preferences[0][1] with preferences [1][0]
    // We need to compare preferences[1][2] with preferences [2][1]
    // Etc...

    for(int i = 0; i < candidate_count; i++){
        for (int j = 0; j < candidate_count; j++){
            if(preferences[i][j] == preferences[j][i]){
                // They are the same, so skip
            } else if (preferences[i][j] > preferences[j][i]){
                // i is winner
                // j is loser
                // Create a new pair
                pair newpair;
                newpair.winner = i;
                newpair.loser = j;
                // Add pair to pairs array
                pairs[pair_count] = newpair;
                // Increment pair counter
                pair_count++;
            }
        }
    }
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    // Loop through pairs array
    for (int i = 0; i < pair_count; i++){
        int highestStrength;

        // For each pair in the pairs array
        // Check how many people preferred the winner over the loser
        // The strength is just the amount of people that preferred candidate x over y
        // Use this strength to sort the array descending (biggest victory comes first)

        // For current pair, calculate the strength
        int strength = preferences[pairs[i].winner][pairs[i].loser];

        // Now compare this with all the other items (to the right) of the array
        for (int j = i+1; j < pair_count; j++){
            // Calculate strength here as wel
            int otherStrength = preferences[pairs[j].winner][pairs[j].loser];

            if(otherStrength > strength){
                // The elements have to switch places
                pair temp;
                temp.winner = pairs[j].winner;
                temp.loser = pairs[j].loser;

                pairs[j].winner = pairs[i].winner;
                pairs[j].loser = pairs[i].loser;

                pairs[i].winner = temp.winner;
                pairs[i].loser = temp.loser;
            }
        }
    }
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // Use the sorted pairs array
    // for every winner i, draw an arrow (set boolean to true) for loser j
    // For example, if i wins over j then
    // locked[i][j] = true;

    // Loop through the pairs array
    for(int i = 0; i < pair_count; i++){
        // Create a lock for every winner
        // i is the winner
        // j is the loser

        // BUT: you may not lock a pair, when this will create a cycle.

        if(!isCycle(pairs[i].winner,pairs[i].loser)){
            locked[pairs[i].winner][pairs[i].loser] = true;
        }


    }

    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{

    // The winner is the one who has no arrows pointing towards him
    // So loop through the 'locked' array
    // And find that value where the value is 'false' which means that there are now arrows pointing to this candidate

    int counter;
    bool check = false;

    for (int i = 0; i < pair_count; i++){


        for (counter = 0; counter < pair_count; counter++){
            // Loop through twodimennsional array
            // Loop will go like this:
            // locked[0][0];
            // locked[1][0];
            // locked[2][0];
            // locked[0][1];
            // locked[1][1];
            // etc...
            if(locked[counter][i]==true){
                // overwrite boolean
                check = true;
            }

        }

        if(check == false){
            // If the boolean still has value 'false' (so it hasn't been overwritten), then this person is the winner
            printf("%s\n",candidates[i]);
        }

        // Reset the check
        check = false;
    }

    // TODO
    return;
}

bool isCycle (int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if(isCycle(winner, i))
            {
                return true;
            }
        }

    }
    return false;
}
