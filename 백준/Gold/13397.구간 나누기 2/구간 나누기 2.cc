#include <iostream>
using namespace std;

int N, M;
int a[5001];
 
bool count_section(int size) {
    int cnt = 1;   
    int mini = a[0];
    int maxi = a[0];
    int idx = 0;
    for (int j = idx + 1 ; j < N; j++) {
        maxi = max(maxi, a[j]);
        mini = min(mini, a[j]);
        if (maxi - mini > size) {
            cnt++;
            idx = j;
            maxi = mini = a[j];
        }        
    }
    return cnt <= M;
}
 
int main() {

    cin >> N >> M;
    int r = 0;
    
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        r = max(r, a[i]);
    }
    
    int l = 0;
    int ans = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (count_section(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << ans;
}
