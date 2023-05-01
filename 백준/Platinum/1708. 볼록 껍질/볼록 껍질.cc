#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

// Key point: Graham scan 알고리듬 사용
// Graham scan:
//     1. y가 가장 작은 점을 구한다.
//     2. 그 점을 기준으로 직선의 각을 정렬한다.
//     3. 가장 작은점부터 조사하여 블록 껍질 확인 후 추가한다.
// hull의 뒤에서 2번째 값, 1번째 값, 그리고 point의 3번째 값을 비교하여
// 반시계가 아니면 hull의 맨 뒤의 점을 뺀다.
// 반시계이면 해당 점을 포함한 상태로 다음점을 비교한다.
// 반시계방향의 여부는 ccw를 활용하여 판별

typedef long long ll;

int N;

struct Point
{
   ll x, y;
   Point(ll a, ll b) :x(a), y(b) {};
   Point() {};
   bool operator<(const Point &rhs) const
   {
      if (x != rhs.x) return x < rhs.x;
      return y < rhs.y;
   }
};
vector<Point> point;


// ** Counter clock wise -> ab x ac (벡터 외적)의 결과가 양수일 시 a를 기준으로 b, c가 반시계방향으로 존재한다
ll ccw(Point pt1, Point pt2, Point pt3)
{
   ll ret = pt1.x * pt2.y + pt2.x * pt3.y + pt3.x * pt1.y;
   ret -= (pt2.x * pt1.y + pt3.x * pt2.y + pt1.x * pt3.y);
   return ret;
}

ll dist(Point pt1, Point pt2)
{
   ll dx = pt2.x - pt1.x;
   ll dy = pt2.y - pt1.y;
   return dx * dx + dy * dy;
}

void Input()
{
    cin >> N;
    point.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> point[i].x >> point[i].y;
    }
}

void Solve()
{   
    vector<Point> hull;
    swap(point[0], *min_element(point.begin(), point.end()));
    sort(point.begin() + 1, point.end(), [](Point x, Point y){
       ll cw = ccw(point[0], x, y);
       if (cw == 0) return dist(point[0], x) < dist(point[0], y);
       return cw > 0;
    });

    for (auto i : point)
    {
        // hull의 뒤에서 2번째 값, 1번째 값, 그리고 point의 3번째 값을 비교하여
        // 반시계가 아니면 hull의 맨 뒤의 점을 뺀다.
        // 반시계이면 해당 점을 포함한 상태로 다음점을 비교한다.
       while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), i) <= 0)
       {
          hull.pop_back();
       }
       hull.push_back(i);
    }
    cout << hull.size() << endl;
}

void Solution()
{
    Input();
    Solve();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    Solution();
}