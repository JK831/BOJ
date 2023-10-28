#include <string>
#include <vector>

using namespace std;

// Key point: 시작위치부터 정방향으로 진행하며 현재 위치에서 다음 A가 아닌 알파벳의 위치를 파악하고
// 현재 위치에서 역방향으로 진행하여 다음 알파벳에 도달하는 경우와
// 다음 알파벳에 먼저 도달한 후 정방향으로 현재 알파벳에 도달하는 경우 중 더 적게 이동하는 경우의 횟수를 이전에 저장한 최소 횟수와 비교하여 더 작은 값을 저장.


// 현재 알파벳과 A와의 차, Z와의 차 중 작은 값을 더해준다.
// 좌우로 이동하는 횟수의 최댓값은 이름의 사이즈 (정방향 진행 시)
// 다음번 A가 아닌 알파벳의 위치를 찾고
// 시작 위치에서 현재 위치에 들렀다 역방향으로 진행하여 다음번 A가 아닌 알파벳의 위치에 들르는 경우와
// 다음번 A가 아닌 알파벳의 위치에 역방향으로 들른 후 현재 위치에 들르는 경우가 있다.
// -> 현재 알파벳의 위치 CurPos + (마지막 위치 - 다음번 A가 아닌 알파벳의 위치 + 1) NextNotA 두 값 중 작은 값을 더해준 값이 최소 이동 횟수.



int solution(string name) {
    int answer = 0;
    int NextNotA = 0;
    int LeftRightCount = name.size() - 1;
    int Length = name.size();

    for(int CurPos = 0; CurPos < name.size(); ++CurPos)
    {   
        answer += min(name[CurPos] - 'A','Z' - name[CurPos] + 1);        

        NextNotA = CurPos + 1;
        while(NextNotA < Length)
        {
            if(name[NextNotA] != 'A')
                break;
            ++NextNotA;
        }
        NextNotA = Length - NextNotA; // 배열 사이즈(Length - 1)에 역방향 진행시 추가되는 횟수 = 1 이므로 생략 (Length - 1 - NextNotA + 1)
        LeftRightCount = min(LeftRightCount, CurPos + NextNotA + min(CurPos, NextNotA));         
    }
    
    answer += LeftRightCount;
    return answer;
}