#include <bits/stdc++.h>

using namespace std;

int N, Fail[1010101], A[1010101];
char S[1010101];

void Input()
{
    cin >> S; N = strlen(S);
}

void Failure()
{
    for(int i=1, j=0; i<N; i++){
        while(j && S[i] != S[j]) j = Fail[j-1];
        if(S[i] == S[j]) Fail[i] = ++j;
        if(i != N-1) A[Fail[i]] = 1;
    }
}

void Solution()
{
    Failure();
    for(int i=Fail[N-1]; i; i=Fail[i-1]) if(A[i]){ S[i] = 0; cout << S; return;}
    cout << -1;
}

void Solve()
{
    Input();
    Solution();
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    Solve();
    return 0;
}