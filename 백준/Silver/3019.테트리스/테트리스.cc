#include<iostream>

#define MAX 100
using namespace std;
 
int C, P, Answer;
int MAP[MAX];
 
void Input()
{
    cin >> C >> P;
    for (int i = 0; i < C; i++)
    {
        cin >> MAP[i];
    }
}
 
void Shape1()
{
    Answer = Answer + C;
    for (int i = 0; i < C - 3; i++)
    {
        if (MAP[i] == MAP[i + 1] && MAP[i + 1] == MAP[i + 2] && MAP[i + 2] == MAP[i + 3]) Answer++;
    }
}
 
void Shape2()
{
    for (int i = 0; i < C - 1; i++)
    {
        if (MAP[i] == MAP[i + 1]) Answer++;
    }
}
 
void Shape3()
{
    for (int i = 0; i < C - 2; i++)
    {
        if (MAP[i] == MAP[i + 1] && MAP[i + 1] == MAP[i + 2] - 1) Answer++;
    }
    for (int i = 0; i < C - 1; i++)
    {
        if (MAP[i] == MAP[i + 1] + 1) Answer++;
    }
}
 
void Shape4()
{
    for (int i = 0; i < C - 2; i++)
    {
        if (MAP[i] == MAP[i + 1] + 1 && MAP[i + 1] == MAP[i + 2]) Answer++;
    }
    for (int i = 0; i < C - 1; i++)
    {
        if (MAP[i] == MAP[i + 1] - 1) Answer++;
    }
}
 
void Shape5()
{
    for (int i = 0; i < C - 2; i++)
    {
        if (MAP[i] == MAP[i + 1] && MAP[i + 1] == MAP[i + 2]) Answer++;
        if (MAP[i] == MAP[i + 1] + 1 && MAP[i + 1] == MAP[i + 2] - 1) Answer++;
    }
    for (int i = 0; i < C - 1; i++)
    {
        if (MAP[i] == MAP[i + 1] - 1) Answer++;
        if (MAP[i] == MAP[i + 1] + 1) Answer++;
    }
}
 
void Shape6()
{
    for (int i = 0; i < C - 2; i++)
    {
        if (MAP[i] == MAP[i + 1] && MAP[i + 1] == MAP[i + 2]) Answer++;
        if (MAP[i] == MAP[i + 1] - 1 && MAP[i + 1] == MAP[i + 2]) Answer++;
    }
    for (int i = 0; i < C - 1; i++)
    {
        if (MAP[i] == MAP[i + 1]) Answer++;
        if (MAP[i] == MAP[i + 1] + 2) Answer++;
    }
}
 
void Shape7()
{
    for (int i = 0; i < C - 2; i++)
    {
        if (MAP[i] == MAP[i + 1] && MAP[i + 1] == MAP[i + 2]) Answer++;
        if (MAP[i] == MAP[i + 1] && MAP[i + 1] == MAP[i + 2] + 1) Answer++;
    }
    for (int i = 0; i < C - 1; i++)
    {
        if (MAP[i] == MAP[i + 1] - 2) Answer++;
        if (MAP[i] == MAP[i + 1]) Answer++;
    }
}
 
void Solution()
{
    if (P == 1) Shape1();
    else if (P == 2) Shape2();
    else if (P == 3) Shape3();
    else if (P == 4) Shape4();
    else if (P == 5) Shape5();
    else if (P == 6) Shape6();
    else if (P == 7) Shape7();
    
    cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    Solve();
    
    return 0;
}