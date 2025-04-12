/*
Implement a statistical analysis tool that allows the user to enter multiple numbers and then
perform various statistical operations on the data.
Operations:
1. Find Maximum and Minimum Numbers
2. Calculate the Average
3. Count Even and Odd Numbers
4. Sum of All Numbers
Detailed Instructions:
● First, allow the user to enter multiple numbers. You can ask the user how many
numbers they wish to input, and then use a loop to collect those numbers.
● After collecting the numbers, display maximum number, minimum number, sum of all
numbers, average, even number count and odd number count.
Example Scenario:
How many numbers do you want to enter? 5
Enter 5 numbers: 10 15 25 30 40
Minimum Number: 10
Maximum Number:40
Sum of all Numbers: 120
Average: 24
Even Number Count: 3
Odd Number Count: 2
*/


#include <stdio.h>
#include <limits.h>

int main ()
{
    printf("How many numbers do you want to enter? "); 
    int n; 
    scanf("%d", &n);

    int max = INT_MIN, min = INT_MAX, sum = 0, even = 0, odd = 0;


    printf("Enter %d numbers: ",n);
    for(int i = 0; i < n; i++)
    {
        int x; scanf("%d",&x);
        
        if(x > max) max = x;
        if(x < min) min = x;
        
        sum += x;
        
        if(x%2) odd++;
        else even++;
    }

    printf("Minimum Number: %d\n",min);
    printf("Maximum Number: %d\n",max);
    printf("Sum of all Numbers: %d\n",sum);
    printf("Average: %0.2f\n", (float)sum/n);
    printf("Even Number Count: %d\n",even);
    printf("Odd Number Count: %d\n",odd);
}