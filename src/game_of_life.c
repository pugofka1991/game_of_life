// gcc -Wall -Werror -Wextra game_of_life.c
//
/*
    Правила:
    
    Если у клетки:
     0 или 1 сосед она живёт.
     4-8 соседей она умирает.
     2,3 соседа она растёт.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define delayTime 1000000

void cycle(int h, int w);
void poleDraw(void *size, int w, int h);
void growing(void *size, int w, int h);
void delay(int number_of_seconds);


int main(int resolution, char ** v) {
    // принимает данные о размере поля сразу с запуском => ./a.out 30 30 => размер поля будет 30 на 30
    int poleSizeWidht = 0, poleSizeHight = 0;
    if (resolution > 1) poleSizeWidht = atoi(v[1]);
    if (resolution > 1) poleSizeWidht = atoi(v[1]);

    if (0 >= poleSizeWidht) poleSizeWidht = 30;
    if (0 >= poleSizeHight) poleSizeHight = 30;

    cycle(poleSizeHight, poleSizeWidht);

    return 0;
}
/*
//  Этот мейн классический - принимает данные через сканф
int main() {
    int poleSizeWidht = 30, poleSizeHight = 30;
    if (scanf("Введите размеры поля для игры:%d %d", &poleSizeWidht, &poleSizeHight) != 2) {
        printf("Данные введены некоректно, введите ширину и высоту поля корректно.");
    }

    if (0 >= poleSizeWidht) poleSizeWidht = 30;
    if (0 >= poleSizeHight) poleSizeHight = 30;

    cycle(poleSizeWidht, poleSizeHight);

    return 0;
}
*/
void cycle(int h, int w) {
    unsigned pole[h][w];
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
        int a = rand() % 2 + 1;
        if (a == 1) pole[y][x] = ' ';
            else
            pole[y][x] = '*';
        }
    }
    int time = 1;
    while (time == 1) {
        // system("cls");
        // system("clear");
        poleDraw(pole, w, h);
        growing(pole, w, h);
        // delay(delayTime);
        usleep(200000);
    }
}

void poleDraw(void *size, int w, int h) {
    
    int (*pole)[w] = size;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (pole[y][x] == '*'){
                printf("%c", '*');
            } else {
                printf("%c", ' ');
            }
        }
    }
    
}
void growing(void *size, int w, int h) {
    unsigned (*pole)[w] = size;
    unsigned new[h][w];

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int n = 0;
            for (int y1 = y - 1; y1 <= y + 1; y1++)
                for (int x1 = x - 1; x1 <= x + 1; x1++)
                    if (pole[(y1 + h) % h][(x1 + w) % w])
                        n++;

            if (pole[y][x]) n--;
            new[y][x] = (n == 3 || (n == 2 && pole[y][x]));
            }
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            pole[y][x] = new[y][x];
        }
    }
}

void delay(int number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds) {
    }
}
