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
    vector<pair<long long, long long>> v;
    double v1num1 = 0; double v1num2 = 0; double v1num3 = 0;
    double v2num1 = 0; double v2num2 = 0; double v2num3 = 0;
    double BFED = 0; double ECAF = 0; double ADBC = 0;
    double x = 0; double y = 0;
    
    for (int i = 0; i < line.size(); i++)
    {
        v1num1 = line[i][0]; v1num2 = line[i][1]; v1num3 = line[i][2];
        for (int j = i + 1; j < line.size(); j++)
        {
            v2num1 = line[j][0]; v2num2 = line[j][1]; v2num3 = line[j][2];

            BFED = v1num2 * v2num3 - v1num3 * v2num2;
            ECAF = v1num3 * v2num1 - v1num1 * v2num3;
            ADBC = v1num1 * v2num2 - v1num2 * v2num1;

            if(ADBC != 0)
            {
                x = BFED / ADBC;
                y = ECAF / ADBC;
                if(x - (long long)x == 0 && y - (long long)y == 0)
                {
                    v.emplace_back(pair<long long, long long>{x, y});
                }
            }
        }
    }

    pair<long long, long long> pr;
    sort(v.begin(), v.end(), [](auto a, auto b)
        {
            return a.first < b.first;
        });
    pr.first = v[0].first;
    double size1 = abs(v[0].first - v[v.size() - 1].first) + 1;
    sort(v.begin(), v.end(), [](auto a, auto b)
        {
            return a.second > b.second;
        });

    double size2 = abs(v[0].second - v[v.size() - 1].second) + 1;

    pr.second = v[0].second;

    string st1 = "";
    st1.append(size1, '.');
    vector<string> result(size2, st1);

    for (int i = 0; i < v.size(); i++)
    {
        result[(long long)pr.second - v[i].second][(long long)v[i].first - pr.first] = '*';
    }

    answer = result;

    return answer;
}