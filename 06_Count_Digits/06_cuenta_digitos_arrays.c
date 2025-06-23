#include <stdio.h>
#include <ctype.h>

void print_digit_table(int ndigit[10]) {
    int max_width = 0;

    for (int i = 0; i < 10; ++i) {
        int temp = ndigit[i];
        int width = 1;
        while (temp /= 10) ++width;
        if (width > max_width) max_width = width;
    }

    if (max_width < 3) max_width = 3;

    char barra[256];
    int pos = 0;
    pos += sprintf(barra + pos, "+");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < max_width + 2; ++j) {
            pos += sprintf(barra + pos, "-");
        }
        pos += sprintf(barra + pos, "+");
    }
    barra[pos] = '\0';

    printf("%s\n", barra);
    printf("|");
    for (int i = 0; i < 10; ++i) {
        printf(" %*d |", max_width, i);
    }
    printf("\n%s\n", barra);

    printf("|");
    for (int i = 0; i < 10; ++i) {
        printf(" %*d |", max_width, ndigit[i]);
    }
    printf("\n%s\n", barra);
}

int main()
{
    int ndigit[10] = {0};
    int c, total_digits, nwhite, nother;
    total_digits=nwhite=nother = 0;

    while ((c = getchar()) != EOF)
    {
        if (isspace(c)){
            ++nwhite;
        }
        else if (isdigit(c))
        {
            ++total_digits;
            ++ndigit[c - '0'];
        }
        else
        {
            ++nother;
        }
    }

    print_digit_table(ndigit);

    printf("+--------------------------+----------+\n");
    printf("| Blank spaces total count | %8d |\n", nwhite);
    printf("+--------------------------+----------+\n");
    printf("| Digits total count       | %8d |\n", total_digits);
    printf("+--------------------------+----------+\n");
    printf("| Other Char total count   | %8d |\n", nother);
    printf("+--------------------------+----------+\n");

    return 0;
}
