#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

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
int check_dup(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }
    
    if (argc == 2)
    {
        printf("%s\n", argv[1]);
        return 0;
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
    
    int dup = check_dup();
    if (dup != 0)
    {
        printf("No two candidates will have the same name");
        return 4;
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

// Check dup the name of candidates
int check_dup(void)
{
    int dup = 0;
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = (i + 1); j < candidate_count; j++)
        {
            if (strcasecmp(candidates[i], candidates[j]) == 0)
            {
                dup ++;
            }

        }
    }
    return dup;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
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
    // TODO
    int c, d;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }
            else
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (i == ranks[k])
                    {
                        c = k;
                    }
                    if (j == ranks[k])
                    {
                        d = k;
                    }
                }
                if (c < d)
                {
                    preferences[i][j] ++;
                }
                
            }
        }
        
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
            
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int c, d;
    int strength[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }
    //begin sort
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (strength[i] < strength[j])
            {   
                //sort the winner
                c = pairs[i].winner;
                pairs[i].winner = pairs[j].winner;
                pairs[j].winner = c;
            
                //sort the loser
                d = pairs[i].loser;
                pairs[i].loser = pairs[j].loser;
                pairs[j].loser = d;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
bool make_cycle(int start, int end)
{
    if (start == end)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (make_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!make_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool c = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                c = true;
                break;
            }
        }
        if (!c)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

