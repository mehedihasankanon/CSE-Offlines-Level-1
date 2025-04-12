/*
4:
0
10
010
1010

5:
1
01
101
0101
10101

6:
0
10
010
1010
01010
101010


*/


#include <stdio.h>

int main ()
{
    int n; scanf("%d",&n);

    int prev = n%2;
    for(int i = 1; i <= n; i++)
    {
        // if the first digit of the previous line is 0, 1 is added
        // if 1, 0 is added in the front 
        if(prev)
        {
            for(int j = 1; j <= i; j++) printf("%d", j%2);
            prev = 1-prev;
        }
        else
        {
            for(int j = 0; j < i; j++) printf("%d", j%2);
            prev = 1-prev;            
        }
        printf("\n");
    }

    return 0;
}