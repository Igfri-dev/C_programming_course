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


Core Design & Logic:
 - Letters guessed are tracked using a single 32-bit integer (`played_letters`), where each 
   bit represents whether a letter has been played.
 - Ownership of guessed letters (user vs computer) is tracked using another 32-bit integer
   (`ownership_flags`), where a 1 means the user guessed it.
 - The overall game state, including remaining lives and win conditions, is stored in an 
   8-bit value (`game_data`), using lower 4 bits for lives and specific bits for win flags.
 - The user's input is read using `getchar()` and stored in a signed 8-bit variable 
   (`int8_t`) to correctly detect EOF (`-1`).
 - Bitwise operations are used to check, update, and mark letter guesses efficiently,
   replacing the need for arrays, reducing memory usage and improving CPU cache performance.

This implementation emphasizes performance, minimal memory footprint, and clear output formatting 
using ANSI escape sequences for screen control and colored output.

*/
#include <stdio.h>      // For input/output functions
#include <stdint.h>     // For fixed-size integer types
#include <stdlib.h>     // For rand() and srand()
#include <time.h>       // For seeding rand() with time

// ASCII range for lowercase letters
#define MIN_CHAR 97
#define MAX_CHAR 122

// Bit flags to signal win states
#define USER_WON 0b00010000
#define COMPUTER_WON 0b01000000

// ANSI escape sequence to clear the screen
const char *CLEAR_SCREEN = "\033[H\033[J";

const char *request;

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
    uint8_t computer_guess;         // Variables to hold guesses
    int8_t user_input;              //EOF returns -1 so it is needed a variable that can store a sign in it (the other way is to compare if the input is 255 but that normally equals to ÿ )
    uint32_t played_letters = 0;         // Track which letters have been guessed
    uint32_t ownership_flags = 0;        // Track who guessed each letter (1 = user, 0 = computer)
    uint32_t letter_bit;                 // Temporary bitmask for individual guesses

    srand(time(NULL));                   // Seed RNG with current time
    rand_numb = MIN_CHAR + (rand() % 26); // Choose a random target letter between 'a' and 'z'


    // Prompt the user to enter a character
    // Detect OS (operating system)
    #ifdef _WIN32
        request = "Enter your guess (a-z) (Ctrl+Z to end):\n";
    #elif __APPLE__
        request = "Enter your guess (a-z) (Ctrl+D to end):\n";
    #elif __linux__
        request = "Enter your guess (a-z) (Ctrl+D to end):\n";
    #else
        request = "Enter your guess (a-z) (Ctrl+D to end on Unix/Linux or Ctrl+Z on Windows):\n";
    #endif



    // Game loop continues until win or lives are 0
    while ((game_data & (USER_WON | COMPUTER_WON)) == 0 && (game_data & 0b00001111) > 0)
    {
        print_table(played_letters, ownership_flags, game_data & 0b00001111);  // Display game state
        printf("Computer guessed: %c\n", computer_guess);  // Show last computer guess

        // USER TURN
        printf("%s", request);
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
