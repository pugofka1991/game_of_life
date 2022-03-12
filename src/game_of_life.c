#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define delayTime 1000000

char** create_matrix(int w, int h);
void initial_position(char **pole, int w, int h);
//char **cycle(int h, int w);
//void game(char **pole, int w, int h);

int main() {
    char **p = NULL;
    int Widht = 87, Hight = 25;
    p = create_matrix(Widht, Hight);
    initial_position(p, Widht, Hight);
    //game(p, poleSizeWidht, poleSizeHight);
    
    free(p);
    return 0;
}
char** create_matrix(int w, int h) {
    char** matrix = (char**) malloc(w * sizeof(char*) + w * h * sizeof(char));
    char *ptr = (char *) (matrix + w);
    for (int i = 0; i < w; i++) {
        matrix[i] = ptr + h *i;
    }
    return matrix;
}


//void game(char **pole, int w, int h) {
    /*
     for (int time = 1; time == 1;) {
         growing(pole, w, h);
         poleDraw(pole, w, h);
     }
     */
//}

void initial_position(char **pole, int w, int h) {
    unsigned char c;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (scanf("%c", &c) != EOF) {
                pole[i][j] = c;
                printf("%c", pole[i][j]);
            }
        }
    }
}
