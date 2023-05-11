#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: A가 어떤 순서로 내든 B가 획득할 수 있는 최대 승점은 똑같다. -> A와 B 정렬 후 B의 각 원소보다 작은 A의 원소들을 최대한 매칭한다.
// A의 숫자를 이길 수 있는 큰 숫자가 있다면 해당 숫자로 승점을 챙긴다
// A의 숫자를 이길 수 없다면, 상대적으로 더 작은 숫자를 내서 큰 숫자를 남겨둔다

// -> A와 B를 큰 원소부터 하나씩 비교하며 A보다 B가 클 시 승점 추가 후 둘의 인덱스 이동
// => A의 원소가 클 시 A의 인덱스만 이동하여 B의 원소들을 각 원소들보다 작은 A의 원소들과 최대한 매칭하도록 한다.

int solution(vector<int> A, vector<int> B) 
{
    int answer = 0;
    
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    int A_Idx = A.size() - 1;
    int B_Idx = B.size() - 1;

    while (A_Idx >= 0)
    {
        int A_Score = A[A_Idx];
        int B_Score = B[B_Idx];
        if (A_Score < B_Score)
        {
            B_Idx--;
            answer++;
        }
        A_Idx--;
    }
    return answer;
}
