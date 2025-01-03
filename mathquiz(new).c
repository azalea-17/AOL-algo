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
} Qna;UserScore;

void menu();
void quiz(int difficulty);
int diffpage();
void leaderboard(UserScore scores[], int count);
void sorter(int limit, int index, Qna arr[]);
void exitc();

// addition and subtraction
Qna baby[] =
{ 
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

// multiplication, division, 2-exponents
Qna ez[] =
{ 
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

// algebra (PEMDAS)
Qna ms[] =
{ 
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

int main (void)
{
    srand(time(0));
    menu();
    return 0;
}

void menu()
{
    int select = 0;
    char key;
    while(1) {
        system("cls");
        puts("\033[0;36mWelcome to Kuso Kuizu!\033[0m\n==========================\n");

        switch(select) {
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
            if (select > 0) {
                select--;
            }
        } else if (key == 's' || key == 'S') {
            if (select < 2) {
                select++;
            }
        } else if (key == '\r') {
            if(select == 0) {
                int diff = diffpage();
                quiz(diff);
            } else if(select == 1) {
                leaderboard();
                continue;
            } else if(select == 2) {
                exitc();
                return;
            }
        }
    }
}

int diffpage()
{
    int select = 0;
    char key;
    while(1) {
        system("cls");
        puts("Select Difficulty\n=================\n");

        switch(select) {
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

        key = _getch();

        if (key == 'a' || key == 'A') {
            if (select > 0) {
                select--;
            }
        } else if (key == 'd' || key == 'D') {
            if (select < 2) {
                select++;
            }
        } else if (key == '\r') {
            if(select == 0) {
                return 1;
            } else if(select == 1) {
                return 2;
            } else if(select == 2) {
                return 3;
            }
        }
    }
}

void quiz(int difficulty)
{
    system("cls");
    double answer = 0;
    int correct = 0, index = 0;

    if(difficulty == 1) {
        const int size = (sizeof(baby) / sizeof(baby[0])) / 2;
        int limit = size;
        for (int i = 0; i < size; i++) {
            system("cls");
            index = rand() % limit;
            printf("%d. %s\nAnswer: ", i + 1, baby[index].que);
            scanf("%lf", &answer);

            if (answer == baby[index].ans) {
                correct++;
            }

            sorter(limit, index, baby);
            limit--;
        }
        system("cls");
        printf("%d / %d \033[0;32mCorrect\033[0m", correct, size);

    } else if (difficulty == 2) {
        const int size = (sizeof(ez) / sizeof(ez[0])) / 2;
        int limit = size;
        for (int i = 0; i < size; i++) {
            system("cls");
            index = rand() % limit;
            printf("%d. %s\nAnswer: ", i + 1, ez[index].que);
            scanf("%lf", &answer);

            if (answer == ez[index].ans) {
                correct++;
            }

            sorter(limit, index, ez);
            limit--;
        }
        system("cls");
        printf("%d / %d \033[0;32mCorrect\033[0m", correct, size);

    } else if (difficulty == 3) {
        const int size = (sizeof(ms) / sizeof(ms[0])) / 2;
        int limit = limit;
        for (int i = 0; i < size; i++) {
            system("cls");
            index = rand() % size;
            printf("%d. %s\nAnswer: ", i + 1, ms[index].que);
            scanf("%lf", &answer);

            if (answer == ms[index].ans) {
                correct++;
            }

            sorter(limit, index, ms);
            limit--;
        }
        system("cls");
        printf("%d / %d \033[0;32mCorrect\033[0m", correct, size);
    }

    getchar();
    getchar();
    return;
}

void leaderboard()
{
    system("cls");
    // to do
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
}

void sorter(int limit, int index, Qna arr[])
{
    int end = limit - 1;
    Qna tmp = arr[end];
    arr[end] = arr[index];
    arr[index] = tmp;
}

void exitc()
{
    system("cls");
    // exit screen design
}