#include <iostream>
using namespace std;

int K, N, ans;
int line[10001];
int longest;
long long low, high, mid;

int main()
{
    cin >> K >> N;
    
    for (int i = 0; i < K; i++)
    {
        cin >> line[i];
        if (longest < line[i]) longest = line[i];
    }
    
    low = 1;
    high = longest;
    while (low <= high)
    {
        int count = 0;
        mid = (low + high) / 2;
        for (int i = 0; i < K; i++)
        {
             count += line[i] / mid;
        }
        if (count >= N)
        {
            low = mid +1;
            if (ans < mid) ans = mid;
        }
        else
            high = mid - 1;
    }
    
    cout << ans;
}