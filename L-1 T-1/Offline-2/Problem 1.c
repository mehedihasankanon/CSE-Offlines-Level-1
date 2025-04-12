#include <stdio.h>

int main ()
{
    int n; scanf("%d",&n);
    int a1[n], a2[n], ans = 0;

    for(int i =0; i < n; i++) scanf("%d",&a1[i]);
    for(int i =0; i < n; i++) scanf("%d",&a2[i]);

    for(int curr_ind = 0; curr_ind < n-1; curr_ind++) // no need to check ind = n-1 bcz it doesnt form any pair
    {
        for(int i = curr_ind+1; i < n; i++)
        { 
            int curr_ind2, i2; // curr_ind2: index where a[curr_ind] is
                               // i2 : index where a[i] is
                               // if i2 > curr_ind2, then the two form a pair which also
                               // exists in array 1. hence ans increases by 1.

            for(int j = 0; j < n; j++)
            {
                // linear search on array 2 to find where a[curr_ind] and a[i] are
                if(a2[j]==a1[curr_ind]) curr_ind2 = j;
                if(a2[j]==a1[i]) i2 = j;
            }

            if(i2 > curr_ind2) ans++;

        }
    }

    printf("%d\n", ans);
    return 0;
    
}