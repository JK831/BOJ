#include <iostream>

#include <algorithm>

#include <functional>

#include <string>

#include <vector>

using namespace std;

 

string S;

 

//N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[]를 계산

//pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이

vector<int> getPartialMatch(const string &N)

{

        int M = N.size();

        vector<int> pi(M, 0);

        //KMP로 자기 자신을 찾는다

        //N을 N에서 찾는다

        //begin=0이면 자기 자신을 찾아버리니까 안됨!

        int begin = 1, matched = 0;

        //비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록

        while (begin + matched < M)

        {

                 if (N[begin + matched] == N[matched])

                 {

                         matched++;

                         pi[begin + matched - 1] = matched;

                 }

                 else

                 {

                         if (matched == 0)

                                 begin++;

                         else

                         {

                                 begin += matched - pi[matched - 1];

                                 matched = pi[matched - 1];

                         }

                 }

        }

        return pi;

}

void Input()
{
    cin >> S;   
}

void Solution()
{
    //접미사도 되고 접두사도 되면 이미 2번 출현한 것이므로 여기서 최대길이 출력

        int result = 0;

        for (int i = 0; i < S.size(); i++)

        {

                 string temp=S.substr(i, S.size()); //문자열의 pop_front 같은 역할

                 vector<int> pi = getPartialMatch(temp);

                

                 sort(pi.begin(), pi.end(), greater<int>());

                 result = max(result, pi[0]);

        }

        cout << result << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
int main(void)

{
    Solve();
    return 0;
}