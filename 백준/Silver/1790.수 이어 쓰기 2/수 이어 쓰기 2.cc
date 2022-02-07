#include <iostream>
#include <string>
using namespace std;

long long cal_length(int N)
{
    long long len = 0;
    for(int start = 1, i = 1; start <= N; start *= 10, i++)
    {
        int end = start * 10 - 1;
        if (end > N)
            end = N;
        len += (end - start + 1) * i;
    }
    return len;
}

int binary_search(int left, int right, int target)
{
    if (left >= right)
    {
        return right;
    }
    int mid = (left + right) / 2;
    
    long long len = cal_length(mid);
    
    if (len < target)
        return binary_search(mid + 1, right, target);
    else
        return binary_search(left, mid, target);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // 입력
    int N, K;
    cin >> N >> K;
    // 수의 길이가 K보다 작은 경우
    if (cal_length(N) < K)
    {
        cout << -1;
        return 0;
    }
    
    int num = binary_search(1, N, K);
    
    int num_len = cal_length(num);
    
    string num_to_string = to_string(num);
    
    cout << num_to_string[(num_to_string.size() - 1 - (num_len - K))];
    return 0;
}
