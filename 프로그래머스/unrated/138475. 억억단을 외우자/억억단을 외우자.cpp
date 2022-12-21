#include <string>
#include <vector>

using namespace std;

int count[5000001] = {0,};
int maxAddressByNum[5000001] = {0,};

vector<int> solution(int e, vector<int> starts) {
    vector<int> answer;
    
    
    for (int i = 1; i <= e; i++)
    {
        count[i]++;
        for (int j = i + 1; j <= e / i; j++)
        {
            count[i * j] += 2;
        }
    }
    
    int maxVal = 0, maxValAddr = 0;
    
    for(int i = e ; i >= 0 ; i--)
    {
        maxValAddr = maxVal > count[i] ? maxValAddr : i;
        maxVal = maxVal > count[i] ? maxVal : count[i];
        maxAddressByNum[i] = maxValAddr;
    }
    
    for(int i = 0 ; i < starts.size() ; i++)
    {
        answer.push_back(maxAddressByNum[starts[i]]);
    }
    
    return answer;
}