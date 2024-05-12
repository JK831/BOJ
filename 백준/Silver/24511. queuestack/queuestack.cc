#include <iostream>
#include <queue>
#include <stack>

/**
 * Key point: 첫 번째 자료구조부터 현재 번호에 해당하는 자료구조가 Queue인지 Stack인지에 따라
 * 다음 자료구조로 return할 값을 설정.
 * - Queue라면 현재 B에 저장되어 있는 값을 return 값으로 설정
 * - Stack이라면 전달받은 return 값을 그대로 전달
 * -> Queue일 때에만 전달할 값을 변경하면 되며 자료구조에는 변경된 값을 저장할 필요가 없고
 * -> Queue를 만나 값이 변경되었다면 그 Queue에 현재 return 값이 들어가고 return 값이 변경
 * -> 그 다음 Queue를 만났을 시 그 변경된 값이 저장된다.
 * --> 가장 마지막에 있는 Queue의 값이 최종적으로 반환 될 것이므로
 * --> Queue들에 있는 값을 stack에 push하여 마지막 Queue의 값부터 반환되도록 한다.
 * --> 그리고 이 stack에 있는 값을 마지막에 정답을 반환할 queue에 push, C수열의 원소들을 queue에 push
 * => 최종적으로 반환되는 값은 queue의 앞 M개 만큼의 값들
 */

#define NM_MAX 100001

int g_N;
int g_M;
bool g_A[NM_MAX];
int g_Ans[NM_MAX];
std::queue<int> g_q;
std::stack<int> g_stk;

void solution()
{
    scanf("%d", &g_N);
    for (int i = 0; i < g_N; ++i)
    {
        int input;
        scanf("%d", &input);
        g_A[i] = (bool)input;
    }
    for (int i = 0; i < g_N; ++i)
    {
        int input;
        scanf("%d", &input);
        if (g_A[i] == false)
        {
            g_stk.push(input);
        }
    }
    while (g_stk.empty() == false)
    {
        g_q.push(g_stk.top());
        g_stk.pop();
    }
    
    scanf("%d", &g_M);
    for (int i = 0; i < g_M; ++i)
    {
        int input;
        scanf("%d", &input);
        g_q.push(input);
    }
    
    for (int i = 0; i < g_M; ++i)
    {
        printf("%d ", g_q.front());
        g_q.pop();
    }
}

int main()
{
    solution();

    return 0;
}