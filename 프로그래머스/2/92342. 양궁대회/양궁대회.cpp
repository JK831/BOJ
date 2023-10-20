#include <string>
#include <vector>

using namespace std;


// Key point: 과녁 배열을 순회하며 현재 과녁에 화살을 쏘는 경우, 쏘지 않는 경우를 탐색하여 가장 많은 점수를 얻으면서 낮은 점수 과녁을 많이 맞춘 경우 return.

// 화살을 쏴서 점수를 얻을 수 있는 경우 = 현재 남은 화살의 갯수 >= 어피치가 현재 과녁에 맞춘 화살의 갯수 + 1 일 때이다.
// 이 때 화살을 쏴서 점수를 얻거나 쏘지 않고 다음 과녁으로 넘어갈 수 있다.
// 0점 과녁일 경우 남은 화살을 모두 사용한다.

// DFS, 현재 과녁에 대해 화살을 쏠 수 있는 경우 화살을 쏜 경우, 쏘지 않는 경우 탐색
// 어피치보다 높은 점수를 받은 경우 저장된 가장 큰 점수 차보다 현재 점수 차가 클 시 현재 과녁 배열과 이전에 저장된 라이언의 과녁 배열 비교하여 낮은 점수의 과녁 많이 맞춘 배열을 라이언의 과녁 배열에 저장.

int MaxDiff = -1;
vector<int> Ryan, RyanAnswer, Appeach;

pair<int, int> CalculateScore()
{
    pair<int, int> Score = {0, 0};
    for (int i = 0; i < 11; ++i)
    {
        if (Ryan[i] == Appeach[i])
        {
            if (Ryan[i] == 0)
                continue;
            Score.second += (10 - i);
        }
        else
        {
            if(Ryan[i] > Appeach[i])
                Score.first += (10 - i);
            else
                Score.second += (10 - i);
        }
    }
    return Score;
}

void Check()
{
    pair<int, int> Score = CalculateScore();
    int RyanScore = Score.first;
    int AppeachScore = Score.second;
    int Diff = RyanScore - AppeachScore;
    if (Diff <= 0)
        return;
    
    if (MaxDiff == -1)
    {
        MaxDiff = Diff;
        RyanAnswer = Ryan;
    }
    else
    {
        if (Diff == MaxDiff)
        {
            for (int i = 10; i >= 0; --i)
            {
                if (Ryan[i] != 0 && RyanAnswer[i] == 0)
                {
                    RyanAnswer = Ryan;
                    break;
                }
                else if (Ryan[i] == 0 && RyanAnswer[i] != 0)
                {
                    break;
                }
                else if (Ryan[i] != 0 && RyanAnswer[i] != 0)
                {
                    if (Ryan[i] != RyanAnswer[i])
                    {
                        RyanAnswer = Ryan[i] > RyanAnswer[i] ? Ryan : RyanAnswer;
                        break;
                    }
                }
            }
        }
        else if (Diff > MaxDiff)
        {
            MaxDiff = Diff;
            RyanAnswer = Ryan;
        }
    }
}

void DFS(int ShotCount, int CurIdx, int n)
{
    if (ShotCount == n)
    {
        Check();
        return;
    }
    
    int RemainArrow = n - ShotCount;
    
    if (CurIdx == 10)
    {
        Ryan[CurIdx] = RemainArrow;
        DFS(ShotCount + RemainArrow, CurIdx + 1, n);
        Ryan[CurIdx] = 0;
    }
    else
    {
        if (RemainArrow >= Appeach[CurIdx] + 1)
        {
            Ryan[CurIdx] = Appeach[CurIdx] + 1;
            DFS(ShotCount + Appeach[CurIdx] + 1, CurIdx + 1, n);
            Ryan[CurIdx] = 0;
        }
        DFS(ShotCount, CurIdx + 1, n);
    }
}

vector<int> solution(int n, vector<int> info) {
    Ryan.resize(11, 0);
    Appeach = info;
    DFS(0, 0, n);
    if (MaxDiff == -1)
    {
        RyanAnswer.push_back(-1);
    }
    return RyanAnswer;
}