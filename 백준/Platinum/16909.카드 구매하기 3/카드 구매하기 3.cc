#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll arr[1010101];
vector<int> idx;

int par[1010101];
ll lf[1010101];
ll rf[1010101];

void init(){
	for(int i=1; i<=n; i++){
		par[i] = i;
		lf[i] = i, rf[i] = i;
	}
}

int find(int v){
	return v == par[v] ? v : par[v] = find(par[v]);
}

bool merge(int u, int v){
	u = find(u); v = find(v);
	if(u == v) return 0;
	if(u < 1 || v < 1) return 0;
	if(u > n || v > n) return 0;
	par[u] = v;
	lf[v] = min(lf[v], lf[u]);
	rf[v] = max(rf[v], rf[u]);
	return 1;
}

void Input()
{
    cin >> n;
    init();
    
    for(int i = 1; i <= n; i++)
    {    
        cin >> arr[i];
        idx.push_back(i);
    }
}

void Solution()
{
    sort(idx.begin(), idx.end(), [](int a, int b){
		if(arr[a] != arr[b]) return arr[a] < arr[b];
		return a < b;
	});
	ll ans = 0;
	for(int i=0; i < idx.size(); i++)
    {
		int j = idx[i];
		if(arr[j] >= arr[j-1]) merge(j, j-1);
		if(arr[j] >= arr[j+1]) merge(j, j+1);
		if(i != idx.size()-1 && arr[j] == arr[idx[i+1]]){
			int k = idx[i+1];
			int r = j; if(arr[j] > arr[j+1]) r = rf[find(j+1)];
			if(arr[k] >= arr[k-1]) merge(k, k-1);
			int jj = find(j), kk = find(k);
			if(lf[kk] <= rf[jj]){
				ans += arr[j] * (j - lf[jj] + 1) * (r - j + 1);
				continue;
			}
		}
		int jj = find(j);
		ans += arr[j] * (rf[jj] - j + 1) * (j - lf[jj] + 1);
	}

	init();
	sort(idx.begin(), idx.end(), [](int a, int b){
		if(arr[a] != arr[b]) return arr[a] > arr[b];
		return a < b;
	});
    
	for(int i=0; i<idx.size(); i++)
    {
		int j = idx[i];
		if(arr[j] <= arr[j-1]) merge(j, j-1);
		if(arr[j] <= arr[j+1]) merge(j, j+1);
		if(i != idx.size()-1 && arr[j] == arr[idx[i+1]]){
			int k = idx[i+1];
			int r = j; if(arr[j] < arr[j+1]) r = rf[find(j+1)];
			if(arr[k] <= arr[k-1]) merge(k, k-1);
			int jj = find(j), kk = find(k);
			if(lf[kk] <= rf[jj]){
				ans -= arr[j] * (j - lf[jj] + 1) * (r - j + 1);
				continue;
			}
		}
		int jj = find(j);
		ans -= arr[j] * (rf[jj] - j + 1) * (j - lf[jj] + 1);
	}
	cout << ans;
}

void Solve()
{
    Input();
    Solution();
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
    Solve();
	return 0;
}