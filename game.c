#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#define UPDATE_INTERVALL 200
#define HEIGTH 10
#define WIDTH 10

typedef struct ball {
    int x;
    int y;
    int velx;
    int vely;
} Ball;

typedef struct slider {
    int y;
    int x;
} Slider;

void printScreen(char screen[HEIGTH][WIDTH]) {
    system("cls");

    for(size_t i = 0; i < HEIGTH; i++) {
        for(size_t j = 0; j < WIDTH; j++) {
            printf(" %c ", screen[i][j]);
        }
        printf("\n");
    }
}

void fillScreen(char screen[HEIGTH][WIDTH], Ball ball, Slider sldLeft, Slider sldRight) {
    for(size_t i = 0; i < HEIGTH; i++) {
        for(size_t j = 0; j < WIDTH; j++) {
            if(i == 0 || i == HEIGTH - 1) {
                screen[i][j] = '-';
            } else if (j == 0 || j == WIDTH - 1) {
                screen[i][j] = '|';
            } else if(i == ball.y && j == ball.x){
                screen[i][j] = '@';
            } else if(j == sldLeft.x && (i == sldLeft.y || i == sldLeft.y + 1 || i == sldLeft.y - 1)) {
                screen[i][j] = 'x';
            } else if(j == sldRight.x && (i == sldRight.y || i == sldRight.y + 1 || i == sldRight.y - 1)) {
                screen[i][j] = 'x';
            } else {
                screen[i][j] = ' ';
            }
            
        }
    }
}

int main() {
    char screen[HEIGTH][WIDTH];

    char winner;

    const int middleHeigth = (int)(HEIGTH / 2);
    const int middleWidth = (int)(WIDTH / 2);

    time_t deltaGame = clock();
    time_t deltaBall = clock();

    Ball ball;  

    srand(time(NULL));

    ball.x = rand() % ((middleWidth + 2) + 1 - (middleWidth - 2)) + (middleWidth - 2);
    ball.y = rand() % ((middleHeigth + 2) + 1 - (middleHeigth - 2)) + (middleHeigth - 2);

    ball.velx = 1;
    ball.vely = 1;

    Slider sldLeft;
    Slider sldRight;

    sldLeft.y = (int)(HEIGTH / 2);
    sldRight.y = (int)(HEIGTH / 2);

    sldLeft.x = 1;
    sldRight.x = WIDTH - 2;

    while(!winner) {
        if(clock() - deltaBall > 700) {
            if(ball.y == HEIGTH - 2) {
                ball.vely = -1;
            }
            if(ball.x == WIDTH - 3) {
                if(ball.y == sldRight.y || ball.y == sldRight.y + 1 || ball.y == sldRight.y - 1) {
                    ball.velx = -1;
                } else {
                    winner = 'A';
                }  
            }
            if(ball.y == 1) {
                ball.vely = 1;
            }
            if(ball.x == 2) {
                if(ball.y == sldLeft.y || ball.y == sldLeft.y + 1 || ball.y == sldLeft.y - 1) {
                    ball.velx = 1;
                } else {
                    winner = 'B';
                }  
            }

            ball.x += ball.velx;
            ball.y += ball.vely;

            deltaBall = clock();
        }

        if(clock() - deltaGame > UPDATE_INTERVALL) {
            if(kbhit()) {
                char ch = getch();

                if(ch == 'w' && sldLeft.y != 2) {
                    sldLeft.y -= 1;  
                } else if(ch == 's' && sldLeft.y != HEIGTH - 2) {
                    sldLeft.y += 1;  
                } 
                
                if(ch == 'i' && sldRight.y != 2) {
                    sldRight.y -= 1;
                } else if(ch == 'k' && sldRight.y != HEIGTH - 2) {
                    sldRight.y += 1;
                }
            }

            fillScreen(screen, ball, sldLeft, sldRight);
            printScreen(screen);

        
            deltaGame = clock();
        }
    }

    system("cls");

    printf("Winner is %c\n", winner);

    system("pause");
}

