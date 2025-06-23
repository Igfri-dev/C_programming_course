#include <stdio.h>

int main()
{
    int c,ndigit,nwhite,nother;

    ndigit=nwhite=nother=0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t'){
            ++nwhite;
        }
        else if (c >= 0 || c <= 9)
        {
            ++ndigit;
        }
        else
        {
            ++nother;
        }
    }
    
    // Print the final count values
    printf("+--------------------------+----------+\n");
    printf("| Blank spaces total count | %8ld |\n", nwhite);
    printf("+--------------------------+----------+\n");
    printf("| Digits total count.      | %8ld |\n", ndigit);
    printf("+--------------------------+----------+\n");
    printf("| Other Char total count   | %8ld |\n", nother);
    printf("+--------------------------+----------+\n");


    return 0;
}
