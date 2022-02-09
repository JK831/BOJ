#include <bits/stdc++.h>

#define MAX 1000

using namespace std;

int N, Q;

vector<string> patterns(MAX);
vector<string> words(MAX);

struct Trie {
public:
	bool isEnd;
	map<char, Trie*> child;
	Trie* fail;

	Trie() : isEnd(false), fail(nullptr) {}

	void Insert(string pattern) {
		Trie* now = this;
		int m = pattern.length();
		for (int i = 0; i < m; ++i) {
			if (now->child.find(pattern[i]) == now->child.end())
				now->child[pattern[i]] = new Trie;
			now = now->child[pattern[i]];

			if (i == m - 1) now->isEnd = true;
		}
	}

	void Fail() {  // BFS + KMP
		Trie* root = this;
		queue<Trie*> q;

		q.push(root);

		while (!q.empty()) {
			Trie* now = q.front();
			q.pop();

			for (auto& ch : now->child) {

				Trie* next = ch.second;
				if (now == root)
					next->fail = root;
				else {
					Trie* prev = now->fail;
					while (prev != root && prev->child.find(ch.first) == prev->child.end())
						prev = prev->fail;
					if (prev->child.find(ch.first) != prev->child.end())
						prev = prev->child[ch.first];
					next->fail = prev;
				}

				if (next->fail->isEnd)
					next->isEnd = true;

				q.push(next);
			}
		}
	}
};
Trie* root = new Trie;

// 검색어들이 모여 있는 트라이를 통해 탐색하며 word 의 부분 문자열과 일치하는 것을 처음으로 찾아내자마자 return true 하고 종료함
bool KMP(string word, Trie* root) {
	Trie* now = root;
	int n = word.length();
	for (int i = 0; i < n; ++i) {
		while (now != root && now->child.find(word[i]) == now->child.end())
			now = now->fail;
		if (now->child.find(word[i]) != now->child.end())
			now = now->child[word[i]];
		if (now->isEnd)
			return true;
	}
	return false;
}

void Input()
{
    cin >> N;
    for (int i = 0; i < N; ++i)
		cin >> patterns[i];
    
    cin >> Q;
    for (int i = 0; i < Q; ++i)
		cin >> words[i];
}

void Solution()
{
    for (int i = 0; i < N; ++i)
		root->Insert(patterns[i]);
	root->Fail();

	
	for (int i = 0; i < Q; ++i) {
		if (KMP(words[i], root))
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
}

void Solve()
{
    Input();
    Solution();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Solve();
    
    return 0;
}