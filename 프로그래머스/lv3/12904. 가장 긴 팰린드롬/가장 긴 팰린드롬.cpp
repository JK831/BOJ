#include <string>

using namespace std;

// Key point: DP[n][m] = n번째 문자 ~ m번째 문자가 펠린드롬을 이루는지 여부
// 체크할 길이를 늘려가며 펠린드롬인지 체크. 펠린드롬의 조건 => s[n] = s[m] and DP[n + 1][m - 1] (n + 1 부터 m - 1까지가 펠린드롬이어야 n과 m도 펠린드롬이 될 수 있다.)

bool DP[2501][2501];

int solution(string s)
{
    int answer = 1;
    int sLen = s.size();
    
    // 자기 자신에 대한 펠린드롬 길이 = 1
    for (int i = 0; i < sLen; ++i)
        DP[i][i] = true;
    
    // 연속으로 같은 문자열이 나온 경우
    for(int i = 0; i < sLen - 1; ++i)
		if(s[i] == s[i + 1]) DP[i][i + 1] = true;
    
    for (int len = 3; len <= sLen; ++len) // len 길이의 문자열에 대해 펠린드롬 여부 체크
    {
		for(int i = 0; i + len <= sLen; ++i)
        {
			int j = i + len - 1;
            
			if(s[i] == s[j] and DP[i + 1][j - 1])
            {
				DP[i][j] = true;
				answer = len;
			}
		}
	}

    return answer;
}