#include <stdio.h>
#include <stdlib.h>

int DrawPlayground(int Width, int Height);

int main() {
    int Width = 80;
    int Height = 25;
    DrawPlayground(Width, Height);
    return 0;
}

int DrawPlayground(int Width, int Height) {
    printf("\e[H\e{\e{");
        for (int x = 0; x < Height; x++) {
            for (int y = 0; y < Width; y++) {
                if ((x == 0 && (y >= 0 && y < Width)) || (x == Height - 1 && (y >= 0 && y < Width))) {
                    printf("-");
                } else if ((y == 0 && (x > 0 && x < Height)) || (y == Width - 1 && (x > 0 && x < Height))) {
                    printf("|");
                    
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
    return 0;
}
