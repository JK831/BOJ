#include <string>
#include <vector>
#include <stack>
 
using namespace std;
 
struct NODE
{
    int Data;
    NODE *Prev;
    NODE *Next;
    NODE(int D)
    {
        Data = D;
        Prev = NULL;
        Next = NULL;
    }
};
 
struct LINKEDLIST
{
    NODE *Head;
    NODE *Tail;
 
    LINKEDLIST() : Head(NULL), Tail(NULL) {}
    void Insert(int _Data);
    NODE* Erase(NODE *Node);
    void Restore(NODE *Node);
};
 
void LINKEDLIST::Insert(int _Data)
{
    if (Head == NULL)
    {
        NODE *NewNode = new NODE(_Data);
        Head = NewNode;
        Tail = NewNode;
    }
    else
    {
        NODE *NewNode = new NODE(_Data);
        NewNode->Prev = Tail;
        Tail->Next = NewNode;
        Tail = Tail->Next;
    }
}
 
NODE* LINKEDLIST::Erase(NODE *Node)
{
    if (Node == Head)
    {
        Head = Node->Next;
        Node->Next->Prev = NULL;
        return Node->Next;
    }
    else if (Node == Tail)
    {
        Tail = Node->Prev;
        Node->Prev->Next = NULL;
        return Node->Prev;
    }
    else
    {
        Node->Prev->Next = Node->Next;
        Node->Next->Prev = Node->Prev;
        return Node->Next;
    }
}
 
void LINKEDLIST::Restore(NODE *Node)
{
    if (Node->Prev == NULL)
    {
        Head = Node;
        Node->Next->Prev = Node;
    }
    else if (Node->Next == NULL)
    {
        Tail = Node;
        Node->Prev->Next = Node;
    }
    else
    {
        Node->Prev->Next = Node;
        Node->Next->Prev = Node;
    }
}
 
stack<NODE*> Delete;
LINKEDLIST *List;
 
void Make_LinkedList(int N)
{
    List = new LINKEDLIST();
    for (int i = 0; i < N; i++) List->Insert(i);
}
 
string Solve(int N, int K, vector<string> Cmd)
{
    NODE *Iter = List->Head;
    for (int i = 0; i < K; i++) Iter = Iter->Next;
 
    for (int i = 0; i < Cmd.size(); i++)
    {
        string Str = Cmd[i];
        if (Str[0] == 'U')
        {
            string SX = Str.substr(2);
            int X = stoi(SX);
            for (int i = 0; i < X; i++) Iter = Iter->Prev;
        }
        else if (Str[0] == 'D')
        {
            string SX = Str.substr(2);
            int X = stoi(SX);
            for (int i = 0; i < X; i++) Iter = Iter->Next;
        }
        else if (Str[0] == 'C')
        {
            Delete.push(Iter);
            Iter = List->Erase(Iter);
        }
        else
        {
            NODE *Z = Delete.top();
            Delete.pop();
            List->Restore(Z);
        }
    }
    
    string Result = "";
    for (int i = 0; i < N; i++) Result += 'O';
    while (Delete.empty() == false)
    {
        NODE *Temp = Delete.top();
        Delete.pop();
 
        int Idx = Temp->Data;
        Result[Idx] = 'X';
    }
    return Result;
}
 
string solution(int n, int k, vector<string> cmd)
{
    string answer = "";
    Make_LinkedList(n);
    answer = Solve(n, k, cmd);
    return answer;
}