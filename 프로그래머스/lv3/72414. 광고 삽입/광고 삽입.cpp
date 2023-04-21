#include <string>
#include <vector>

using namespace std;

#define MAX 360010 // 3600 * 99 + 60 * 59 + 59 -> 최대 재생 시간

int arr[MAX];

// Key point: 누적합, Sliding window algorithm을 이용. 어떤 구간에서의 누적합이 가장 큰지를 판별하여 해당 구간의 시작 시간을 return.
// 공익 광고의 재생시간 크기의 윈도우를 설정하고 동영상 재생시간의 처음부터 끝까지 슬라이딩하며 윈도우 내 원소들의 값이 가장 큰 구간을 return
// 시청자들의 누적 시청시간을 누적합으로 구한다. -> 각 시청자가 시청을 시작한 시간에 1을 더해주고 시청이 끝난 시간에 -1을 해주면 누적합을 구할 때 시청 구간은 1 값을 가지고 그 이외의 구간은 0 값을 가지게 된다.

int time_to_sec(string time)
{
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    int s = stoi(time.substr(6, 2));
    
    return 3600 * h + 60 * m + s;
}

string time_to_string(int t)
{
    string ret = "";
    
    int h = t / 3600; t %= 3600;
    int m = t / 60;
    int s = t % 60;
    
    ret += h >= 10 ? to_string(h) : ("0" + to_string(h));
    ret += ":";
    ret += m >= 10 ? to_string(m) : ("0" + to_string(m));
    ret += ":";
    ret += s >= 10 ? to_string(s) : ("0" + to_string(s));
    
    return ret;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    int END = time_to_sec(play_time);
    int ADV = time_to_sec(adv_time);
    
    int answer = 0;
    long long sum = 0;
    
    for(string log: logs)
    {
        int t1 = time_to_sec(log.substr(0, 8));
        int t2 = time_to_sec(log.substr(9));
        
        // 누적합
        arr[t1] += 1;
        arr[t2] -= 1;
    }
    
    // 누적합 계산
    for(int i = 0; i < END - 1; ++i)
        arr[i+1] += arr[i];
    
    // 공익광고 재생시간 윈도우 설정
    for(int i = 0; i < ADV; ++i)
        sum += arr[i];

    long long max_sum = sum;
    for(int i = ADV; i < END; ++i)
    {
    	// 한 칸씩 슬라이딩하면서 sum 계산
        sum -= arr[i-ADV];
        sum += arr[i];
        
        if(sum > max_sum)
        {
            max_sum = sum;
            answer = i - ADV + 1;
        }
    }
    
    return time_to_string(answer);
}