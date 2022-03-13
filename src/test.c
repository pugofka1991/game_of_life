#include <stdio.h>
#include <stdlib.h>


int main() {
    for (int i = 1;i > 0; i++) {
    int a = rand() % 100 + 1;
        if (a % 2 == 0) printf("1");
            else 
                printf("0");
    }
    return 0;
}