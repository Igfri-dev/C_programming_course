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
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

#define MIN_CHAR 97
#define MAX_CHAR 122
#define MAX_LIVES 10

#define ALREADY_PLAYED 0b00100000
#define NOT_PLAYED 0b00000000

#define USER_WON 0b00010000
#define COMPUTER_WON 0b01000000



void print_table(uint8_t *user_selections, uint8_t *computer_selections, uint8_t lives) {
    printf("%s", CLEAR_SCREEN);
    printf("+------------+------------+\n");
    printf("|    User    |  Computer  |\n");
    printf("+------------+------------+\n");
    for (int i = 0; i < MAX_LIVES; i++) {
        printf("|     %c      |     %c      |\n",
               user_selections[i] ? user_selections[i] : ' ',
               computer_selections[i] ? computer_selections[i] : ' ');
        printf("+------------+------------+\n");
    }
    printf("Lives remaining: %d\n", lives);
}



const char *CLEAR_SCREEN = "\033[H\033[J";



int main()
{

    // 00 computerScore 00 userScore 1010 user lives
    uint8_t game_data = 0b00001010; //(0b00001010 = 10) 8 bits value where first two bits store a bit flag to signail if the machine or the user won (0 = still playing; 1 = player won) and the last 4 bits are to store the tries of the user (10 to 0)(max posible lifes with this aproach are 15)
    uint8_t rand_numb;
    uint8_t user_selections[10] = {0}; // Initialize to 0
    uint8_t computer_selections[10] = {0}; // Initialize to 0
    uint8_t user_input, computer_guess;;

    uint8_t round = 0; //KEEP TRACK ON THIS HANS

    srand(time(NULL)); // Seed the random number generator
    rand_numb = MIN_CHAR + (rand() % 26); // Random number between 97 and 122

    
        do
        {

            print_table(user_selections, computer_selections, game_data & 0b00001111);

            // User guess
            printf("Enter your guess (a-z) or Ctrl+D to quit: ");

            do
            {
                
                
                user_input = getchar();

                while (getchar() != '\n'); // Clear input buffer is trolling
                if (user_input == EOF) {
                    game_data |= COMPUTER_WON;
                    print_table(user_selections, computer_selections, game_data & 0b00001111);
                    printf("You gave up. COMPUTER WINS!!\n");
                    break;
                }

                game_data &= ~ALREADY_PLAYED; // Clear played flag

                for(uint8_t i = 0; i < (10 - (game_data & 0b00001111)); i++){
                    if (user_selections[i] == user_input)
                    {
                        game_data |= ALREADY_PLAYED; // 00 10 played letter flag  
                        printf("This letter is already played\nEnter a valid guess:");
                        break;
                    }
                }

            } while ((user_input < 'a' || user_input > 'z') || ((game_data & 0b00100000) == 32));



            
            if (user_input != rand_numb)
            {       
                user_selections[(10 - (game_data & 0b00001111))] = user_input;
                printf("Try again!\n");
                game_data = (game_data & 0b11110000) | ((game_data & 0b00001111) - 1);
            }
            else
            {
                game_data = game_data | 0b00010000;
                printf("YOU WIN!!\n");
                break;
            }


        } while ((game_data & 0b11110000) == 0 && (game_data & 0b00001111)); // (game_data & 0b11110000) == 0 extract the first 4 bits and compare with 0 (no one won yet) and (game_data & 0b00001111) extract the last 4 bits, I didn't compare it with 0 ("value>0") because I read that every number above 0 is readed as true; both of this ways in combination may reduce some CPU cycles depending in the compilator and CPU arquitecture (really nothing big but is something)
    
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