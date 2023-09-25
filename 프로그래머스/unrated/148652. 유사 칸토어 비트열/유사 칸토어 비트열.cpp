#include <string>
#include <vector>

using namespace std;

// Key point: 0이 나오는 위치는 현재 숫자를 5보다 작을 때까지 5로 나누었을 때 나머지가 2인 위치이다.

// 숫자가 5보다 작을 때 2번째가 아니면 (n % 5 != 2) 1이다.
// (5 * k) + 2 번째의 숫자는 항상 0이다.
// => 어떤 숫자 - 2 번째의 숫자 % 5 == 0 이면 해당 숫자는 0이다.

// 5^n 길이의 비트열에서 0이 연속으로 나오는 위치 (비트열의 3/5 지점 ~ 5/4 시작 지점 전)
// = [1 + 5^(n - 1) * 2, 5^(n - 1) * 3]
// => 이 위치는 5 이하의 숫자가 될 때까지 5로 계속해서 나누었을 시 나머지가 2가 된다.
// ex) 51 / 5 = 10 -> 10 / 5 = 2 -> 5 이하의 숫자가 되었으므로 2 % 5 = 2

// -> 만약 (현재 숫자 - 2) % 5 == 0 이면 false, 5로 나눈 몫을 계속해서 5로 나누면서 5보다 작아지면 해당 숫자를 5로 나눴을 때의 나머지가 2가 아닐 시 true


bool Check(long long Num)
{
    if (Num < 5 && Num % 5 != 2) return true;
    if ((Num - 2) % 5 == 0) return false;
    
    return Check(Num / 5);
}

int solution(int n, long long l, long long r) {
    int answer = 0;
    
    for (--l; l < r; ++l)
    {
        if (Check(l))
            ++answer;
    }
    
    return answer;
}