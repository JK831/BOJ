#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
int n, m;
int arr[100001];
int main() {

	int l, r = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
    {
		cin >> arr[i];
		r += arr[i];	// 최대값 r은 모든 배열의 합
	}
    
	l = *max_element(arr, arr + n);	// 최소값 l은 배열의 max값

	while (l <= r) {	
		int mid = (l + r) / 2;	// 현재 블루레이 길이

		int sum = 0, cnt = 0;	// mid일때 블루레이 수 구하기
        
		for (int i = 0; i < n; i++)
        {
			if (sum + arr[i] > mid)
            {
				sum = 0;
				cnt++;
			}
			sum += arr[i];
		}
		if (sum != 0) cnt++;	
		
        	// 블루레이 수와 m 비교하여 l,r값 조정하기 
		if (cnt > m)
        {
			l = mid + 1;
		}
		else
        {
			r = mid - 1;
		}
	}
    
	cout << l;
	return 0;
}