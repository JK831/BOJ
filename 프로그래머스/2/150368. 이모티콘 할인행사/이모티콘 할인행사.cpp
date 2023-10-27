#include <string>
#include <vector>

using namespace std;

// Key point: 각 이모티콘들에 대해 할인율이 각각 설정된 상태에서 해당 경우에 각 사용자의 플러스 서비스 가입 여부와 판매액을 구한다. 모든 할인율에 대해 탐색하여 플러스 서비스 가입자가 가장 많은 경우의 가입자 수와 판매액 return. (조합 구현 및 탐색)


int DiscountRate[4] = { 10, 20, 30, 40 };
int RatesIndex[7] = { 0, };
int EmoticonsSize;

vector<vector<int>> GUsers;
vector<int> GEmoticons;
vector<int> answer;

void Combination(int Index)
{
    if (Index == EmoticonsSize)
    {

        int PlusMember = 0;
        int Sales = 0;

        for (int User = 0; User < GUsers.size(); ++User)
        {

            int count = 0.0;

            for (int Emoticon = 0; Emoticon < EmoticonsSize; ++Emoticon)
            {
                if (GUsers[User][0] <= DiscountRate[RatesIndex[Emoticon]])
                {
                    count += GEmoticons[Emoticon]
                        * (100.0 - DiscountRate[RatesIndex[Emoticon]]) / 100;
                }
            }

            if (count >= GUsers[User][1])
                ++PlusMember;
            else
                Sales += count;
        }

        if (answer.size() == 0)
        {
            answer.push_back(PlusMember);
            answer.push_back(Sales);
        }
        else if (answer[0] < PlusMember || (answer[0] == PlusMember && answer[1] < Sales))
        {
                answer[0] = PlusMember;
                answer[1] = Sales;
        }
    }
    else
    {
        for (int i = 0; i < 4; ++i)
        {
            RatesIndex[Index] = i;
            Combination(Index + 1);
        }
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    GUsers = users;
    GEmoticons = emoticons;
    EmoticonsSize = emoticons.size();
    
    Combination(0);
    
    return answer;
}