#include<iostream>
#include<algorithm>
 
#define endl "\n"
#define MAX 4000
using namespace std;
 
int N;
long long Answer;
int Arr[4][MAX], AB[MAX * MAX], CD[MAX * MAX];
 
void Input()
{
    cin >> N;
 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> Arr[j][i];
        }
    }
}
 
void Solution()
{
    int Idx = 0;
    /* 4개의 배열을 2개의 배열로 만들어주는 과정
       : AB[] = 0번 배열과 1번 배열을 합쳤을 때 나올 수 있는 원소를 저장
       : CD[] = 2번 배열과 3번 배열을 합쳤을 때 나올 수 있는 원소를 저장 
    =================================================================*/
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            AB[Idx] = Arr[0][i] + Arr[1][j];
            CD[Idx] = Arr[2][i] + Arr[3][j];
            Idx++;
        }
    }
 
    /* 2개의 배열을 정렬 */
    sort(AB, AB + Idx);
    sort(CD, CD + Idx);
 
    int AB_Idx = 0;            // A배열은 0번 Index부터 (처음부터)
    int CD_Idx = Idx - 1;    // B배열은 마지막 Index부터 (마지막부터)
 
    while (AB_Idx < Idx && CD_Idx >= 0)        // 어느 한 곳이라도 모두 탐색하면 종료
    {
        if (AB[AB_Idx] + CD[CD_Idx] == 0)    // A배열 + B배열 = 0 인 경우
        {
            int Orig = AB_Idx;
            long long Same_AB = 0, Same_CD = 0;
 
            while (AB[AB_Idx] + CD[CD_Idx] == 0)
            {
                /* A배열에서 현재 원소와 같은 원소의 개수를 Count*/
                if (AB_Idx >= Idx) break;
                Same_AB++;
                AB_Idx++;
            }
 
            while (AB[Orig] + CD[CD_Idx] == 0)
            {
                /* B배열에서 현재 원소와 같은 원소의 개수를 Count*/
                if (CD_Idx < 0) break;
                Same_CD++;
                CD_Idx--;
            }
            
            Answer = Answer + (Same_AB * Same_CD);    // 곱한 값(조합의 개수)을 전체 결과값에 + 
        }
        else if (AB[AB_Idx] + CD[CD_Idx] < 0) AB_Idx++;
        else CD_Idx--;
    }
    cout << Answer << endl;
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