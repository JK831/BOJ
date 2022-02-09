#include <iostream>

using namespace std;

typedef struct _trie {
	struct _trie* next[2];
} Trie;

Trie* root;

long long power_2[31], input, result = 0;
int binary[100000][31];
int N;

Trie* makeNode() {
	Trie* tmp= (Trie*)malloc(sizeof(Trie));
	tmp->next[0] = NULL;
	tmp->next[1] = NULL;
	return tmp;
}

void initPower() {
	power_2[0] = 1;
	for (int i = 1; i < 31; i++) {
		power_2[i] = power_2[i - 1] * 2;
	}
}

void binaryToDecimal(long long input, int n) {
	for (int i = 30; i >= 0; --i) {
		if (input / power_2[i] == 1) {
			binary[n][30 - i] = 1;
			input -= power_2[i];
		}
		else binary[n][30 - i] = 0;
	}
}

void insert(int n) {
	Trie* cur = root;
	for (int i = 0; i < 31; ++i) {
		if (!cur->next[binary[n][i]]) cur->next[binary[n][i]] = makeNode();
		cur = cur->next[binary[n][i]];
	}
}

long long find(int n) {
	Trie* cur = root;
	long long tmp = 0;
	for (int i = 0; i < 31; ++i) {
		if (binary[n][i] && cur->next[0]) {
			cur = cur->next[0];
			binary[n][i] = 1;
		}
		else if (!binary[n][i] && cur->next[1]) {
			cur = cur->next[1];
			binary[n][i] = 1;
		}
		else {
			cur = cur->next[binary[n][i]];
			binary[n][i] = 0;
		}
	}

	for (int i = 0; i < 31; i++) {
		if (binary[n][i]) tmp += binary[n][i] * power_2[30 - i];
	}

	return tmp;
}

void Input()
{
    cin >> N;
}

void Solution()
{
    root = makeNode();
	initPower();
    
    for (int n = 0; n < N; ++n) {
		cin >> input;
		binaryToDecimal(input, n);
		insert(n);
	}
	for (int n = 0; n < N; ++n) {
		long long tmp = find(n);
		if (result < tmp) result = tmp;
	}
	cout << result;
}

void Solve()
{
    Input();
    Solution();
}

int main(void) {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
	Solve();
}