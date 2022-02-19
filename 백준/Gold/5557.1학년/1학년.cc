#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <cmath>

#define endl '\n'

using namespace std;

int N;
int arr[100];
long long dp[100][21] = {0};

void Input()
{
    cin >> N;
    
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}

void Solution(){
  dp[0][arr[0]] = 1;

  for (int i = 1; i < N-1; i++)
    for (int val = 0; val < 21; val++){
      if (dp[i-1][val]){
        if (val+arr[i] <= 20) dp[i][val+arr[i]] += dp[i-1][val];
        if (val-arr[i] >= 0) dp[i][val-arr[i]] += dp[i-1][val];  
      }
    }
  
  cout << dp[N - 2][arr[N - 1]];
}

void Solve()
{
    Input();
    Solution();
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
    
    return 0;
}