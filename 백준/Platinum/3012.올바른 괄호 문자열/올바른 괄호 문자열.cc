#include <iostream>

#include <string>

#include <cstring>

using namespace std;

 

const long long MOD = 100000;

const int MAX = 200;

 

int N;

string s;

long long cache[MAX][MAX];

string open = "({[", close = ")}]";

 
void Input()
{
    cin >> N >> s;
}
 

long long Solution(int start, int end)

{

        if (start > end)
             return 1;

 

        long long &result = cache[start][end];

        if (result != -1)
             return result;

 

        result = 0;

        //+=2인 이유는 그 사이도 쌍이 생겨야하므로

        for (int i = start + 1; i <= end; i += 2)

             for(int j = 0; j < open.size(); j++)

                 if(s[start] == open[j] || s[start] == '?')

                     if (s[i] == close[j] || s[i] == '?')
                     {
                          long long temp = Solution(start + 1, i - 1) * Solution(i + 1, end);

                          result += temp;

                          if (result >= MOD)
                              result = MOD + result % MOD;

                     }

        return result;

}

void Solve()
{
    Input();
    
    long long result = Solution(0, N - 1);

 

        if (result >= MOD)

                 printf("%05lld\n", result % MOD);

        else

                 cout << result << "\n";
}

int main(void)

{

        ios_base::sync_with_stdio(0);

        cin.tie(0);

        memset(cache, -1, sizeof(cache));

        Solve();

        return 0;

}