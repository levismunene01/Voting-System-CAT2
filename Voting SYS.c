#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CANDIDATES 10
#define MAX_VOTERS 200

// Structure for Candidate
typedef struct {
    int id;
    char name[50];
    char position[30];
    int votes;
} Candidate;

// Structure for Voter
typedef struct {
    char studentId[30];
    int hasVoted;
} Voter;

// Initial pre-configured candidates for UoEm Student Council
Candidate candidates[MAX_CANDIDATES] = {
    {1, "John Kamau", "President", 0},
    {2, "Amina Mohamed", "President", 0},
    {3, "Brian Ochieng", "Secretary General", 0},
    {4, "Faith Wanjiku", "Secretary General", 0}
};
int candidateCount = 4;

Voter voters[MAX_VOTERS];
int voterCount = 0;

// Function to verify or register a voter
int verifyVoter(char *id) {
    int i;
    for (i = 0; i < voterCount; i++) {
        if (strcmp(voters[i].studentId, id) == 0) {
            return i; // Voter found
        }
    }
    // Register new voter if space permits
    if (voterCount < MAX_VOTERS) {
        strcpy(voters[voterCount].studentId, id);
        voters[voterCount].hasVoted = 0;
        voterCount++;
        return voterCount - 1;
    }
    return -1; // Voter database full
}

// Function to display candidates
void displayCandidates() {
    printf("\n===========================================================\n");
    printf("            UNIVERSITY OF EMBU - CANDIDATE LIST            \n");
    printf("===========================================================\n");
    printf("%-5s | %-22s | %-20s | %-5s\n", "ID", "Candidate Name", "Position", "Votes");
    printf("-----------------------------------------------------------\n");

    int i;
    for (i = 0; i < candidateCount; i++) {
        printf("%-5d | %-22s | %-20s | %-5d\n",
            candidates[i].id,
            candidates[i].name,
            candidates[i].position,
            candidates[i].votes);
    }
    printf("-----------------------------------------------------------\n");
}

// Function to register a new candidate
void registerCandidate() {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("\n[ERROR] Candidate limit reached (%d max). Cannot register more candidates.\n", MAX_CANDIDATES);
        return;
    }

    Candidate newCand;
    // Auto-assign ID based on current count or max ID + 1
    newCand.id = candidates[candidateCount - 1].id + 1;

    printf("\n===========================================================\n");
    printf("            REGISTER NEW CANDIDATE                         \n");
    printf("===========================================================\n");
    printf("Assigned Candidate ID: %d\n", newCand.id);

    // Clear input buffer before reading strings
    while (getchar() != '\n' && !feof(stdin));

    printf("Enter Candidate Full Name: ");
    fgets(newCand.name, sizeof(newCand.name), stdin);
    newCand.name[strcspn(newCand.name, "\n")] = 0; // Remove trailing newline

    printf("Enter Position (e.g., Treasurer, President): ");
    fgets(newCand.position, sizeof(newCand.position), stdin);
    newCand.position[strcspn(newCand.position, "\n")] = 0; // Remove trailing newline

    newCand.votes = 0;

    candidates[candidateCount] = newCand;
    candidateCount++;

    printf("\n[SUCCESS] Candidate %s successfully registered for %s!\n", newCand.name, newCand.position);
}

// Function to cast a vote
void castVote() {
    char studentId[30];
    printf("\nEnter your UoEm Student ID (e.g., D33/1234/2024): ");
    scanf("%29s", studentId);

    int voterIndex = verifyVoter(studentId);
    if (voterIndex == -1) {
        printf("[ERROR] Voter database is full or invalid ID format!\n");
        return;
    }

    if (voters[voterIndex].hasVoted) {
        printf("[WARNING] Student (%s) has already cast a vote! Multiple voting is prohibited.\n", studentId);
        return;
    }

    displayCandidates();
    int choice;
    printf("\nEnter the Candidate ID you wish to vote for: ");
    scanf("%d", &choice);

    int found = 0;
    int i;
    for (i = 0; i < candidateCount; i++) {
        if (candidates[i].id == choice) {
            candidates[i].votes++;
            voters[voterIndex].hasVoted = 1;
            printf("[SUCCESS] Vote successfully recorded for %s (%s).\n", candidates[i].name, candidates[i].position);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[ERROR] Invalid Candidate ID selected. Vote not cast.\n");
    }
}

// Function to view results
void displayResults() {
    printf("\n===========================================================\n");
    printf("         UNIVERSITY OF EMBU - LIVE E-VOTING RESULTS        \n");
    printf("===========================================================\n");
    displayCandidates();
}

// Function to export voting results to a CSV file
void exportResults() {
    FILE *file = fopen("voting_results.csv", "w");
    if (file == NULL) {
        printf("\n[ERROR] Could not open file for exporting results.\n");
        return;
    }

    // Write CSV header
    fprintf(file, "Candidate ID,Candidate Name,Position,Total Votes\n");

    // Write candidate records
    int i;
    for (i = 0; i < candidateCount; i++) {
        fprintf(file, "%d,%s,%s,%d\n",
            candidates[i].id,
            candidates[i].name,
            candidates[i].position,
            candidates[i].votes);
    }

    fclose(file);
    printf("\n[SUCCESS] Results successfully exported to 'voting_results.csv'!\n");
}

// Main Menu Loop
int main() {
    int choice;
    while (1) {
        printf("\n===========================================================\n");
        printf("           UoEm STUDENT UNION E-VOTING PORTAL              \n");
        printf("===========================================================\n");
        printf("1. View Candidates\n");
        printf("2. Cast Vote\n");
        printf("3. Register New Candidate (Admin)\n");
        printf("4. View Live Results (Admin)\n");
        printf("5. Export Results to CSV (Admin)\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                displayCandidates();
                break;
            case 2:
                castVote();
                break;
            case 3:
                registerCandidate();
                break;
            case 4:
                displayResults();
                break;
            case 5:
                exportResults();
                break;
            case 6:
                printf("\nExiting UoEm E-Voting Portal. Thank you!\n");
                exit(0);
            default:
                printf("[ERROR] Invalid choice. Please choose between 1 and 6.\n");
        }
    }
    return 0;
}
