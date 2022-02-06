#include<iostream>
#include<vector>
#include<cmath>
 
#define endl "\n"
#define MAX 100000

typedef long long ll;
using namespace std;
 
int N;
int Arr[MAX];
vector<int> Segment_Tree;
bool Inp_Flag;

/* Divide and conquer 사용한 풀이 */
 
int Min(int A, int B) { return A < B ? A : B; }
ll Max(ll A, ll B) { return A > B ? A : B; }
 
void Initialize()
{
    Segment_Tree.clear();
}
 
void Input()
{
    cin >> N;
    if (N == 0)
    {
        Inp_Flag = true;
        return;
    }
    for (int i = 0; i < N; i++) cin >> Arr[i];
}
 
void Make_SegmentTree(int Node, int Start ,int End)
{
    if (Start == End)
    {
        Segment_Tree[Node] = Start;
        return;
    }
 
    int Mid = (Start + End) / 2;
    Make_SegmentTree(Node * 2, Start, Mid);
    Make_SegmentTree(Node * 2 + 1, Mid + 1, End);
    
    if (Arr[Segment_Tree[Node * 2]] <= Arr[Segment_Tree[Node * 2 + 1]]) Segment_Tree[Node] = Segment_Tree[Node * 2];
    else Segment_Tree[Node] = Segment_Tree[Node * 2 + 1];
}
 
int Find_Idx(int Node, int Start, int End, int Left, int Right)
{
    if (Right < Start || Left > End) return -1;
    if (Left <= Start && End <= Right) return Segment_Tree[Node];
    
    int Mid = (Start + End) / 2;
    int Left_Idx = Find_Idx(Node * 2, Start, Mid, Left, Right);
    int Right_Idx = Find_Idx(Node * 2 + 1, Mid + 1, End, Left, Right);
 
    if (Left_Idx == -1) return Right_Idx;
    if (Right_Idx == -1) return Left_Idx;
    if (Arr[Left_Idx] <= Arr[Right_Idx]) return Left_Idx;
    return Right_Idx;
}
 
ll Find_Area(int Start, int End)
{
    int Min_Idx = Find_Idx(1, 0, N - 1, Start, End);
    ll Result = (ll)(End - Start + 1) * (ll)Arr[Min_Idx];
    
    if (Start <= Min_Idx - 1)
    {
        ll Left_Result = Find_Area(Start, Min_Idx - 1);
        Result = Max(Result, Left_Result);
    }
 
    if (Min_Idx + 1 <= End)
    {
        ll Right_Result = Find_Area(Min_Idx + 1, End);
        Result = Max(Result, Right_Result);
    }
 
    return Result;
}
 
void Solution()
{
    int Tree_Height = (int)ceil(log2(N));
    int Tree_Size = (1 << (Tree_Height + 1));
    Segment_Tree.resize(Tree_Size);
    Make_SegmentTree(1, 0, N - 1);
    ll Result = Find_Area(0, N - 1);
    cout << Result << endl;
}
 
void Solve()
{
    while (1)
    {
        Initialize();
        Input();
        if (Inp_Flag == true) return;
        Solution();
    }
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
 
    return 0;
}
