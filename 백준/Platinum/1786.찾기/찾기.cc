#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
 
typedef long long ll;
 
using namespace std;
 
string text, pattern;
vector<int> table;
vector<int> idxans;
int ans = 0;
 
void Input(){
    getline(cin, text);
    getline(cin, pattern);
}
 
void failure_function(){
    table.resize(pattern.size(), 0);
    int j = 0;
    for(int i = 1; i < pattern.size(); i++){
        while(j > 0 && pattern[i] != pattern[j]){
            j = table[j-1];
        }
        if(pattern[i] == pattern[j]){
            table[i] = ++j;
        }
    }
}
 
void KMP()
{
    int j = 0;
    for(int i = 0; i < text.size(); i++){
        while(j > 0 && text[i] != pattern[j]){
            j = table[j-1];
        }
        if(text[i] == pattern[j]){
            if(j == pattern.size()-1){
                idxans.push_back(i - pattern.size() + 2);
                ans++;
                j = table[j];
            }
            else{
                j++;
            }
        }
    }
}

void Solution()
{
    failure_function();
    KMP();
    
    cout << ans << "\n";
    for(auto &w : idxans)
        cout << w << " ";   
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