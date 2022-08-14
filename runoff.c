// runoff.c
// by: Charles Mitchell

/* In this homework assignment, we were asked to create a program that is essentially a 
ranked choice voting system that users cast their ballots for an election and returns a 
winner based on highest ranked vote */

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
}
candidate;

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
    //loops through all candidates array until a name match is found
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            //voter represents the rows and rank represents the columns in the 2D array
            preferences[voter][rank] = i;
            return true;

            //this command ends the loop right here and doesn't continue even if the loop didn't get through the entire array
            break;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //a nested double loop that loops through the preferences 2D array and checks if a candidate is eliminated in the candidates array
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                //adds to the votes for the specific candidate
                candidates[preferences[i][j]].votes = candidates[preferences[i][j]].votes + 1;

                //this command ends the loop right here and doesn't continue even if the loop didn't get through the entire array
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //loops through candidates array to check if any candidates has majority of the votes and returns true if so
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int counter = voter_count;

    //loops through candidates array and checks if the votes are lower the previous for the specific candidate and replaces the old value into the variable and then returns that value
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes < counter && candidates[j].eliminated != true)
        {
            counter = candidates[j].votes;
        }
    }

    return counter;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //loops through candidate array to check if any candidate that is not eliminated has the minimum vote. If not then it returns false
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes != min && candidates[j].eliminated != true)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //loops through the candidates array to check if a candidate has the lowest vote count and sets there eliminated status to true
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == min)
        {
            candidates[j].eliminated = true;
        }
    }
}
