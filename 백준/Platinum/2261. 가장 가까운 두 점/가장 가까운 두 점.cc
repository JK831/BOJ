#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MAX = 2000000000;

int N;
vector<pair<int, int>> arr;
// low번째 점과 high번째 점 사이 거리를 구한다
int Distance(int low, int high)
{
	int lowX = arr[low].first, lowY = arr[low].second;
	int highX = arr[high].first, highY = arr[high].second;
	
	int disX = highX - lowX, disY = highY - lowY;
	
	return disX * disX + disY * disY;
}

// 가장 가까운 두 점의 거리를 구하는 재귀함수를 이분 탐색을 통해 구현한다
int BinarySearch(int low, int high)
{
	// 기저 조건은 처음과 끝 숫자의 차이가 1인 경우다
	if(low == high)
		return MAX;
	
	if(low + 1 >= high)
		return Distance(low, high);
	
	int disMin = Distance(low, high);
	int tempDis = 0, mid = (low + high) / 2;
	
	// 왼쪽 영역의 최소 거리를 구하고
	if((tempDis = BinarySearch(low, mid)) < disMin)
    {
		disMin = tempDis;
	}
	// 오른쪽 영역의 최소 거리를 구하여 둘 중 최솟값을 찾는다
	if((tempDis = BinarySearch(mid + 1, high)) < disMin)
    {
		disMin = tempDis;
	}	
	
	vector<pair<int, int>> inner;
	// 중간 영역에서 기준선과 x값의 차이의 제곱이 최솟값 이하인 영역의 점들을 찾는다
	int lineX = arr[mid].first;
	// 왼쪽 영역
	for(int i = mid; i >= low; i--)
    {
		int x = arr[i].first, dist = lineX - x;
		if(disMin <= dist * dist) break;
		inner.push_back({arr[i].second, arr[i].first});
	}
	// 오른쪽 영역
	for(int i = mid + 1; i <= high; i++)
    {
		int x = arr[i].first, dist = lineX - x;
		if(disMin <= dist * dist) break;
		inner.push_back({arr[i].second, arr[i].first});
	}
	
	int len = inner.size();
	// 아무 점도 못찾았으면 최솟값을 반환한다
	if(len == 0) return disMin;
	// y값에 대해 정렬한다
	sort(inner.begin(), inner.end());
	
	for(int i = 0; i < len; i++)
    {
		int iX = inner[i].second, iY = inner[i].first;
		for(int j = i + 1; j < len; j++){
			int jX = inner[j].second, jY = inner[j].first;
			int distX = jX - iX, distY = jY - iY;
			// 두 점의 y좌표의 차이를 제곱한 값이 최솟값 이상이면 loop를 멈춘다
			if(disMin <= distY * distY) break;
			// 두 점의 x좌표의 차이를 제곱한 값이 최솟값 이상이면 건너뛴다
			if(disMin <= distX * distX) continue;
			
			int dist = distX*distX + distY*distY;
			if(dist < disMin)
				disMin = dist;
		}
	}
	
	return disMin;
}

void Input()
{
    scanf("%d",&N);
    
    arr = vector<pair<int, int>>(N);
	
	for(int i = 0; i < N; i++)
    {
		scanf("%d %d", &arr[i].first, &arr[i].second);
	}
}

void Solution()
{
    sort(arr.begin(), arr.end());
    printf("%d \n", BinarySearch(0, N-1));
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
	Solve();
    
    return 0;
}