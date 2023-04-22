#include <string>
#include <vector>

using namespace std;

// Key point: 문자열을 인덱스를 증가시켜 살펴보며 110을 찾았을 경우 110을 문자열에서 지운다.
// 지운 후엔 지운 110이 있던 위치의 전, 후 문자열을 합쳤을 때 새로운 110이 나올 수 있으므로 지운 110의 인덱스에 -5를 하여 다시 110이 있는지 탐색할 수 있도록 한다.
// 사전순으로 빠르기 위해선 0 뒤에 1이 와야 하며 110 뒤에 1이 있게 만들어 줘야 한다.
// -> 지운 개수를 카운트한 후, 110을 모두 지운 문자열의 뒤부터 탐색하며 0을 만났을 시 해당 0의 바로 뒤에 지운 110들을 붙여준다.

vector<string> solution(vector<string> s) {
    
    for(int k = 0; k < s.size() ; k++)
    {
        string threeChar = "";
        int count = 0;
        for(int i = 0; i < s[k].size(); i++)
        {
            if (threeChar.size() == 3)
                threeChar = threeChar.substr(1, 2);
            
            threeChar += s[k][i];
            
            if(threeChar == "110")
            {
                s[k] = s[k].replace(i - 2, 3, "");
                count++;
                i = (i - 5) < -1 ? -1 : i - 5;
                threeChar = "";
            }
        }
        
        int a;
        
        for(a = s[k].size(); a > 0; a--)
            if(s[k][a - 1] == '0') break;
        while(count > 0)
        {
            count--;
            s[k] = s[k].replace(a, 0, "110");
        }
    }
    return s;
}