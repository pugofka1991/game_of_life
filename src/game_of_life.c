#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define WIDHT 81
#define HIGHT 25

char** create_matrix();
void initial_position(char **pole);
void new_pole(char **pole, char **buff);
void game(char **pole, char **buff);
int sosed_count(char **pole, int x, int y);
void stop_game(char **pole, char **buff, int *flag);

int main() {
    int  delayTime = 100000;
    char **pole_game = NULL;
    char** buff = NULL;
    char speed;
    int flag = 1;
    pole_game = create_matrix();
    buff = create_matrix();
    initial_position(pole_game);
    int e = 100;
    while (e > 0) {
        if (flag == 1) {
            game(pole_game, buff);
            new_pole(pole_game, buff);
            usleep(delayTime);
        } else {
            break;
        }
        e--;
    }
    free(pole_game);
    free(buff);
    return 0;
}

char** create_matrix() {
    char** matrix = malloc(HIGHT * sizeof(char*) + WIDHT * HIGHT * sizeof(char));
    char *ptr = (char *) (matrix + HIGHT);
    for (int i = 0; i < HIGHT; i++) {
        matrix[i] = ptr + WIDHT *i;
    }
    return matrix;
}

void new_pole(char **pole, char **buff) {
    printf("\e[H\e{\e{");
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            pole[i][j] = buff[i][j];
            printf("%c", pole[i][j]);
        }
    }
}

void stop_game(char **pole, char **buff, int *flag) {
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            if (pole[i][j] == '_') {
                *flag = 0;
            }
           // if (pole[i][j] != buff[i][j]) {
            //*flag = 1;
           // }
        }
    }
}

void game(char **pole, char **buff) {
    int sosed = 0;
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            sosed = sosed_count(pole, i, j);
            if (pole[i][j] == '_' && sosed == 3) {
                buff[i][j] = '*';
            }else if (pole[i][j] == '*' && (sosed < 2 || sosed > 3)) {
                buff[i][j] = '_';
            } else {
                buff[i][j] = pole[i][j];
            }
        }
    }
}
    
int sosed_count(char **pole, int x, int y) {
    int col, row;
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            row = (i + x + HIGHT) % HIGHT;
            col = (j + y + WIDHT - 1) % (WIDHT - 1);
            if (pole[row][col] == '*') {
                count++;
            }
        }
    }
    return pole[x][y] == '*' ? --count : count;
}

void initial_position(char **pole) {
    unsigned char c;
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            if (scanf("%c", &c) != EOF) {
                pole[i][j] = c;
            }
        }
    }
}
