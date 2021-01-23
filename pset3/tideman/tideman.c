#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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
int candidate_number(string name);
int win_margin(pair p);
bool is_source(int v);
void append_descendants(int v, bool list[]);
bool is_acyclic(void);

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
            ranks[rank] = candidate_number(candidates[i]);
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
    int pair_number = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_number].winner = i;
                pairs[pair_number].loser = j;
                pair_number++;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_number].winner = j;
                pairs[pair_number].loser = i;
                pair_number++;
            }
        }
    }
    pair_count = pair_number;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swaps;
    do
    {
        swaps = 0;
        pair temp;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (win_margin(pairs[i]) < win_margin(pairs[i + 1]))
            {
                temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                swaps++;
            }
        }
    }
    while (swaps != 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (!is_acyclic())
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int v = 0; v < candidate_count; v++)
    {
        if (is_source(v))
        {
            printf("%s\n", candidates[v]);
        }
    }
}

int candidate_number(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int win_margin(pair p)
{
    int a = p.winner;
    int b = p.loser;
    return preferences[a][b];
}

bool is_source(int v)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][v])
        {
            return false;
        }
    }
    return true;
}

void append_descendants(int v, bool list[])
{
    for (int w = 0; w < candidate_count; w++)
    {
        if (locked[v][w] && !list[w])
        {
            list[w] = true;
            append_descendants(w, list);
        }
    }
}

bool contained_in_cycle(int v)
{
    bool list[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        list[i] = false;
    }
    append_descendants(v, list);
    return list[v];
}

bool is_acyclic(void)
{
    for (int v = 0; v < candidate_count; v++)
    {
        if (contained_in_cycle(v))
        {
            return false;
        }
    }
    return true;
}