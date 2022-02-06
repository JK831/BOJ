#include <iostream>
#include <cstring>
using namespace std;

const int Max = 1000000;

int N, M;
int root[Max];
// Find 함수
int find(int num){
	if(root[num] < 0)
		return num;
	int parent = find(root[num]);
	root[num] = parent;
	return parent;
}
// Union 함수
void merge(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	root[a] = b;
}
int n,m,l;
int main(){
    ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);

	cin >> N >> M;
	memset(root, -1, sizeof(root));
	for (int i = 0; i < M; ++i){
		cin >> n >> m >> l;
		if(n == 0)
			merge(m,l);
		else if(n == 1){
			if(find(m) == find(l))
				cout << "YES" << '\n';
			else
				cout << "NO" << '\n';
		}
	}

    return 0;
}
