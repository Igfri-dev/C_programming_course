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

#define CORRECT 1
#define INCORRECT 0
#define MIN_CHAR 97
#define MAX_CHAR 122
#define MAX_GUESSES 10

const char *CLEAR_SCREEN = "\033[H\033[J";

int main(){


    uint8_t lives = 10;
    uint8_t won = INCORRECT;
    uint8_t guessed_by_computer[MAX_GUESSES] = {0};
    //uint8_t user_guesses[MAX_GUESSES];


    srand(time(NULL));// for better randomness

    uint8_t target = rand() % (MAX_CHAR - MIN_CHAR +1) + 97;

    //printf("Random number: %d\n", target);
    //printf("Corresponding character: %c\n", target);

    while (lives > 0 && won == INCORRECT) {
        //printf("%s", CLEAR_SCREEN);
        printf("You have %d lives left.\n", lives);
        printf("Enter a lowercase letter [a-z]: ");

        int user_input = getchar();
        while (getchar() != '\n'); // Clear buffer

        if (user_input == EOF) {
            printf("\nYou gave up. Computer wins!\n");
            break;
        }

        if (user_input < MIN_CHAR || user_input > MAX_CHAR) {
            printf("Invalid input. Please enter a lowercase letter.\n");
            continue;
        }

        if (user_input == target) {
            printf("You guessed correctly! You win!\n");
            won = CORRECT;
            break;
        } else {
            printf("Wrong guess.\n");
            //user_guesses[MAX_GUESSES-lives] = user_input;
            lives--;
        }

        // Computer's turn
        uint8_t computer_guess;
        do {
            computer_guess = rand() % (MAX_CHAR - MIN_CHAR + 1) + MIN_CHAR;
        } while (guessed_by_computer[computer_guess - MIN_CHAR]);

        guessed_by_computer[computer_guess - MIN_CHAR] = 1;

        printf("Computer guesses: %c\n", computer_guess);

        if (computer_guess == target) {
            printf("Computer guessed correctly! Computer wins!\n");
            break;
        }

        printf("Press Enter to continue...\n");
        getchar(); // Wait for user to continue
    }

    if (lives == 0 && won == INCORRECT) {
        printf("You ran out of lives. Computer wins!\n");
    }


    return 0;
}
