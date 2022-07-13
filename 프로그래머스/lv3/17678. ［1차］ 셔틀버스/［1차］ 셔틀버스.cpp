#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
string solution(int n, int t, int m, vector<string> timetable) 
{
    vector<int> Crew;
    for (int i = 0; i < timetable.size(); i++)
    {
        string S_Hour = "";
        S_Hour += timetable[i][0];
        S_Hour += timetable[i][1];
        int Hour = stoi(S_Hour);
        
        string S_Minute = "";
        S_Minute = S_Minute + timetable[i][3];
        S_Minute = S_Minute + timetable[i][4];
        int Minute = stoi(S_Minute);
        
        Crew.push_back(Hour * 60 + Minute);
    }
    sort(Crew.begin(), Crew.end());
 
    int Shuttle_Time = 540;
    int Crew_Idx = 0;
    int Answer_Time;
    for (int i = 1; i <= n; i++, Shuttle_Time += t)
    {
        int Cnt = 0;
        for (int j = Crew_Idx; j < Crew.size(); j++)
        {
            if (Crew[j] <= Shuttle_Time)
            {
                Crew_Idx++;
                Cnt++;
                if (Cnt == m) break;
            }
        }
 
        if (i == n)
        {
            if (Cnt == m) Answer_Time = Crew[Crew_Idx - 1] - 1;
            else Answer_Time = Shuttle_Time;
        }
    }
    
    string answer = "";
    int Hour = Answer_Time / 60;
    int Minute = Answer_Time % 60;
    char A = Hour / 10 + '0';
    char B = Hour % 10 + '0';
    char C = Minute / 10 + '0';
    char D = Minute % 10 + '0';
    
    answer += A;
    answer += B;
    answer += ':';
    answer += C;
    answer += D;
    
    return answer;
}