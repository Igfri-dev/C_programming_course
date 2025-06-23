#include <stdio.h>

#define MAX_LINE 1000

int my_getline(char line[], int lim){

    int c, i;

    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
    {
        line[i]=c;
    }
    if(c=='\n'){
        line[i]=c;
        ++i;
    }

    line[i]='\0';
    return i;
}

int main(){

    int len;
    char line[MAX_LINE];

    len=my_getline(line, MAX_LINE);
    printf("--%s-- numero de Caracteres: %d\n", line, len);

    return 0;
}