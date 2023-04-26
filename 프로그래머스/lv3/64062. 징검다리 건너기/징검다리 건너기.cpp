#include <string>
#include <vector>
#include <map>

using namespace std;

// Key point: 슬라이드 윈도우를 이용, 슬라이드 윈도우의 크기를 k로 설정했을 때 슬라이드 윈도우 내의 모든 원소가 0보다 작을 시 -> 건널 수 없게 된다
// 따라서 각 슬라이드 윈도우 내에서의 최댓값을 구하고, 구한 최댓값들 중 최솟값을 구하여 return
// -> 구한 최댓값들 중 최솟값이 아닌 다른 값(최솟값보다 큰 수)을 사용할 시 어떤 슬라이드 내의 모든 원소가 0보다 작은 경우 생기므로 건널 수 없게 된다.
// **윈도우는 multimap을 사용하여 구현해준다.**


int solution(vector<int> stones, int k) {
    int answer = 0;
    
    multimap<int, int, greater<int>> m;
	int size = stones.size();

	// 길이가 k인 윈도우 생성
	for (int i = 0; i < k; ++i)
		m.insert({stones[i], i});

	// 초기값 설정
	auto iter = m.begin();
	answer = iter->first;

	// 각 윈도우 내 최댓값 추출
	for (int i = 0; i < size - k; ++i)
    	{
		// 한 칸씩 이동
		iter = m.find(stones[i]);
		m.erase(iter);
		m.insert({stones[i + k], i + k});

		iter = m.begin();
		if (iter->first < answer)
			answer = iter->first;
	}
    
	return answer;
}
