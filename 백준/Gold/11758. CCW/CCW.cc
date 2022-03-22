#include<stdio.h>


int x1, y1, x2, y2, x3, y3;
int result;

int outerProduct()
{
    return (x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y1 - x1*y3) / 2;
}

void Input()
{
    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
}

void Solution()
{
    result = outerProduct();
    
    if (result > 0)
        printf("1\n");
    else if (result < 0)
        printf("-1\n");
    else
        printf("0\n");
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
    Solve();
    
    return 0;    
}