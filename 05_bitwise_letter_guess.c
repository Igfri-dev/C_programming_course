/*
select a random char (lowercase)(ASCII [97 - 122][a-z])(rand())
number of oportunities (10)
correct guesses (0)
get the user guess
compare the user guess with the actual char
    if the user insert a EOF he loses the match
    if the user guess is wrong
        reduce oportunities by 1
    if the user guess is correct
        user wins the match and program ends
the computer get a random char for his guess (better if it can't repeat)
    if the computer guess is wrong
        nothing happens (computer is inmortal)
    if the computer guess is correct
        computer wins the match and program ends
if no one guesses correctly the char repeat until the user or the computer wins or the users ends with no oportunities



For dysplay purposes, the game board will be printed in a 4x7 grid format.
where each cell represents a letter from 'a' to 'z'.
and when a letter is guessed, it will be replaced with either 'U' for user or 'C' for computer.

+---+---+---+---+
| a | b | c | d |
+---+---+---+---+
| e | f | g | h |
+---+---+---+---+
| i | j | k | l |
+---+---+---+---+
| m | n | o | p |
+---+---+---+---+
| q | r | s | t |
+---+---+---+---+
| u | v | w | x |
+---+---+---+---+
| y | z |   |   |
+---+---+---+---+


*/
#include <stdio.h>      // For input/output functions
#include <stdint.h>     // For fixed-size integer types
#include <stdlib.h>     // For rand() and srand()
#include <time.h>       // For seeding rand() with time

// ASCII range for lowercase letters
#define MIN_CHAR 97
#define MAX_CHAR 122
#define MAX_LIVES 10

// Bit flags to signal win states
#define USER_WON 0b00010000
#define COMPUTER_WON 0b01000000

// ANSI escape sequence to clear the screen
const char *CLEAR_SCREEN = "\033[H\033[J";

// Print the game board in a 4x7 grid
void print_table(uint32_t played_letters, uint32_t ownership_flags, uint8_t lives)
{
    printf("%s", CLEAR_SCREEN);  // Clear screen for fresh output
    printf("Guessed Letters (U = User, C = Computer)\n");
    printf("+---+---+---+---+\n");

    uint8_t col = 0;  // Track current column position
    for (uint8_t c = MIN_CHAR; c <= MAX_CHAR; c++)
    {
        uint32_t bit = 1U << (c - MIN_CHAR);  // Create bitmask for current letter, in this operation a bit is moved to the left by (c - MIN_CHAR) positions
        uint8_t display = c;  // Default to showing the letter

        if (played_letters & bit)  // If letter was guessed
        {
            if (ownership_flags & bit)  // User guessed this letter
            {
                printf("| \033[32mU\033[0m ");  // Green U
            }
            else  // Computer guessed this letter
            {
                printf("| \033[31mC\033[0m ");  // Red C
            }
        }
        else  // Not guessed yet
        {
            printf("| %c ", display);  // Show letter
        }

        col++;
        if (col == 4)
        {
            printf("|\n+---+---+---+---+\n");  // End of row
            col = 0;  // Reset column count
        }
    }

    // Fill empty columns in the last row if necessary
    if (col != 0)
    {
        for (int i = col; i < 4; i++)
        {
            printf("|   ");
        }
        printf("|\n+---+---+---+---+\n");
    }

    printf("Lives remaining: %d\n", lives);  // Show remaining lives
}

int main()
{
    uint8_t game_data = 0b00001010; // Bit-packed game state: bits [0-3] for lives, bit 4 USER_WON, bit 6 COMPUTER_WON
    uint8_t rand_numb;              // The target letter to guess
    uint8_t user_input, computer_guess;  // Variables to hold guesses
    uint32_t played_letters = 0;         // Track which letters have been guessed
    uint32_t ownership_flags = 0;        // Track who guessed each letter (1 = user, 0 = computer)
    uint32_t letter_bit;                 // Temporary bitmask for individual guesses

    srand(time(NULL));                   // Seed RNG with current time
    rand_numb = MIN_CHAR + (rand() % 26); // Choose a random target letter between 'a' and 'z'

    // Game loop continues until win or lives are 0
    while ((game_data & (USER_WON | COMPUTER_WON)) == 0 && (game_data & 0b00001111) > 0)
    {
        print_table(played_letters, ownership_flags, game_data & 0b00001111);  // Display game state
        printf("Computer guessed: %c\n", computer_guess);  // Show last computer guess

        // USER TURN
        printf("Enter your guess (a-z) or Ctrl+D to quit: ");
        while (1)
        {
            user_input = getchar();  // Read user input

            if (user_input == EOF)  // If Ctrl+D or input ends
            {
                game_data |= COMPUTER_WON;  // Computer wins by default
                print_table(played_letters, ownership_flags, game_data & 0b00001111);
                printf("THE LETTER WAS: %c\n", rand_numb);
                printf("You gave up. COMPUTER WINS!!\n");
                return 0;
            }

            if (user_input == '\n') continue;  // Ignore newlines

            if (user_input < MIN_CHAR || user_input > MAX_CHAR)  // Out of range
            {
                printf("Invalid input. Try again: ");
                while ((getchar()) != '\n');  // Clear the input buffer
                continue;
            }

            letter_bit = 1U << (user_input - MIN_CHAR);  // Generate bitmask for input, in this operation a bit is moved to the left by (user_input - MIN_CHAR) positions

            if (played_letters & letter_bit)  // Already guessed
            {
                printf("This letter is already played.\nEnter a valid guess: ");
                while ((getchar()) != '\n');
                continue;
            }

            break;  // Valid input
        }

        // Record user guess
        played_letters |= letter_bit;       // Mark as played
        ownership_flags |= letter_bit;      // Mark ownership as user

        if (user_input == rand_numb)  // Correct guess
        {
            game_data |= USER_WON;
        }
        else  // Wrong guess
        {
            printf("Try again!\n");
            game_data = (game_data & 0b11110000) | ((game_data & 0b00001111) - 1); // Decrement lives
        }

        // COMPUTER TURN
        do
        {
            computer_guess = MIN_CHAR + (rand() % 26);  // Pick a random letter
            letter_bit = 1U << (computer_guess - MIN_CHAR);  // Convert to bitmask, in this operation a bit is moved to the left by (computer_guess - MIN_CHAR) positions
        } while (played_letters & letter_bit);  // Ensure it's not already guessed

        played_letters |= letter_bit;     // Mark letter as guessed
        ownership_flags &= ~letter_bit;   // Mark ownership as computer

        if (computer_guess == rand_numb)  // Computer guessed correctly
        {
            game_data |= COMPUTER_WON;
        }

        // If someone won, show results
        if (game_data & USER_WON)
        {
            print_table(played_letters, ownership_flags, game_data & 0b00001111);
            printf("THE LETTER WAS: %c\n", rand_numb);
            printf("YOU WIN!!\n");
            break;
        }

        if (game_data & COMPUTER_WON)
        {
            print_table(played_letters, ownership_flags, game_data & 0b00001111);
            printf("THE LETTER WAS: %c\n", rand_numb);
            printf("COMPUTER WINS!!\n");
            break;
        }
    }

    // If user ran out of lives and no one has won
    if ((game_data & 0b00001111) == 0 && !(game_data & (USER_WON | COMPUTER_WON)))
    {
        print_table(played_letters, ownership_flags, 0);
        printf("THE LETTER WAS: %c\n", rand_numb);
        printf("Out of lives!\nCOMPUTER WINS!!\n");
    }

    return 0;
}

/*

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +----+
| 0 | 1 | 1 | 0 | 0 | 0 | 0 | 1 |    | 97 |
+---+---+---+---+---+---+---+---+    +----+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +-----+
| 0 | 1 | 1 | 1 | 1 | 0 | 1 | 0 |    | 122 |
+---+---+---+---+---+---+---+---+    +-----+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +----+
| 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 |    | 10 |
+---+---+---+---+---+---+---+---+    +----+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |    | 9 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |    | 8 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 |    | 7 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 |    | 6 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 |    | 5 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |    | 4 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |    | 3 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |    | 2 |
+---+---+---+---+---+---+---+---+    +---+

|128|64 |32 |16 | 8 | 4 | 2 | 1 |
+---+---+---+---+---+---+---+---+    +---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |    | 1 |
+---+---+---+---+---+---+---+---+    +---+


so lives would be

 10: 1010
 9 : 1001
 8 : 1000
 7 : 0111
 6 : 0110
 5 : 0101
 4 : 0100
 3 : 0011
 2 : 0010
 1 : 0001
 0 : 0000

*/
