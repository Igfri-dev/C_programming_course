#include <stdio.h>

int main()
{
    long nc, nl, nt, nr; // Declare variables for character count, line count, tab count and return count
    nc = 0;              // Initialize character count to zero
    nl = 0;              // Initialize line count to zero
    nt = 0;              // Initialize tab count to zero
    nr = 0;              // Initialize return count to zero

    int c; // Declare a character variable, c is a integer type to handle EOF properly


    char *clear_screen = "\033[H\033[J"; // ANSI escape code to clear the screen
    printf("%s", clear_screen); // Clear the screen at the start


    // Ask the user to enter characters
    printf("Enter characters (Ctrl+D to end on Unix/Linux or Ctrl+Z on Windows):\n");
    printf("characters start count: %ld\n", nc);
    printf("lines start count: %ld\n", nl);
    printf("tabs start count: %ld\n", nt);
    printf("returns start count: %ld\n", nr);

    // Read characters until end of file
    while ((c = getchar()) != EOF)
    {
        // Check if the character is a newline
        if (c == '\n')
        {
            // Increment line count for each newline character
            ++nl;
        }
        else if (c == '\t')
        {
            // Increment tab count for each tab character
            ++nt;
        }
        else if (c == '\r')
        {
            // Increment return count for each return character
            ++nr;
        }
        else
        {
            // Increment character count for each character read
            ++nc;
        }

        printf("%s", clear_screen); // Clear the screen after each character input

        printf("Enter characters (Ctrl+D to end on Unix/Linux or Ctrl+Z on Windows):\n");
        printf("characters start count: %ld\n", nc);
        printf("lines start count: %ld\n", nl);
        printf("tabs start count: %ld\n", nt);
        printf("returns start count: %ld\n", nr);
    }

    printf("\033[H\033[J"); // Clears the screen and moves the cursor to the top-left corner
    printf("characters start count: %ld\n", nc);
    printf("lines start count: %ld\n", nl);
    printf("tabs start count: %ld\n", nt);
    printf("returns start count: %ld\n", nr);

    return 0;
}