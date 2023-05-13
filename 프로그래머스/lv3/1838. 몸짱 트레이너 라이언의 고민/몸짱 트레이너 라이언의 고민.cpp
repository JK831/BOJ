#include <vector>
#include <algorithm>

using namespace std;

// Key point: 구간합을 사용하여 가장 사람이 몰린 시간 구한 후, 락커 내 두 위치 사이에 허용되는 최대 거리에서부터 시작하여 거리를 줄여가며 락커를 배정하여 배정해야 할 사람의 수를 만족시켰을 시의 거리를 return 한다.

// 1. 구간합을 사용하여 가장 사람이 몰린 시간대의 사람 수를 구한다.
// 2. 두 락커 사이 최대 거리 (= 2 * n - 2) 부터 시작하여 거리를 줄여가며 락커의 모든 칸을 순회하는데, 현재까지 배정된 모든 락커로부터 현재 거리 이상 떨어져있는, 배정 가능한 칸을 찾아 배정한다.
// 3. 모든 사람을 배정했다면 현재 거리 return.


const int MAX = 1320 - 600 + 10;

struct Location
{
    int x;
    int y;
};

int GetDistance(const Location& a, const Location& b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool CanPlaceFurther(const Location& coord, int maxDistance, vector<Location> &peoples)
{
	for (Location p : peoples)
	{
		if (GetDistance(p, coord) < maxDistance)
			return false;
	}

	return true;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, int m, vector<vector<int>> timetable) {
	int answer = 0;
	int numberOfPeople[MAX] = { 0, };
    
    // timetable을 순회하며 구간합을 구해준다.
	for (vector<int> t : timetable)
	{
		numberOfPeople[t[0] - 600]++;
        numberOfPeople[t[1] - 600 + 1]--;	
	}
    
    int sum = 0;
	int maxNumOfPeople = 0;

	for (int i = 0; i <= 720; ++i)
    {
        sum += numberOfPeople[i];
        numberOfPeople[i] = sum;
        maxNumOfPeople = max(maxNumOfPeople, numberOfPeople[i]);   
    }

	if (maxNumOfPeople <= 1) // 손님이 겹치는 시간이 없을 경우
		return 0;
    
    // 거리를 줄여가며 락커를 배정
	for (int distance = 2 * n - 2; distance > 0; --distance)
	{
		for (int y = 0; y < n; ++y)
		{
			for (int x = 0; x < n; ++x)
			{
				vector<Location> peoples;
				peoples.push_back({ x, y });

				for (int y2 = y; y2 < n; ++y2)
				{
					for (int x2 = 0; x2 < n; ++x2)
					{
						if (y2 == y and x2 <= x)
							continue;

						if (CanPlaceFurther({ x2, y2 }, distance, peoples))
							peoples.push_back({ x2, y2 });

						if (peoples.size() == maxNumOfPeople)
							return distance;
					}
				}
			}
		}
	}

	return answer;
}