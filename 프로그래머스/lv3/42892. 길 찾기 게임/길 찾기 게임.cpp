#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: y좌표가 큰 순으로 parent, child 여부 (depth)가 결정되고 두 노드가 같은 y좌표 (depth)를 가지고 있을 경우
// x좌표가 작은 노드가 바로 위 depth 노드의 left child, 큰 노드가 right child가 된다.

// 1. 노드를 가지고 트리를 구성, 각 노드는 x, y 좌표와 노드 번호(return 시 필요), left, right child를 가리키는 변수를 가져야 한다.
// 2. y좌표 기준으로 내림차순으로 주어진 배열의 원소들을 정렬하는데 같은 y좌표를 가진 경우 x좌표가 더 작은 노드가 먼저 오도록 정렬한다.
// 3. 정렬된 배열을 가지고 트리를 구성
// 4. 전위 순회의 결과, 후위 순회의 결과를 answer에 넣어 return
 
struct NODE
{
    int Idx;
    int x;
    int y;
    NODE* Left;
    NODE* Right;
};
 
bool Cmp(const NODE& A, const NODE& B)
{
    if (A.y >= B.y) // y가 큰 순으로 정렬
    {
        if (A.y == B.y) // y가 같은 경우 x가 작은 순으로 정렬
        {
            if (A.x < B.x)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}
 
void MakeBinaryTree(NODE* Root, NODE* Child)
{
    if (Root->x > Child->x) // 삽입할 노드의 x가 현재 노드의 x보다 작을 시 left child
    {
        if (Root->Left == NULL) // left child가 없는 경우
        {
            Root->Left = Child;
            return;
        }
        MakeBinaryTree(Root->Left, Child); // left child가 있는 경우 해당 node를 기준으로 하여 다시 탐색
    }
    else // 삽입할 노드의 x값이 현재 노드보다 클 시
    {
        if (Root->Right == NULL)
        {
            Root->Right = Child;
            return;
        }
        MakeBinaryTree(Root->Right, Child);
    }
}
 
void PreOrder(const NODE* Root, vector<int>& answer)
{
    if (Root == NULL) return;
    answer.push_back(Root->Idx);
    PreOrder(Root->Left, answer);
    PreOrder(Root->Right, answer);
}
 
void PostOrder(const NODE* Root, vector<int>& answer)
{
    if (Root == NULL) return;
    PostOrder(Root->Left, answer);
    PostOrder(Root->Right, answer);
    answer.push_back(Root->Idx);
}
 
vector<vector<int>> solution(vector<vector<int>> nodeinfo) 
{
    vector<vector<int>> answer;
    vector<NODE> Tree;
    
    for (int i = 0; i < nodeinfo.size(); ++i)
    {
        int x = nodeinfo[i][0];
        int y = nodeinfo[i][1];
        int idx = i + 1;
        Tree.push_back({ idx, x, y, NULL, NULL });
    }
    
    sort(Tree.begin(), Tree.end(), Cmp);
    
    NODE* Root = &Tree[0];
    
    for (int i = 1; i < Tree.size(); ++i) // Root 노드, 각 노드로 트리를 만들어준다
        MakeBinaryTree(Root, &Tree[i]);
    
    vector<int> PreV;
    PreOrder(Root, PreV);
    
    vector<int> PostV;
    PostOrder(Root, PostV);
    
    answer.push_back(PreV);
    answer.push_back(PostV);
    return answer;
}
