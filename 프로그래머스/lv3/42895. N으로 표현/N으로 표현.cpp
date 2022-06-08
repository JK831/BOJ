#include <vector>
#include <unordered_set>

using namespace std;

int get_Ns(int N, int rpt)
{
    int result = N;
    
    for (int i = 1; i <= rpt; i++)
        result = result * 10 + N;
    
    return result;
}

int solution(int N, int number) {
    if (N == number) return 1;

    // DP에는 N을 x개 사용하여 만들 수 있는 수들이 들어간다.
    unordered_set<int> DP[8]; // 순서 상관없어도 되기 때문에 unordered_set 사용
    
    // N을 k번 써서 만들 수 있는 수 = N을 (k - i) 번 써서 만들 수 있는 수 + N을 i번 써서 만들 수 있는 수. i를 k - 1까지 증가시켜가며 체크한다.
    
    DP[0].insert(N); // N을 한 개 써서 만들 수 있는 수는 N 하나 뿐이다.
    
    for (int k = 1; k < 8; k++) // N을 2~8개 써서 만들 수 있는 수들 넣어줌
    {
        DP[k].insert(get_Ns(N, k)); // 먼저 N을 k번 붙여 만들어지는 수 넣는다.
        
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (i + j + 1 != k) continue; // k - i와 i를 i와 j로 구분해서 반복문 실행하도록 하였다.
                
                for (int a : DP[i])
                {
                    for (int b : DP[j])
                    {
                        DP[k].insert(a + b);
                        DP[k].insert(a * b);
                        
                        // 0보다 작은 값 존재하면 안되므로 -와 /는 조건 검사
                        if (a - b > 0) DP[k].insert(a - b);
                        if (a / b > 0) DP[k].insert(a / b);
                    }
                }
            }
        }
        if (DP[k].find(number) != DP[k].end())
            return k + 1;
    }
    
    return -1;
}