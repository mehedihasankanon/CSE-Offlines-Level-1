/*
    Take a string, s, as input and reverse the order of the words. A 
    word is defined as a sequence of non-space characters. The words in s will be 
    separated by at least one space. If there are any extra spaces remove this 
    in the output string.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void reverseWords(char *a, char *t);


int main ()
{
    char *a = (char *)calloc(1000, sizeof(char)); 
    char *t = (char *)calloc(1000, sizeof(char));


    // scanf("%s",a);
    fgets(a,1000,stdin);
    *(a + strlen(a) - 1) = '\0';

    reverseWords(a,t);

    printf("%s\n",t);

    free(a);
    free(t);

    return 0;
}

void reverseWords(char *a, char *t)
{
    int s1 = strlen(a);

    bool wordstarted = false;

    int j = 0, start, end;
    for(int i = s1 - 1; i >= 0; i--)
    {
        // printf("i %d\n",i);
        if(!isspace(*(a+i)))
        {
            if(!wordstarted)
            {
                wordstarted = true;
                start = i;
            }
            
            else if(i == 0) // reached the end of string
            {
                if(wordstarted)
                {
                    wordstarted = false;
                    end = 0;
                    // printf("end %d\n",end);

                    for(int k = end; k <= start; k++)
                    {
                        // t[j] = a[k];
                        *(t + j) = *(a + k);
                        // printf("cp %c\n",t[j]);
                        j++; 
                    }
                    // t[j] = ' ';
                    *(t + j) = ' ';
                    j++;
                }
                else continue;
            }
        }
        else
        {
            if(wordstarted)
            {
                wordstarted = false;
                end = i + 1;
                if(i == 0) end = 0;
                // printf("end %d\n",end);

                for(int k = end; k <= start; k++)
                {
                    // t[j] = a[k];
                    *(t + j) = *(a + k);
                    // printf("cp %c\n",t[j]);
                    j++; 
                }
                // t[j] = ' ';
                *(t + j) = ' ';
                j++;
            }
            else continue;
        }

    }

    return;
}
