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
}
pair;

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
bool check_cycle(int to, int from);
int is_pointed_to(int candidate);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] - preferences[j][i] > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swap_counter = -1;
    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int left_diff = preferences[pairs[i].winner][pairs[i].loser];
            int right_diff = preferences[pairs[i + 1].winner][pairs[i + 1].loser];

            if (right_diff > left_diff)
            {
                pair temp = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = temp;
                swap_counter++;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // for each pair's winner
    // is anyone pointing to the winner
        // noone is pointing to the winner
            // lock in
        // someone is pointing to the winner
            // is that someone the person the pair's loser
                // if yes
                    // cycle: don't lock in
                // if no
                    // does that someone have anyone pointing to them
                        // if no
                            // lock in
                        // if yes
                            // is that someone the person the pair's loser
                                // if yes
                                    // cycle: don't lock in
                                // if no
                                    // does that someone have anyone pointing to them
                                        // etc...

    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!check_cycle(loser, winner))
        {
            locked[winner][loser] = true;
        }
    }

    return;
}

bool check_cycle(int to, int from)  // (loser, winner)
{
    int pointing = is_pointed_to(from);
    if (pointing == candidate_count)
    {
        return false;
    }

    while (pointing != candidate_count)
    {
        pointing = is_pointed_to(pointing);
        if (pointing == to)
        {
            return true;
        }
    }

    return false;
}

int is_pointed_to(int candidate)    // return index of person who is pointing to candidate or candidate_count if no one is pointing to
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][candidate])
        {
            return i;
        }
    }

    return candidate_count;
}

// Print the winner of the election
void print_winner(void)
{
    bool lost[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                lost[j] = true;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (!lost[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

