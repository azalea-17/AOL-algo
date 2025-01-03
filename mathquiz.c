#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

void menu();
void quiz();
int diffpage();
void leaderboard();
void sorter();
void exitc();

typedef struct Qna {
    char que[50];
    int ans;
} Qna;

// addition and subtraction
Qna baby[] =
{ 
    {"1 + 1", 2},
    {"2 + 2", 4},
    {"3 + 3", 6},
    {"4 + 4", 8},
    {"5 + 5", 10},
    {"6 + 6", 12}
};

// multiplication, division, 2-exponents
Qna ez[] =
{ 
    {" ", },
    {" ", }
};

// algebra (PEMDAS)
Qna ms[] =
{ 
    {" ", },
    {" ", }
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