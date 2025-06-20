/*
 * Bitwise Guessing Game - Ultra Compact Version (Single 64-bit Variable)
 *
 * All game data is stored in a single 64-bit integer:
 *  - Bits 0–51: 2 bits per letter (00 = not guessed, 01 = computer, 10 = user)
 *  - Bits 52–55: player lives (0–15)
 *  - Bit 56: user won
 *  - Bit 57: computer won
 *  - Bits 58–63: reserved for future use
 *
 * Memory used: 8 bytes total
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

#define MIN_CHAR 'a'
#define MAX_CHAR 'z'
#define LETTERS 26

#define COLOR_U "\033[32mU\033[0m"
#define COLOR_C "\033[31mC\033[0m"

uint64_t game_state = 0;

// Access macros
#define SET_LETTER(ch, val) \
    game_state = (game_state & ~(0b11ULL << (((ch) - MIN_CHAR) * 2))) | ((uint64_t)(val) << (((ch) - MIN_CHAR) * 2))

#define GET_LETTER(ch) \
    ((game_state >> (((ch) - MIN_CHAR) * 2)) & 0b11)

#define SET_LIVES(val) \
    game_state = (game_state & ~(0xFULL << 52)) | ((uint64_t)((val) & 0xF) << 52)

#define GET_LIVES() \
    ((game_state >> 52) & 0xF)

#define SET_USER_WON() (game_state |= (1ULL << 56))
#define SET_COMP_WON() (game_state |= (1ULL << 57))
#define USER_WON() ((game_state >> 56) & 1)
#define COMP_WON() ((game_state >> 57) & 1)

void print_board() {
    printf("\033[H\033[J");
    printf("+---+---+---+---+\n");
    for (int i = 0; i < LETTERS; i++) {
        char ch = MIN_CHAR + i;
        uint8_t state = GET_LETTER(ch);
        printf("| ");
        if (state == 2) printf(COLOR_U);
        else if (state == 1) printf(COLOR_C);
        else printf("%c", ch);
        printf(" ");
        if ((i + 1) % 4 == 0) printf("|\n+---+---+---+---+\n");
    }
    if (LETTERS % 4 != 0) {
        for (int i = LETTERS % 4; i < 4; i++) printf("|   ");
        printf("|\n+---+---+---+---+\n");
    }
    printf("Lives: %" PRIu64 "\n", GET_LIVES());
}

int main() {
    srand(time(NULL));
    uint8_t target = MIN_CHAR + (rand() % LETTERS);
    int8_t input;
    uint8_t comp_guess;

    SET_LIVES(10);

    while (!USER_WON() && !COMP_WON() && GET_LIVES() > 0) {
        print_board();

        printf("(Ctrl+D on Unix/Linux or Ctrl+Z on Windows)");
        printf("Enter a letter: ");
        while (1) {
            input = getchar();
            if (input == EOF) {
                SET_COMP_WON();
                goto END;
            }
            if (input == '\n') continue;
            if (input < MIN_CHAR || input > MAX_CHAR) {
                printf("Invalid input. Try again: ");
                while ((getchar()) != '\n');
                continue;
            }
            if (GET_LETTER(input) != 0) {
                printf("Letter already guessed. Try another: ");
                while ((getchar()) != '\n');
                continue;
            }
            break;
        }

        SET_LETTER(input, 2);
        if (input == target) {
            SET_USER_WON();
            break;
        } else {
            SET_LIVES(GET_LIVES() - 1);
        }

        do {
            comp_guess = MIN_CHAR + (rand() % LETTERS);
        } while (GET_LETTER(comp_guess) != 0);

        SET_LETTER(comp_guess, 1);
        if (comp_guess == target) {
            SET_COMP_WON();
            break;
        }
    }

END:
    print_board();
    printf("The letter was: %c\n", target);
    if (USER_WON()) printf("YOU WIN!\n");
    else printf("COMPUTER WINS!\n");
    return 0;
}
