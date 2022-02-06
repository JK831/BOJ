#include <stdio.h>
#include <stdbool.h>
#define MAX 9
int map[MAX][MAX];
bool row[MAX+1][MAX+1];
bool col[MAX+1][MAX+1];
bool square[MAX+1][MAX+1];

void input() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j] != 0)
            {
                row[i][map[i][j]] = true;
                col[j][map[i][j]] = true;
                square[(i / 3) * 3 + (j / 3)][map[i][j]] = true;
            }
        }
    }
}

void print_map() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
   }
}

void tracking_puzzle(int sell) {
    int x = sell / MAX;
    int y = sell % MAX;
    if (sell == 81) {
        print_map();
        exit(0);
    }
    if (map[x][y] == 0) {
        for (int i = 1; i <= 9; i++) {
            if (row[x][i] == false && col[y][i] == false && square[(x / 3) * 3 + (y / 3)][i] == false)
            {
                row[x][i] == true;
                col[y][i] == true;
                square[(x / 3) * 3 + (y / 3)][i] = true;
                map[x][y] = i;
                tracking_puzzle(sell + 1);
                map[x][y] == 0;
                row[x][i] == false;
                col[y][i] == false;
                square[(x / 3) * 3 + (y / 3)][i] = false;

            }
        }
    }
    else tracking_puzzle(sell + 1);
}

int main() {
    input();
    tracking_puzzle(0);
}
