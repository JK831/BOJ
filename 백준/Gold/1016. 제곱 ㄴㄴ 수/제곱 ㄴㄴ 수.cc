#include<iostream>
#include<cmath>
 
using namespace std;
 
bool result[1000001] = {false};  //max - min 사이의 최대 갯수
long long num[1000001] = {0};    //제곱들 저장
 
int main(void){
    long long min;
    long long max;
 
    cin >> min >> max;
 
    long long sq_max = (long long)sqrt(max);    //범위 내 제곱값이 될 수 있는 가장 큰수
    long long cntNum =0;                        //제곱들의 개수
    for(long long i=2; i<=sq_max; i++) {        //제곱들 저장
        num[i] = i*i;
        cntNum++;
    }
 
    int count =0; // max와  min 사이에 제곱의 수로 나누어 떨어지는 수.
 
    for(int i=2; i<cntNum+2; i++){
 
        long long div_min = min;                 //div_min을 범위의 최소값 min으로 둔 후 
        if(div_min % num[i] != 0){               //div_min이 제곱수로 나누어 지지 않으면 
            div_min = (min/num[i] + 1) * num[i]; //최소값을 제곱근으로 나눈 몫에 +1 후 다시 곱해서 범위 안의 값으로 바꾼다.
        }
 
        
        for(long long tmp = div_min; tmp <=max; tmp += num[i]){ //num[i]로 나누어지는 div_min을 count 한다.
            if(!result[tmp-min]){
                result[tmp-min] = true;
                count++;
            }
        }
 
    }
    cout << max-min-count+1 ;
 
    return 0;
}