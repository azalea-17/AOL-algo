#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_USERS 100
#define FILE_NAME "scores.txt"

// Structure to hold user scores
typedef struct {
    char name[50];
    int score;
} UserScore;

// Function declarations
void displayMenu();
void takeQuiz();
void viewScores();
void generateReport();
void sortScores(UserScore scores[], int count);

int main() {
    int choice;
    while (1) {
        system("cls");
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from input buffer

        switch (choice) {
            case 1:
                takeQuiz();
                break;
            case 2:
                viewScores();
                break;
            case 3:
                generateReport();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n===== Math Quiz Menu =====\n");
    printf("1. Take Quiz\n");
    printf("2. View Scores\n");
    printf("3. Generate Report\n");
    printf("4. Exit\n");
}

void takeQuiz() {
    system("cls");
    char name[50];
    int score = 0;
    int num1, num2, answer, userAnswer;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character

    srand(time(NULL));
    printf("\n===== Math Quiz =====\n");

    // Generate 5 random math questions
    for (int i = 0; i < 5; i++) {
        system("cls");
        num1 = rand() % 20 + 1; // Random number between 1 and 20
        num2 = rand() % 20 + 1;
        answer = num1 + num2;

        printf("Question %d: %d + %d = ", i + 1, num1, num2);
        scanf("%d", &userAnswer);

        if (userAnswer == answer) {
            printf("Correct!\n");
            score += 10; // 10 points for each correct answer
        } else {
            printf("Wrong! The correct answer is %d.\n", answer);
        }
    }

    // Save score to file
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error: Unable to save score.\n");
        return;
    }
    fprintf(file, "%s,%d\n", name, score);
    fclose(file);

    printf("\nQuiz Complete! Your score: %d\n", score);
}

void viewScores() {
    system("cls");
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No scores available.\n");
        return;
    }

    UserScore scores[MAX_USERS];
    int count = 0;

    // Read scores from file
    while (fscanf(file, "%[^,],%d\n", scores[count].name, &scores[count].score) != EOF) {
        count++;
    }
    fclose(file);

    // Sort scores in descending order
    sortScores(scores, count);

    printf("\n===== High Scores =====\n");
    for (int i = 0; i < count; i++) {
        system("cls");
        printf("%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }
}

void generateReport() {
    system("cls");
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No scores available for report.\n");
        return;
    }

    UserScore scores[MAX_USERS];
    int count = 0, totalScore = 0;

    // Read scores from file
    while (fscanf(file, "%[^,],%d\n", scores[count].name, &scores[count].score) != EOF) {
        totalScore += scores[count].score;
        count++;
    }
    fclose(file);

    // Sort scores in descending order
    sortScores(scores, count);

    // Write report to a file
    FILE *reportFile = fopen("report.txt", "w");
    if (reportFile == NULL) {
        system("cls");
        printf("Error: Unable to generate report.\n");
        return;
    }

    fprintf(reportFile, "===== Math Quiz Report =====\n");
    fprintf(reportFile, "Total Participants: %d\n", count);
    fprintf(reportFile, "Average Score: %.2f\n", (float)totalScore / count);
    fprintf(reportFile, "\nHigh Scores:\n");

    for (int i = 0; i < count; i++) {
        fprintf(reportFile, "%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }

    fclose(reportFile);
    printf("\nReport generated successfully! Check 'report.txt'.\n");
}

void sortScores(UserScore scores[], int count) {
    UserScore temp;
    for (int i = 0; i < count - 1; i++) {
        system("cls");
        for (int j = 0; j < count - i - 1; j++) {
            
            if (scores[j].score < scores[j + 1].score) {
                temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}