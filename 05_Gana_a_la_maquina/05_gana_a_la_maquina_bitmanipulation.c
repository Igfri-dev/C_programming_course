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


+------------+------------+
|    User    |  Computer  |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+
|            |            |
+------------+------------+


NOT COMPLETED


*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MIN_CHAR 97
#define MAX_CHAR 122
#define MAX_LIVES 10

#define USER_WON 0b00010000
#define COMPUTER_WON 0b01000000

const char *CLEAR_SCREEN = "\033[H\033[J";

void print_table(uint32_t played_letters, uint32_t ownership_flags, uint8_t lives) {
    printf("%s", CLEAR_SCREEN);
    printf("Guessed Letters (U = User, C = Computer)\n");
    printf("+---+---+---+---+\n");

    int col = 0;
    for (char c = MIN_CHAR; c <= MAX_CHAR; c++) {
        uint32_t bit = 1U << (c - MIN_CHAR);
        char display = c;

        if (played_letters & bit) {
            if (ownership_flags & bit) {
                // Usuario → verde
                printf("| \033[32mU\033[0m ");
            } else {
                // Computadora → rojo
                printf("| \033[31mC\033[0m ");
            }
        } else {
            // No ha sido jugado
            printf("| %c ", display);
        }

        col++;
        if (col == 4) {
            printf("|\n+---+---+---+---+\n");
            col = 0;
        }
    }

    if (col != 0) {
        for (int i = col; i < 4; i++) {
            printf("|   ");
        }
        printf("|\n+---+---+---+---+\n");
    }

    printf("Lives remaining: %d\n", lives);
}


int main() {
    uint8_t game_data = 0b00001010; // [64:pc win][32][16:user win][0-15: vidas]
    uint8_t rand_numb;
    uint8_t user_input, computer_guess;
    uint32_t played_letters = 0;
    uint32_t ownership_flags = 0;
    uint32_t letter_bit;

    srand(time(NULL));
    rand_numb = MIN_CHAR + (rand() % 26);

    while ((game_data & (USER_WON | COMPUTER_WON)) == 0 && (game_data & 0b00001111) > 0) {
        print_table(played_letters, ownership_flags, game_data & 0b00001111);

        // Turno del usuario
        printf("Enter your guess (a-z) or Ctrl+D to quit: ");
        while (1) {
            user_input = getchar();

            if (user_input == EOF) {
                game_data |= COMPUTER_WON;
                print_table(played_letters, ownership_flags, game_data & 0b00001111);
                printf("You gave up. COMPUTER WINS!!\n");
                return 0;
            }

            if (user_input == '\n') continue;

            if (user_input < MIN_CHAR || user_input > MAX_CHAR) {
                printf("Invalid input. Try again: ");
                while ((getchar()) != '\n');
                continue;
            }

            letter_bit = 1U << (user_input - MIN_CHAR);

            if (played_letters & letter_bit) {
                printf("This letter is already played.\nEnter a valid guess: ");
                while ((getchar()) != '\n');
                continue;
            }

            break;
        }

        // Registrar jugada del usuario
        played_letters |= letter_bit;
        ownership_flags |= letter_bit;

        if (user_input == rand_numb) {
            game_data |= USER_WON;
        } else {
            printf("Try again!\n");
            game_data = (game_data & 0b11110000) | ((game_data & 0b00001111) - 1);
        }

        // Turno de la computadora
        do {
            computer_guess = MIN_CHAR + (rand() % 26);
            letter_bit = 1U << (computer_guess - MIN_CHAR);
        } while (played_letters & letter_bit);

        played_letters |= letter_bit;
        ownership_flags &= ~letter_bit;

        printf("Computer guessed: %c\n", computer_guess);

        if (computer_guess == rand_numb) {
            game_data |= COMPUTER_WON;
        }/* else {
            printf("Computer failed.\n");
        }*/

        // Mostrar tabla después de ambos turnos si alguien ganó
        if (game_data & USER_WON) {
            print_table(played_letters, ownership_flags, game_data & 0b00001111);
            printf("YOU WIN!!\n");
            break;
        }

        if (game_data & COMPUTER_WON) {
            print_table(played_letters, ownership_flags, game_data & 0b00001111);
            printf("COMPUTER WINS!!\n");
            break;
        }
    }

    if ((game_data & 0b00001111) == 0 && !(game_data & (USER_WON | COMPUTER_WON))) {
        print_table(played_letters, ownership_flags, 0);
        printf("Out of lives! COMPUTER WINS!!\n");
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


so liveS would be

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
