#include <queue>
#include <iostream>  
#define MAX_TIME 60000000000
#define MAX_M 10000 + 1 
using namespace std;
 

int N, M; 

int arrM[MAX_M];
 
int main() {
    
    cin >> N >> M;
    
    if (N <= M) {
        cout << N;
        return 0;
    }
    
    for (int m_idx = 1; m_idx <= M; m_idx++) {
        int minute_required;
        cin >> minute_required;
        arrM[m_idx] = minute_required;
    } 
 
    // 이진탐색
    long long l = 0;
    long long r = MAX_TIME; 
    long long total_time = 0;
 
    // 해당 시간에 탑승할 수 있는 사람들을 세고 
    // N 보다 크거나 같으면 time 을 갱신한다. 
    while (l <= r) {
        long long mid = (l + r) / 2;  
        long long ridden_person = M; 
        for (int m_idx = 1; m_idx <= M; m_idx++) { 
            ridden_person += mid / arrM[m_idx];
        }
 
        if (ridden_person>=N) {
            total_time = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
 
    }
 
    // 찾은 시간의 이전 시간까지(total_time - 1) 탑승한 인원을 전부 더한다. 
    long long ridden_person = M;
    for (int m_idx = 1; m_idx <= M; m_idx++) {
        ridden_person += ((total_time - 1) / arrM[m_idx]);
    }
 
    // 찾은 시간에 탑승한 사람을 확인한다 
    for (int m_idx = 1; m_idx <= M; m_idx++) {
        if (total_time % arrM[m_idx] == 0) ridden_person++;
        if (ridden_person == N) {
            cout << m_idx << endl;
            break;
        }
    }
 
    return 0;
}