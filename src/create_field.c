#include <stdio.h>

int main() {
    int n;
    int found_point = 0;
    scanf("%d", &n);
    int points[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            for (int k = 0; k < n; k++) {
                if (i == points[k][0] && j == points[k][1]) {
                    printf("*");
                    found_point = 1;
                    break;
                }
            }
            if (!found_point) {
                printf("_");
            } else {
                found_point = 0;
            }
        }
        printf("\n");
    }
    return 0;
}
