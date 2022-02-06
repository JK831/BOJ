#include<iostream>
#include<string>
#include<vector>
#include<cstring>
 
#define endl "\n"
using namespace std;
 
int N, K, Answer;
bool Alphabet[26];
vector<string> V;
 
int Bigger(int A, int B) { if (A > B) return A; return B; }
 
void Input()
{
    // a n t i c 가 무조건 들어가
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        string Inp; cin >> Inp;
        V.push_back(Inp);
    }
 
    if (K < 5)
    {
        cout << 0 << endl;
        exit(0);
    }
}
 
int CanReadNum()
{
    bool Read;
    int Cnt = 0;
    for (int i = 0; i < V.size(); i++)
    {
        Read = true;
        string str = V[i];
        for (int j = 0; j < str.length(); j++)
        {
            if (Alphabet[str[j] - 'a'] == false)
            {
                Read = false;
                break;
            }
        }
 
        if (Read == true)
        {
            Cnt++;
        }
    }
    return Cnt;
}
 
void DFS(int Idx, int Cnt)
{
    if (Cnt == K)
    {
        Answer = Bigger(Answer, CanReadNum());
        return;
    }
 
    for (int i = Idx; i < 26; i++)
    {
        if (Alphabet[i] == true) continue;
        Alphabet[i] = true;
        DFS(i, Cnt + 1);
        Alphabet[i] = false;
    }
}
 
void Solution()
{
    Alphabet['a' - 'a'] = true;
    Alphabet['n' - 'a'] = true;
    Alphabet['t' - 'a'] = true;
    Alphabet['i' - 'a'] = true;
    Alphabet['c' - 'a'] = true;
    K = K - 5;
 
    DFS(0, 0);
    cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
 
    return 0;
}
