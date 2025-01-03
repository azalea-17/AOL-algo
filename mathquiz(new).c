#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#define MAX_USERS 100
#define FILE_NAME "scores.txt"

typedef struct Qna {
    char que[50];
    int ans;
} Qna;

typedef struct UserScore {
    char name[50];
    int score;
} UserScore;

void menu();
void quiz(int difficulty);
int diffpage();
void leaderboard();
void sorter(int limit, int index, Qna arr[]);
void exitc();

Qna baby[] = { 
    {"1 + 1", 2},
    {"2 + 2", 4},
    {"3 + 3", 6},
    {"4 + 4", 8},
    {"5 + 5", 10},
    {"6 + 6", 12},
    {"7 + 7", 14},
    {"8 + 8", 16},
    {"9 + 9", 18},
    {"10 + 10", 20},
    {"11 + 11", 22},
    {"12 + 12", 24}
};

Qna ez[] = { 
    {"2 * 2", 4},
    {"2 * 4", 8},
    {"3 * 3", 9},
    {"3 * 4", 12},
    {"4 * 4", 16},
    {"5 * 6", 30},
    {"5 * 7", 35},
    {"6 * 7", 42},
    {"12 / 6", 2},
    {"20 / 4", 5},
    {"36 / 6", 6},
    {"24 / 3", 8},
    {"25 / 5", 5},
    {"49 / 7", 7},
    {"4^2", 16},
    {"2^4", 16},
    {"5^2", 25},
    {"2^5", 32},
    {"3^3", 27},
    {"6^2", 36}
};

Qna ms[] = { 
    {"9 - (3 + 2) * 2", 1},
    {"(10 - 2) / 2 + 3", 7},
    {"(10 - 2) / 2 + 5", 9},
    {"3 + 5 * 2", 13},
    {"12 / 4 + 5 * 2", 14},
    {"10 - 2^2 + 6", 14},
    {"(6 + 2) * (3 - 1)", 16},
    {"(8 - 3) * 4", 20},
    {"4 * (3 + 5) - 6", 26},
    {"(3 + 5) * 2^2 - 4", 28},
    {"(5 + 3) * 2^2", 32},   
    {"2^3 + 4 * 3", 20},
    {"(5 + 5) * (2 + 3)", 50}
};

int main(void) {
    srand((unsigned int)time(0));
    menu();
    return 0;
}

void menu() {
    int select = 0;
    char key;
    while (1) {
        system("cls");
        printf("\033[0;36mWelcome to Kuso Kuizu!\033[0m\n==========================\n\n");

        switch (select) {
            default:
                printf("1. Quiz Time   <<\n2. Leaderboard\n3. Exit\n");
                break;
            case 1:
                printf("1. Quiz Time\n2. Leaderboard <<\n3. Exit\n");
                break;
            case 2:
                printf("1. Quiz Time\n2. Leaderboard\n3. Exit        <<\n");
                break;
        }

        key = _getch();

        if (key == 'w' || key == 'W') {
            if (select > 0) select--;
        } else if (key == 's' || key == 'S') {
            if (select < 2) select++;
        } else if (key == '\r') {
            if (select == 0) {
                int diff = diffpage();
                quiz(diff);
            } else if (select == 1) {
                leaderboard();
            } else if (select == 2) {
                exitc();
                return;
            }
        }
    }
}

int diffpage() {
    int select = 0;
    char key;
    while (1) {
        system("cls");
        printf("Select Difficulty\n=================\n\n");

        switch (select) {
            default:
                printf("1. Baby Mode << 2. Easy    3. Above Elementary School   \n");
                break;
            case 1:
                printf("1. Baby Mode    2. Easy << 3. Above Elementary School   \n");
                break;
            case 2:
                printf("1. Baby Mode    2. Easy    3. Above Elementary School <<\n");
                break;
        }

        key = _getch();

        if (key == 'a' || key == 'A') {
            if (select > 0) select--;
        } else if (key == 'd' || key == 'D') {
            if (select < 2) select++;
        } else if (key == '\r') {
            return select + 1;
        }
    }
}

void quiz(int difficulty) {
    system("cls");
    char name[50];
    double answer = 0;
    int correct = 0, index = 0;
    Qna *questions;
    int size;

    // Input name for their user in leaderboard
    printf("Enter your name: ");
    scanf("%s", name);

    if (difficulty == 1) {
        questions = baby;
        size = sizeof(baby) / sizeof(baby[0]);
    } else if (difficulty == 2) {
        questions = ez;
        size = sizeof(ez) / sizeof(ez[0]);
    } else {
        questions = ms;
        size = sizeof(ms) / sizeof(ms[0]);
    }

    for (int i = 0; i < size / 2; i++) {
        system("cls");
        index = rand() % size;
        printf("%d. %s\nAnswer: ", i + 1, questions[index].que);
        scanf("%lf", &answer);

        if (answer == questions[index].ans) correct++;

        sorter(size, index, questions);
        size--;
    }

    system("cls");
    printf("%d / %d \033[0;32mCorrect\033[0m\n", correct, size / 2);

    // Save the score to the file
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error: Could not open scores file.\n");
        getchar();
        return;
    }

    fprintf(file, "%s,%d\n", name, correct);
    fclose(file);

    printf("Your score has been saved!\n");
    getchar();
    getchar();
}

//file
void leaderboard() {
    system("cls");
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No scores available.\n");
        getchar();
        return;
    }

    UserScore scores[MAX_USERS];
    int count = 0;

    while (fscanf(file, "%[^,],%d\n", scores[count].name, &scores[count].score) != EOF) {
        count++;
    }
    fclose(file);

    printf("Leaderboard:\n\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }

    getchar();
}

//sorting
void sorter(int limit, int index, Qna arr[]) {
    Qna tmp = arr[limit - 1];
    arr[limit - 1] = arr[index];
    arr[index] = tmp;
}

void exitc() {
    system("cls");
    printf("\033[0;35m|=========================|\033[0m\n");
    printf("\033[0;35m|==      ========      ===|\033[0m\n");
    printf("\033[0;35m|====   ===========   ====|\033[0m\n");
    printf("\033[0;35m|===========  ============|\033[0m\n");
    printf("\033[0;35m|==========    ===========|\033[0m\n");
    printf("\033[0;35m|=========================|\033[0m\n");
    printf("\033[0;35m|=====  ===========  =====|\033[0m\n");
    printf("\033[0;35m|======   ======   =======|\033[0m\n");
    printf("\033[0;35m|=========      ==========|\033[0m\n");
    printf("\033[0;35m|=========================|\033[0m\n");
    printf("\033[0;35m|=========================|\033[0m\n\n");
    printf("\033[0;35mThank You For Playing!\033[0m\n");
}
