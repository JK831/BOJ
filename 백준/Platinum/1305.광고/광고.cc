#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
 
int L;
string text, pattern;
vector<int> table;

void Input()
{
    cin >> L >> text;
}

void Solution()
{
    pattern = text;
    table.resize(L+1, 0);
    int j = 0;
    for(int i = 1; i < L; i++){
        while(j > 0 && pattern[j] != text[i]){
            j = table[j-1];
        }
        if(pattern[j] == text[i]){
            table[i] = ++j;
        }
    }
    cout << L - table[L-1];
}

void Solve()
{
    Input();
    Solution();
}
 
int main(){
    Solve();
    return 0;
}