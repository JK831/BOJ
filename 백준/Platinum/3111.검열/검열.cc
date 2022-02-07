#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

string A;
string T;
deque<char> dq_front;
deque<char> dq_rear;


void Input()
{
    cin >> A >> T;
}

void Solution()
{
    int front_index, last_index;
    front_index = 0;
    last_index = T.size() - 1;
    
    while (front_index <= last_index)
    {
        while (front_index <= last_index)
        {
            bool delete_flag = false;
            dq_front.push_back(T[front_index]);
            front_index++;
            if (dq_front.size() >= A.size())
            {
                delete_flag = true;
                for (int i = 0; i < A.size(); i++)
                {
                    if (A[i] != dq_front[dq_front.size() - A.size() + i])
                    {
                        delete_flag = false;
                        break;
                    }
                }
            }
            if (delete_flag == true)
            {
                for (int i = 0; i < A.size(); i++)
                    dq_front.pop_back();
                break;
            }
                
        }
        
        while (front_index <= last_index)
        {
            dq_rear.push_front(T[last_index]);
            last_index--;
            bool delete_flag = false;
            if (dq_rear.size() >= A.size())
            {
                delete_flag = true;
                for (int i = 0; i < A.size(); i++)
                {
                    if (A[i] != dq_rear[i])
                    {
                        delete_flag = false;
                        break;
                    }
                }
                
            }
            if (delete_flag == true)
            {
                for (int i = 0; i < A.size(); i++)
                    dq_rear.pop_front();
                break;
            }
        }
    }
    
    string ans;
    
    for (int i = 0; i < dq_front.size(); i++)
        ans.push_back(dq_front[i]);
    for (int i = 0; i < dq_rear.size(); i++)
        ans.push_back(dq_rear[i]);
    while (ans.find(A) < 300000)
        ans.erase(ans.find(A), A.size());
    
    if (!ans.empty())
        cout << ans << "\n";
    
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