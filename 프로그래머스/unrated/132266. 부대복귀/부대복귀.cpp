#include <string>
#include <vector>
#include <queue>
using namespace std;

// Begin in destination, update the distance of each point using BFS
// When updating the distance is finished, return distance from destination of sources

vector<int> edge[100001];


vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer(sources.size()); // Reserve space
    
    vector<int> distFromDestination(n + 1, -1); // If there isn't edge between two points, the edge between two points present -1
    
    // Update edge information
    for (int i = 0; i < roads.size(); i++)
    {
        edge[roads[i][0]].push_back(roads[i][1]);
        edge[roads[i][1]].push_back(roads[i][0]);
    }
    
    // Update the distance with BFS
    
    queue<pair<int, int>> q; // Position, Distance from Destination
    q.push({destination, 0});
    distFromDestination[destination] = 0;
    
    while (!q.empty())
    {
        auto curPos = q.front().first;
        auto curDist = q.front().second;
        q.pop();
        
        for (int i = 0; i < edge[curPos].size(); i++)
        {
            int nextPos = edge[curPos][i];
            
            if (distFromDestination[nextPos] == -1 || distFromDestination[nextPos] > curDist + 1)
            {
                q.push({nextPos, curDist + 1});
                distFromDestination[nextPos] = curDist + 1;
            }
        }
    }
    
    for (int i = 0; i < sources.size(); i++)
        answer[i] = distFromDestination[sources[i]];
    
    return answer;
}