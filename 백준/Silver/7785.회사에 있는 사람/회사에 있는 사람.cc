#include <iostream>
#include <map>
using namespace std;

int main()
{
    
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    map<string, string, greater<>> m;
    int N;
    cin >> N;
    
    for(int i = 0; i < N; i++){
        string name, statement;
        
        cin >> name >> statement;
        m[name] = statement;
        
    }
    
    map<string, string>::iterator it;
    for(it = m.begin(); it!=m.end(); it++){
        if(it->second == "enter"){
            cout << it->first << "\n";
        }
    }
        
    return 0;
}