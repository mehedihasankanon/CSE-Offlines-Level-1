/*
    Find the mode of some given numbers. The mode of some numbers is/are the ones 
    which appear the highest number of times. Take an integer n as input. Next take n 
    integer elements as input, whose mode you need to find. All the inputs will have values 
    in [0, 10000] range
*/



#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *freq = (int *)calloc(10010,sizeof(int)); 
    if(freq == NULL) return -1;


    int n; scanf("%d",&n);
    int max = -1, max_num = 0;
    for(int i = 0; i < n; i++)
    {
        int x; scanf("%d",&x);
        // freq[x]++;
        (*(freq + x))++;
        if(x > max_num) max_num = x;
        if(*(freq + x) > max) max = *(freq + x);
    }

    for(int i = 0; i <= max_num; i++)
    {
        if(*(freq + i) == max) printf("%d ",i);
    }
    printf("\n");

    free(freq);
    return 0;


}