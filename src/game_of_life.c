// gcc -Wall -Werror -Wextra game_of_life.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define WIDHT 81
#define HIGHT 25
#define for_x for (int x = 0; x < 25; ++x)
#define for_y for (int y = 0; y < 81; ++y)
#define for_xy for_x for_y



char** create_matrix();
void initial_position(char **pole);
void new_pole(char **pole, char **buff);
void game(char **pole, char **buff, char** buff_2, char** buff_3);
int sosed_count(char **pole, int x, int y);
void stop_game(int *flag, char **pole, char **buff_3);

int main(int argc, char* argv[]) {
    if (argc == 2){
        int speed = 3;
        if (*argv[1] > 48 && *argv[1] < 54) speed = *argv[1] - 48;
        

        char **pole_game = NULL;
        pole_game = create_matrix();
        initial_position(pole_game);

        // if (scanf("Введите скорость работы 1-5: %d", &speed) == 1) {

        char** buff = NULL;
        char** buff_2 = NULL;
        char** buff_3 = NULL;
        buff = create_matrix();
        buff_2 = create_matrix();
        buff_3 = create_matrix();

        int  delayTime = 50000 * speed;
        int flag = 0;
        for (int round = 0; flag == 0; ++round) {
            if (round > 2) stop_game(&flag, pole_game, buff_3);
            game(pole_game, buff, buff_2, buff_3);
            new_pole(pole_game, buff);
            usleep(delayTime);
        }
        printf("\n%d\n", *argv[1] - 48);
        printf("%d\n",speed);
        free(pole_game);
        free(buff);
        free(buff_2);
    } else {
        printf("ASDawsdasd");
    }
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

void stop_game(int *flag, char **pole, char **buff_3) {
    /* for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            if (pole[i][j] == '_') {
                *flag = 1;
            }
            }
    }
    */
    int num = 0;
    for_xy if (pole[x][y] != buff_3[x][y]) ++num;
    if (0 == num) *flag = 1;
}

void game(char **pole, char **buff, char** buff_2, char** buff_3) {
    for_xy buff_3[x][y] = buff_2[x][y];
    for_xy buff_2[x][y] = pole[x][y];

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
