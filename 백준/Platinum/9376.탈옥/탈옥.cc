#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
#include<string>
using namespace std;

char prison[102][102];
int min_door[3][102][102];
int height, width, test_num;
pair<int,int> prisoner[2];
int change_pos[4][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};

struct VertexInfo{
  int r;
  int c;
  int cost;

  bool operator<(const VertexInfo& x)const{
    return cost > x.cost;
  }
};

void Dijkstra(int person_idx, int start_r, int start_c){
  priority_queue<VertexInfo> pq;
  pq.push({start_r, start_c, 0});
  min_door[person_idx][start_r][start_c] = 0;

  int r,c,cost,next_r, next_c, next_cost;
  char next_state;
  while(!pq.empty()){
    r = pq.top().r;
    c = pq.top().c;
    cost = pq.top().cost;
    pq.pop();

    if(min_door[person_idx][r][c] < cost)
      continue;

    for(int i=0; i<4;++i){
      next_r = r+ change_pos[i][0];
      next_c = c+ change_pos[i][1];

      if(next_r < 0 || height+1 < next_r  || next_c < 0 || width+1 < next_c)  //범위 확인
        continue;

      next_state = prison[next_r][next_c];
      next_cost = cost;

      if(next_state == '*') //벽이라면 그냥 넘어감
        continue;
      else if(next_state == '#')  //문이라면 cost를 증가
        ++next_cost;

      if(next_cost < min_door[person_idx][next_r][next_c]){
        pq.push({next_r, next_c, next_cost});
        min_door[person_idx][next_r][next_c] = next_cost;
      }
    } //for end
  } //while end

}

void Solution()
{
    while(test_num--){
        
    cin>>height>>width;
    
    int order = 0;
    string st;
    for(int r= 1; r<=height ; ++r){
      cin>>st;
      st = '.' + st + '.';
      for(int c=0; c<=width+1 ; ++c){
        prison[r][c] = st[c];
        if(prison[r][c] == '$')
          prisoner[order++] = {r,c};
      }
    }

    for(int c=0; c<=width+1 ; ++c){
      prison[0][c] = '.';
      prison[height+1][c] ='.';
    }

    memset(min_door, 0xf, sizeof(min_door));  //0xf로 초기화 해주자.
    Dijkstra(0, 0 , 0);
    Dijkstra(1, prisoner[0].first , prisoner[0].second);
    Dijkstra(2, prisoner[1].first , prisoner[1].second);

    int min_open_num = INT32_MAX;
    int opened_doors;
    for(int r= 0; r<=height+1 ; ++r){
      for(int c=0; c<=width+1 ; ++c){
        if(prison[r][c] == '*')
          continue;

        opened_doors = min_door[0][r][c] +min_door[1][r][c] + min_door[2][r][c];
        if(prison[r][c] == '#') //해당 좌표가 문인 경우
          opened_doors -=2;
        min_open_num = min(opened_doors, min_open_num);
      }
    }

    cout<<min_open_num<<endl;
  }
}

void Input()
{
    cin >> test_num;
    
    for(int c=0; c<=width+1 ; ++c){
      prison[0][c] = '.';
      prison[height+1][c] ='.';
    }
}

void Solve()
{
    Input();
    Solution();
}

int main(){
  Solve();  
  return 0;
}