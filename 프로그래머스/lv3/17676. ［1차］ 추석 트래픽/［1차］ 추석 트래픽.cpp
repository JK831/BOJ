#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<string> lines) {
    int answer = 0;
    vector<pair<int, int>> response;
    
    for(int i = 0; i < lines.size(); i++)
    {
        string h, m, s, ms;
        int ih, im, is, process;
        
        lines[i].pop_back();
        h = lines[i].substr(11, 2);
        m = lines[i].substr(14, 2);
        s = lines[i].substr(17, 2);
        ms = lines[i].substr(20, 3);
        process = stof(lines[i].substr(24, 5)) * 1000;
        
        ih = stoi(h) * 3600 * 1000;
        im = stoi(m) * 60 * 1000;
        is = stoi(s) * 1000 + stoi(ms);
        
        response.push_back(make_pair(ih + im + is - process + 1, ih + im + is));
    }
    
    for(int i = 0; i < lines.size(); i++)
    {
        int end_time = response[i].second + 1000;
        int count = 0;
        
        for(int j = i; j < lines.size(); j++)
        {
            if(response[j].first < end_time)
                count++;
        }
        
        if(answer < count)
            answer = count;
    }
    return answer;
}