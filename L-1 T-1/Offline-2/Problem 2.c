#include <stdio.h>

int main ()
{
    int n; scanf("%d",&n);
    int a[n]; 
    for(int i = 0; i < n; i++) scanf("%d",&a[i]);

    printf("Initial order: ");
    for(int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    int m; scanf("%d",&m);

    for(int i = 1; i <= m; i++)
    {
        int move; scanf("%d",&move);
        if(move > 0) for(int j = 0; j < move; j++)
        {
            // every element from index 1 to n-1 is moved  
            // right by 1 position after every iteration
            
            int n1 = a[n-1]; // handling the last element separately which moves to a[0]
            for(int k = n-1; k >= 1; k--) a[k] = a[k-1];
            a[0] = n1; 
        }
        else for(int j = 0; j < -move; j++)
        {
            // every element from index 1 to n-1 is moved  
            // left by 1 position after every iteration
            
            int n1 = a[0]; // handling the first element separately which moves to a[n-1]
            for(int k = 0; k < n-1; k++) a[k] = a[k+1]; 
            a[n-1] = n1;
        }

        printf("After instruction %d: ", i);
        for(int t = 0; t < n; t++) printf("%d ",a[t]);
        printf("\n");
    }

    int ans = 0;
    for(int i = 1; i < n; i++) if(a[i] > a[ans]) ans = i;
    printf("Winner: Child %d",ans+1);
}