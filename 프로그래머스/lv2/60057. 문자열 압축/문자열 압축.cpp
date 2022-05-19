#include <string>

using namespace std;

int solution(string s) {
    
    int answer = s.size(); // 입력으로 들어온 문자열의 초기 사이즈
    
    for (int i = 1; i <= s.size() / 2; i++) // 문자열을 나눌 수 있는 최대 크기 = 문자열의 길이의 반.
    {
        int count = 1;
        string temp = "", a = "";
        a = s.substr(0, i); // 입력으로 들어온 문자열의 처음부터 i번째까지의 부분 문자열
        
        for (int j = i; j < s.size(); j += i)
        {
            if (a == s.substr(j, i)) count++; // 첫 부분 문자열의 크기만큼 지정된 부분 문자열과 다음 문자부터 부분 문자열의 크기만큼 자른 부분 문자열이 같을 때 count++
            else // 그게 아니라면 count를 문자로 바꾸어 temp에 더해주고 그 뒤에 a(현재 부분문자열)를 더해준다.
            {
                if (count > 1) temp += to_string(count);
                temp += a;
                a = s.substr(j, i);
                count = 1;
            }
        }
        if (count > 1) temp += to_string(count); // 입력 문자열을 부분문자열로 자를 수 있을 때까지 자르고 검사한 후에 count가 1보다 크다면(마지막 부분문자열에 도달하기 전에 똑같은 부분문자열이 있었다면) temp에 count 더해주고 아니라면 그대로 temp에 a 더해준다.
        temp += a;
        if (answer > temp.size()) answer = temp.size();
    }
    
    
    return answer;
}