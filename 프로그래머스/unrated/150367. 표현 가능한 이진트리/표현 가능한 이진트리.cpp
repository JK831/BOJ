#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Convert decimal to binary string
// Make binary string length to 2^n - 1 with 0 padding in front of string
// Check Binary-Tree with binary string from middle index of binary string
// If any node is 0 and have any childeren node, fail


using namespace std;

typedef long long ll;

int result;
string binaryString;

string ConvertToBinary(ll num) // 10진수를 2진수 문자열로 변환
{
    string temp = "";

    while(num > 0)
    {
        ll mod = num % 2;
        temp += ('0' + mod);
        num /= 2;
    }

    reverse(temp.begin(), temp.end());
    return temp;
}

void isFullBinaryTree(ll start, ll end, bool zeroExist) // 완전이진트리를 만들 수 있는지 체크
{
    
    ll mid = (start + end) / 2;
    
    if (zeroExist && binaryString[mid] == '1') // 부모 노드가 0인데 자식 노드가 1이라면
    {
        result = 0;
        return;
    }
    
    if (start < end)
    {
        isFullBinaryTree(start, mid - 1, binaryString[mid] == '0');
        isFullBinaryTree(mid + 1, end, binaryString[mid] == '0');
    }
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer(numbers.size());

    string strBinary = ""; // 2진수로 변환된 문자열에 0 패딩을 추가해주기 위한 문자열

    for ( int i = 0 ; i < numbers.size() ; ++i )
    {
        result = 1;
        binaryString = ConvertToBinary(numbers[i]);

        ll len = binaryString.size();
        
        unsigned long long powerOf2 = 1;

        while (powerOf2 - 1 < len) // 완전이진트리의 노드 갯수는 2^n -1 이므로 binaryString의 길이보다 크거나 같으면서 가장 작은 2^n 의 값 구한다.
            powerOf2 <<= 1;
        
        int paddingSize = powerOf2 - 1 - len; // 패딩의 길이 = 2^n -1 - 이진수 문자열의 길이
        
        while (paddingSize > 0) // 패딩 추가
        {
            strBinary += '0';
            --paddingSize;
        }
        
        strBinary += binaryString; // 패딩 뒤에 구해낸 이진 문자열을 붙이고
        binaryString = strBinary; // 해당 문자열을 binaryString에 대입 (Global variable로서 isFullBinaryTree 함수에서 체크된다.)

        len = binaryString.size(); // 패딩이 붙은 이진 문자열의 길이로 갱신

        isFullBinaryTree(0, len - 1, false);
        answer[i] = result;
        strBinary = ""; // 문자열 초기화
        binaryString = "";
    }

    return answer;
}