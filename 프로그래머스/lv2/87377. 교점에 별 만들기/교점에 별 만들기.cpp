#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 두 직선의 교점을 구하고 교점이 정수일 시 포함한다.

// x값들 중 가장 큰 값과 작은 값의 차가 정답 문자열의 너비
// y값들 중 가장 큰 값과 작은 값의 차가 정답 문자열의 높이

// 교점 구하는 공식
// Px = ((B * F) - (E * D)) / ((A * D) - (B * C))
// Py = ((E * C) - (A * F)) / ((A * D) - (B * C))


vector<string> solution(vector<vector<int>> line) 
{
    vector<string> answer;
    vector<pair<long long, long long>> Intersections;
    double A = 0; double B = 0; double E = 0;
    double C = 0; double D = 0; double F = 0;
    double BFED = 0; double ECAF = 0; double ADBC = 0;
    double X = 0; double Y = 0;
    
    for (int i = 0; i < line.size(); ++i)
    {
        A = line[i][0]; B = line[i][1]; E = line[i][2];
        for (int j = i + 1; j < line.size(); ++j)
        {
            C = line[j][0]; D = line[j][1]; F = line[j][2];

            BFED = B * F - E * D;
            ECAF = E * C - A * F;
            ADBC = A * D - B * C;

            if(ADBC == 0) continue;
         
            X = BFED / ADBC;
            Y = ECAF / ADBC;
            if(X - static_cast<long long>(X) == 0 && Y - static_cast<long long>(Y) == 0)
            {
                Intersections.push_back({X, Y});
            }
         
        }
    }

    pair<long long, long long> MaxYMinX;
    
    sort(Intersections.begin(), Intersections.end(), [](auto a, auto b)
        {
            return a.first < b.first;
        });
        
    MaxYMinX.first = Intersections[0].first;
    double Width = abs(Intersections[0].first - Intersections[Intersections.size() - 1].first) + 1;
    
    sort(Intersections.begin(), Intersections.end(), [](auto a, auto b)
        {
            return a.second > b.second;
        });
    double Height = abs(Intersections[0].second - Intersections[Intersections.size() - 1].second) + 1;
    MaxYMinX.second = Intersections[0].second;

    string Initial = "";
    Initial.append(Width, '.');
    vector<string> result(Height, Initial);

    for (int i = 0; i < Intersections.size(); ++i)
    {
        result[MaxYMinX.second - Intersections[i].second][Intersections[i].first - MaxYMinX.first] = '*';
    }

    answer = result;

    return answer;
}