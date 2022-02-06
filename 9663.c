#include <stdio.h>
int p = 0;
void num_of_queen(int* arr, int N,int r) {
    if (r == N) p += 1;

    else {
        for (int j = 0; j < N; j++) {
            int flag = 1;
            for (int i = 0; i < r; i++) {
                if (arr[i] == j || arr[i] == j + r - i || arr[i] == j - r + i)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                arr[r] = j;
                num_of_queen(arr, N, r + 1);
            }
        }
    }
}

int main() {
    int N;
    int arr[15] = { 0, };
    scanf("%d", &N);

    num_of_queen(arr, N, 0);
    printf("%d", p);
}
