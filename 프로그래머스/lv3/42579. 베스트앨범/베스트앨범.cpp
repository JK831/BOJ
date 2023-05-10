#include <string>
#include <vector>
#include <map>

using namespace std;

// Key point: map을 사용하여 각 장르 별 재생 횟수, 각 노래 별 플레이 횟수를 저장.
// 그 후 많이 재생된 장르 순으로 해당 장르 내 가장 많이 재생된 노래 2곡 선별하여 answer에 넣어 return 한다.
 
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, int> music; // 각 장르 별 노래들의 총 재생 횟수 저장
    map<string, map<int, int>> musiclist; // 각 장르 별로 어떤 노래가 몇 번씩 재생 됐는지 저장
    
    for (int i = 0; i < genres.size(); i++)
    {
        music[genres[i]] += plays[i]; // music map에 장르별 재생 횟수 추가
        musiclist[genres[i]][i] = plays[i]; // musiclist map에 노래 고유번호와 플레이 횟수 추가
    }
    
    // 모든 장르에 대하여 반복
    while (music.size() > 0)
    {
        string genre{};
        int max{0}; // 가장 재생 횟수가 큰 장르
        
        for (auto mu : music)
        {
            if (max < mu.second)
            {
                max = mu.second;
                genre = mu.first;
            }
        }
        
        for (int i = 0; i < 2; ++i) // 2곡을 넣어야 하므로 2번 반복
        {
            int val = 0, ind = -1;
            
            for (auto ml : musiclist[genre]) // 장르 내 노래 중에서 제일 많이 플레이 된 노래 찾는다
            {
                if (val < ml.second)
                {
                    val = ml.second;
                    ind = ml.first;
                }
            }
            
            // 만약 현재 장르에 속한 노래가 0 ~ 1곡 밖에 없다면 반복 중지
            if (ind == -1)    break;
            
            answer.push_back(ind); // 리턴할 리스트에 노래번호 추가
            musiclist[genre].erase(ind);
        }

        music.erase(genre); // map 에서 현재 장르 삭제
    }
    
    return answer;
}