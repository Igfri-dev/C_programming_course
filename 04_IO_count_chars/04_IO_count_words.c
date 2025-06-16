#include <stdio.h>
#include <stdint.h>

#define IN 0 // State: inside a word
#define OUT 1 // State: outside a word

int main()
{
    // Declare variables for character count, line count, tab count, return count and words count
    long nc, nl, nt, nr, nw, ns; 

    // Initialize all counters to zero
    nc=nl=nt=nr=nw=ns=0;

    int c; //Declare a character variable. It must be int to properly handle EOF.
    uint8_t state; // uint8_t for 'state' to minimize memory usage
    state = OUT; // Initial state is OUT, meaning we are not inside a word yet

    char *clear_screen = "\033[H\033[J"; // ANSI escape code to clear the screen
    printf("%s", clear_screen); // Clear the screen at the start


    // Prompt the user to enter characters
    // Detect OS (operating system)
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
    printf("| Words start count:       | %8ld |\n", nw);
    printf("+--------------------------+----------+\n");
    printf("| Characters start count:  | %8ld |\n", nc);
    printf("+--------------------------+----------+\n");
    printf("| Lines start count:       | %8ld |\n", nl);
    printf("+--------------------------+----------+\n");
    printf("| Tabs start count:        | %8ld |\n", nt);
    printf("+--------------------------+----------+\n");
    printf("| Spaces start count:      | %8ld |\n", ns);
    printf("+--------------------------+----------+\n");
    printf("| Carriage returns count:  | %8ld |\n", nr);
    printf("+--------------------------+----------+\n");

    // Read characters until end of file
    while ((c = getchar()) != EOF)
    {
        // Check if the char is a new line, tab, carriage return or space
        if (c == '\n' || c == '\t' || c == '\r' || c == ' ')
        {
            state = OUT; // We are now outside a word

            if (c == '\n') ++nl;        // Increment line count
            else if (c == '\t') ++nt;   // Increment tab count
            else if (c == '\r') ++nr;   // Increment carriage return count
            else if (c == ' ') ++ns;    // Increment space count
            
        }
        else
        {
            ++nc; // Increment character count
            if (state==OUT)
            {
                state=IN; // We are now inside a word
                ++nw; // Increment word count
            }
        
        }
    }

    printf("%s", clear_screen); // Clear the screen before showing the final output

    // Print the final count values
    printf("+--------------------------+----------+\n");
    printf("| Words total count:       | %8ld |\n", nw);
    printf("+--------------------------+----------+\n");
    printf("| Characters total count:  | %8ld |\n", nc);
    printf("+--------------------------+----------+\n");
    printf("| Lines total count:       | %8ld |\n", nl);
    printf("+--------------------------+----------+\n");
    printf("| Tabs total count:        | %8ld |\n", nt);
    printf("+--------------------------+----------+\n");
    printf("| Spaces total count:      | %8ld |\n", ns);
    printf("+--------------------------+----------+\n");
    printf("| Carriage returns count:  | %8ld |\n", nr);
    printf("+--------------------------+----------+\n");

    return 0;
}