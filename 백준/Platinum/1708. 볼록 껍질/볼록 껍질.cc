#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
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

ll ccw(Point pt1, Point pt2, Point pt3)
{
   ll ret = pt1.x*pt2.y + pt2.x*pt3.y + pt3.x*pt1.y;
   ret -= (pt2.x*pt1.y + pt3.x*pt2.y + pt1.x*pt3.y);
   return ret;
}
ll dist(Point pt1, Point pt2)
{
   ll dx = pt2.x - pt1.x;
   ll dy = pt2.y - pt1.y;
   return dx * dx + dy * dy;
}

int main()
{
    int N;
    cin >> N;
    point.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> point[i].x >> point[i].y;
    }
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