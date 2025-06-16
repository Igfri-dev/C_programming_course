#include <stdio.h>

//NOT COMPLETED

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
    // Detectar el sistema operativo
    #ifdef _WIN32
        printf("Enter characters (Ctrl+Z to end):\n");
    #elif __APPLE__
        printf("Enter characters (Ctrl+D to end):\n");
    #elif __linux__
        printf("Enter characters (Ctrl+D to end):\n");
    #else
        printf("Enter characters (Ctrl+D to end on Unix/Linux or Ctrl+Z on Windows):\n");
    #endif


    // Print the starting count values
    printf("+--------------------------+----------+\n");
    printf("| Characters start count:  | %8ld |\n", nc);
    printf("+--------------------------+----------+\n");
    printf("| Lines start count:       | %8ld |\n", nl);
    printf("+--------------------------+----------+\n");
    printf("| Tabs start count:        | %8ld |\n", nt);
    printf("+--------------------------+----------+\n");
    printf("| Carriage returns count:  | %8ld |\n", nr);
    printf("+--------------------------+----------+\n");


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
    }

    printf("%s", clear_screen); // Clears the screen before the final program outputs

    // Print the output table
    printf("+--------------------------+----------+\n");
    printf("| Characters total count:  | %8ld |\n", nc);
    printf("+--------------------------+----------+\n");
    printf("| Lines total count:       | %8ld |\n", nl);
    printf("+--------------------------+----------+\n");
    printf("| Tabs total count:        | %8ld |\n", nt);
    printf("+--------------------------+----------+\n");
    printf("| Carriage returns count:  | %8ld |\n", nr);
    printf("+--------------------------+----------+\n");

    return 0;
}
