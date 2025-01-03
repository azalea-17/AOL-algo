
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void menu();
void quiz(int difficulty);
int diffpage();
void leaderboard();
void sorter(int limit, int index, Qna arr[]);
void write_to_file(int score);
void read_from_file();
void exitc();

typedef struct Qna {
    char que[50];
    int ans;
} Qna;

// addition and subtraction
Qna baby[] = {
    {"1 + 1", 2},
    {"2 + 2", 4},
    {"3 + 3", 6},
    {"4 + 4", 8},
    {"5 + 5", 10},
    {"6 + 6", 12}
};

// multiplication, division, 2-exponents
Qna ez[] = {
    {"2 * 3", 6},
    {"8 / 2", 4},
    {"3 * 3", 9},
    {"16 / 4", 4},
    {"5 * 2", 10},
    {"2^2", 4}
};

// algebra (PEMDAS)
Qna ms[] = {
    {"3 + 5 * 2", 13},
    {"(8 - 3) * 2", 10},
    {"6 / 2 + 4", 7},
    {"5 * (3 + 2)", 25},
    {"12 / (2 + 2)", 3}
};

int main(void) {
    srand(time(0));
    menu();
    return 0;
}

void menu() {
    int select = 0;
    char key;
    while (1) {
        system("cls");
        puts("\033[0;36mWelcome to Kuso Kuizu!\033[0m\n==========================\n");

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

        key = getchar();

        if (key == 'w' || key == 'W') {
            if (select > 0) {
                select--;
            }
        } else if (key == 's' || key == 'S') {
            if (select < 2) {
                select++;
            }
        } else if (key == '\n') {
            if (select == 0) {
                int diff = diffpage();
                quiz(diff);
            } else if (select == 1) {
                leaderboard();
                continue;
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
        puts("Select Difficulty\n=================\n");

        switch (select) {
            default:
                printf("1. Baby Mode << 2. Easy    3. Above Elementary School   ");
                break;
            case 1:
                printf("1. Baby Mode    2. Easy << 3. Above Elementary School   ");
                break;
            case 2:
                printf("1. Baby Mode    2. Easy    3. Above Elementary School <<");
                break;
        }

        key = getchar();

        if (key == 'a' || key == 'A') {
            if (select > 0) {
                select--;
            }
        } else if (key == 'd' || key == 'D') {
            if (select < 2) {
                select++;
            }
        } else if (key == '\n') {
            if (select == 0) {
                return 1;
            } else if (select == 1) {
                return 2;
            } else if (select == 2) {
                return 3;
            }
        }
    }
}

void quiz(int difficulty) {
    system("cls");
    double answer = 0;
    int correct = 0, index = 0;

    Qna *questions;
    int size;

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

    int limit = size;
    for (int i = 0; i < size; i++) {
        system("cls");
        index = rand() % limit;
        printf("%d. %s\nAnswer: ", i + 1, questions[index].que);
        scanf("%lf", &answer);

        if ((int)answer == questions[index].ans) {
            correct++;
        }

        sorter(limit, index, questions);
        limit--;
    }

    system("cls");
    printf("%d / %d \033[0;32mCorrect\033[0m", correct, size);
    write_to_file(correct);
    getchar();
    getchar();
}

void leaderboard() {
    system("cls");
    puts("Leaderboard:\n===========\n");
    read_from_file();
    getchar();
    getchar();
}

void sorter(int limit, int index, Qna arr[]) {
    int end = limit - 1;
    Qna tmp = arr[end];
    arr[end] = arr[index];
    arr[index] = tmp;
}

void write_to_file(int score) {
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Score: %d\n", score);
    fclose(file);
}

void read_from_file() {
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[50];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void exitc() {
    system("cls");
    printf("Thanks for playing!\nExiting now...\n");
    exit(0);
}
