#include <stdio.h>

int main() {

    long nc;
    nc = 0; // Initialize character count to zero

    // Ask the user to enter characters
    printf("Enter characters (Ctrl+D to end on Unix/Linux or Ctrl+Z on Windows):\n");
    printf("characters start count: %ld\n",nc);

    while(getchar() != EOF) { // Read characters until end of file
        ++nc; // Increment character count for each character read
    }

    // Output the total number of characters readed
    printf("Total number of characters: %ld\n", nc);

    return 0;
}