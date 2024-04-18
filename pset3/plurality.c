#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct {
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++) {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name)) {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void) {
    int winners_num = 1;
    int winners[candidate_count];
    winners[0] = 0;

    // finds the candidate with the most votes
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > candidates[winners[0]].votes) {
            winners[0] = i;
        }
    }

    // if there is a tie, then all the tied scores will be added after winners[0]
    for (int i = winners[0] + 1; i < candidate_count; i++) {
        if (candidates[i].votes == candidates[winners[0]].votes) {
            winners[winners_num] = i;
            winners_num++;
        }
    }

    // printing winners
    for (int i = 0; i < winners_num; i++) {
        printf("%s\n", candidates[winners[i]].name);
    }

    return;
}