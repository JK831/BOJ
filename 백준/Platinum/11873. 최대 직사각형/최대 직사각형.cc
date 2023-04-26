#include<cstdio>
#include<algorithm>

using namespace std;

// Key point: 열 별로 높이가 얼마나 되는지 체크하며 직사각형의 넓이를 구해준다.
// 직사각형의 높이가 모든 구간에서 유지되면서 최댓값이어야 넓이가 최대가 될 수 있다.
// 이전에 가장 큰 높이가 나왔던 인덱스 (열 번호)를 stack에 저장

// 현재 열의 높이 체크 후 stack에 담긴 인덱스의 높이와 비교한다
// 현재 열의 높이가 더 낮다면: stack을 pop한 후 (현재 인덱스 - stack의 top값 - 1) * stack의 top값을 구해준다
// -> 스택을 하나씩 pop 하면서 구할 수 있는 직사각형의 최대 넓이를 구한다.
// 현재 열의 높이가 더 높다면: stack에 현재 인덱스 push

int N, M;
int main()
{
    while (scanf("%d %d", &N, &M) && N)
    {
        int r = 0, height[1001] = { 0, }, stk[1001], top;
        for (int i = 1; i <= N; i++)
        {
            stk[top = 0] = 0;
            
            for (int j = 1, x; j <= M; j++)
            {
                scanf("%d", &x);
                
                height[j] = (height[j] + 1) * x;
                
                while (height[stk[top]] > height[j])
                    r = max(r, (j - stk[top - 1] - 1) * height[stk[top--]]);
                
                stk[++top] = j;
            }
            
            while (top)
                r = max(r, (M - stk[top - 1]) * height[stk[top--]]);
        }
        
        printf("%d\n", r);
    }
    return 0;
}