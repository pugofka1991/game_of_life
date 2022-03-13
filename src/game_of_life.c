#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDHT 81
#define HIGHT 25
#define for_x for (int x = 0; x < 25; ++x)
#define for_y for (int y = 0; y < 81; ++y)
#define for_xy for_x for_y



char kbhit();
char** create_matrix();
void button(int* speed);
void initial_position(char **pole);
void new_pole(char **pole, char **buff);
int sosed_count(char **pole, int x, int y);
void stop_game(int *flag, char **pole, char **buff_3);
void free_fun(char** pole_game, char** buff, char** buff_2);
void game(char **pole, char **buff, char** buff_2, char** buff_3);

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int speed = 3;
        if (*argv[1] > 48 && *argv[1] < 54) speed = *argv[1] - 48;

        char **pole_game = NULL;
        pole_game = create_matrix();
        initial_position(pole_game);

        freopen("/dev/tty", "r", stdin);
        system("stty cbreak");

        char** buff = NULL;
        char** buff_2 = NULL;
        char** buff_3 = NULL;
        buff = create_matrix();
        buff_2 = create_matrix();
        buff_3 = create_matrix();

        int flag = 0;
        for (int round = 0; flag == 0; ++round) {
            button(&speed);
            int  delayTime = 500000 / speed;

            if (round > 2) stop_game(&flag, pole_game, buff_3);
            game(pole_game, buff, buff_2, buff_3);
            new_pole(pole_game, buff);
            usleep(delayTime);
        }

        free_fun(pole_game, buff, buff_2);

    } else {
        printf("Данные введены неверно - попробуйте снова!");
        printf("\nФормат данных \"./a.out скорость игры 1 - 5 < 1.txt - паттерн. \"");
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
    for_xy {
            pole[x][y] = buff[x][y];
            printf("%c", pole[x][y]);
        }
    printf("\n\n");
}

void stop_game(int *flag, char **pole, char **buff_3) {
    int num = 0;
    for_xy if (pole[x][y] != buff_3[x][y]) ++num;
    if (0 == num) *flag = 1;
}

void game(char **pole, char **buff, char** buff_2, char** buff_3) {
    for_xy buff_3[x][y] = buff_2[x][y];
    for_xy buff_2[x][y] = pole[x][y];

    int sosed = 0;
    for_xy {
            sosed = sosed_count(pole, x, y);
            if (pole[x][y] == '_' && sosed == 3) {
                buff[x][y] = '*';
            } else if (pole[x][y] == '*' && (sosed < 2 || sosed > 3)) {
                buff[x][y] = '_';
            } else {
                buff[x][y] = pole[x][y];
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
    for_xy if (scanf("%c", &c) != EOF) pole[x][y] = c;
}

char kbhit() {
    int old = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, old | O_NONBLOCK);
    char c = getchar();
    fcntl(0, F_SETFL, old);

    return c;
}

void free_fun(char** pole_game, char** buff, char** buff_2) {
    free(pole_game);
    free(buff);
    free(buff_2);
}

void button(int* speed) {
    char new_speed = kbhit();
            if (new_speed == '+') *speed++;
            if (new_speed == '-') {
                if (*speed > 1) *speed--;
            }
}
