#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
string S, P;

vector<int> failFunc(string P)
{
    int plen = (int)P.length();
    vector<int> failVec(plen, 0);
    int j = 0;
    for(int i = 1; i<plen; i++){
        while(j>0 && P[i]!=P[j]){
            j = failVec[j-1];
        }
        if(P[i] == P[j]){
            failVec[i] = ++j;
        }
    }
    return failVec;
}

int KMP(string S, string P)
{
    vector<int> failVec = failFunc(P);
    int j = 0;
    
    for(int i = 0; i<S.length(); i++)
    {      //S 길이 기준
        while(j>0 && S[i] != P[j]){
            j = failVec[j-1];
        }
        if(S[i] == P[j])
        {
            if(j== P.length()-1) return 1;      //P 길이 기준
            else j+=1;
        }
    }
    return 0;
}

void Input()
{
    cin >> S >> P;
 
    N = (int)S.length();
}

void Solve()
{
    Input();
    cout << KMP(S, P);
}

int main(){
    Solve();
    return 0;
}