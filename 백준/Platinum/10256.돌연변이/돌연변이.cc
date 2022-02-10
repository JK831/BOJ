#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, M;

struct Trie {
	Trie* next[4];
	Trie* fail;
	int output;
	Trie() : output(0), fail(nullptr) {
		fill(next, next + 4, nullptr);
	}
	~Trie() {
		for (int i = 0; i < 4; i++) {
			if (next[i])
				delete next[i];
		}
	}
	void insert(string& s, int idx) {
		if (idx >= s.length()) {
			output = 1;
			return;
		}
		int x = s[idx] - '0';
		if (!next[x]) {
			next[x] = new Trie();
		}
		next[x]->insert(s, idx + 1);
	}
};

void fail(Trie* root) {
	queue<Trie*> q;
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		Trie* cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			Trie* nxt = cur->next[i];
			if (!nxt)
				continue;
			if (root == cur)
				nxt->fail = root;
			else {
				Trie* tmp = cur->fail;
				while (tmp != root && !tmp->next[i])
					tmp = tmp->fail;
				if (tmp->next[i])
					tmp = tmp->next[i];
				nxt->fail = tmp;
			}
			nxt->output += nxt->fail->output;
			q.push(nxt);
		}
	}
}

int Solution(string s, Trie* root)
{
    int ret = 0;
	Trie* cur = root;
	for (int i = 0; i < s.length(); i++) {
		int nxt = s[i] - '0';
		while (cur != root && !cur->next[nxt])
			cur = cur->fail;
		if (cur->next[nxt])
			cur = cur->next[nxt];
		ret += cur->output;
	}
	return ret;
}

void Solve() {
    int T;
	cin >> T;
	while (T--) {
		cin >> N >> M;
		string s, m;
		cin >> s >> m;
		Trie* root = new Trie();
		for (int i = 0; i < N; i++) {
			if (s[i] == 'A')
				s[i] = '0';
			else if (s[i] == 'C')
				s[i] = '1';
			else if (s[i] == 'G')
				s[i] = '2';
			else
				s[i] = '3';
		}
		for (int i = 0; i < M; i++) {
			if (m[i] == 'A')
				m[i] = '0';
			else if (m[i] == 'C')
				m[i] = '1';
			else if (m[i] == 'G')
				m[i] = '2';
			else
				m[i] = '3';
		}
		root->insert(m, 0);
		for (int i = 0; i <= M; i++) {
			for (int j = i + 2; j <= M; j++) {
				reverse(m.begin() + i, m.begin() + j);
				root->insert(m, 0);
				reverse(m.begin() + i, m.begin() + j);
			}
		}
		fail(root);
		cout << Solution(s, root) << "\n";
		delete root;
	}
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
    
    Solve();	
}