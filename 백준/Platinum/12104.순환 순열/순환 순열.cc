#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 5;
char S[MAX], T[MAX];
int N, fail[MAX];
 
int main(){
    scanf("%s %s", S, T);
    N = strlen(S);
    for(int i = 0; i < N; i++){
        S[N + i] = S[i];
    }
    N <<= 1;
    for(int i = 1, j = 0; i < N / 2; i++){
        while(j > 0 && T[i] != T[j])    j = fail[j - 1];
        if(T[i] == T[j])    fail[i] = ++j;
    }
    int ans = 0;
    for(int i = 0, j = 0; i < N - 1; i++){
        while(j > 0 && S[i] != T[j])    j = fail[j - 1];
        if(S[i] == T[j]){
            if(j == N / 2 - 1){
                ans++;
                j = fail[j];
            }
            else ++j;
        }
    }
    printf("%d\n", ans);
    return 0;
}