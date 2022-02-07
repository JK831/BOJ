#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;

unordered_map<string, int> umap;
vector<string> ansVec;

void Input()
{
    cin >> N >> M;
    
    string str1 = "";
    for(int i = 0; i<N; i++){
        cin >> str1;
        umap[str1] = 0;
    }
    string str2 = "";
    for(int i = 0; i < M; i++){
        cin >> str2;
        if(umap.find(str2)!=umap.end()){    //보도 못한 사람이 듣도 못한 사람 명단에도 있으면
            ansVec.push_back(str2);
        }
    }
}

void Solution()
{
    sort(ansVec.begin(), ansVec.end());
    
    cout << ansVec.size() << "\n";
    
    for(int i = 0; i<ansVec.size(); i++)
    {
        cout << ansVec[i] << "\n";
    }
}

void Solve()
{
    Input();
    Solution();
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    Solve();
    
    return 0;
}