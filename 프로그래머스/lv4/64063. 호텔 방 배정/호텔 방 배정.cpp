#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Key point: Map을 사용하여 이미 배정된 방인지를 체크하고 이미 배정된 방이라면 다음 방을 배정할 수 있도록 Map의 Key를 방 번호로, Value에 다음 방 번호를 저장하여 관리한다.

unordered_map<long long, long long> rooms;

long long Find(long long num)
{
    if (rooms[num] == 0) // 방이 비어있다면
    {
        rooms[num] = num + 1;
        return num;
    }
    else return rooms[num] = Find(rooms[num]); // 방이 이미 배정되어 있으면 다음 빈 방을 찾으면서 각 방이 다음으로 가리키는 비어 있는 방으로 값 갱신
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer(room_number.size());
    
    for (int i = 0; i < room_number.size(); ++i)
    {
        answer[i] = Find(room_number[i]);
    }
    
    return answer;
}