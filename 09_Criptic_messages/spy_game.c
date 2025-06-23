/*
Encryption by displacement in alphabet by a 'n'


1) Ask if the user wants to encrypt or decrypt a message (2 functions)
2) Ask the user what displacement wants (ask for n)
3) Ask the user for the message
4)show the output

*/

#include <stdio.h>  // For handle user inputs and program outputs
#include <stdlib.h> // For handlig memory and char to int conversions
#include <string.h> // For manipulating char* (strings)
#include <ctype.h>  // For validate if a char is a digit

char menu();

char *get_message(int *length);
int get_displacement();

char *encrypt(char *message, int message_length, int displacement);
char *decrypt(char *encrypted_message, int message_length, int displacement);

const char *CLEAR_SCREEN = "\033[H\033[J"; // Command to clear the terminal

int main()
{

    printf("%s", CLEAR_SCREEN);

    char *message;
    int length = 0;

    int displacement;

    char choice;
    while (1)
    {
        choice = menu();

        switch (choice)
        {
        case '1':
            printf("%s", CLEAR_SCREEN);
            printf("Input your message: ");
            message = get_message(&length);

            displacement = get_displacement();
            char *encrypted = encrypt(message, length, displacement);

            printf("\nEncrypted message: %s\n", encrypted);

            free(message);

            free(encrypted);

            message = NULL;
            encrypted = NULL;
            break;

        case '2':
            printf("%s", CLEAR_SCREEN);
            printf("Input your encrypted message: ");
            message = get_message(&length);

            displacement = get_displacement();
            char *decrypted = decrypt(message, length, displacement);

            printf("\nDecrypted message: %s\n", decrypted);

            free(message);

            free(decrypted);

            message = NULL; 
            decrypted = NULL;
            break;

        case '3':
            printf("Exiting program.\n");
            return 0;

        default:
            printf("%s", CLEAR_SCREEN);
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
    return 0;
}

char menu()
{
    printf("\n=== Secure Message Program ===\n");
    printf("1. Encrypt a Message\n");
    printf("2. Decrypt a Message\n");
    printf("3. Exit\n");
    printf("===========================\n");
    printf("Enter your choice: ");

    char choice = getchar();
    while (getchar() != '\n')
        ;

    return choice;
}

char *get_message(int *length)
{
    int size = 100;                              // Temporal size
    char *message = malloc(size * sizeof(char)); // Allocate memory for the message
    if (message == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    *length = 0; // Set the calculated length of the message to 0
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {                         // While the user doesn't press enter or inputs End of File
        message[*length] = c; // save the char of 'c' into message
        (*length)++;          // Add 1 to the calculated length of the message

        if (*length >= size)
        {                                                    // If the message reach the size of the array
            size *= 2;                                       // Double the size variable (n * 2)
            message = realloc(message, size * sizeof(char)); // Reallocate memory for the new size of the message array
            if (message == NULL)
            {
                printf("Memory reallocation failed\n");
                exit(1);
            }
        }
    }
    message[*length] = '\0'; // Ends the String
    return message;
}

int get_displacement()
{
    char buffer[100];           // Buffer to hold the user's input as a string
    int is_valid, displacement; // 'is_valid' is used to flag if the input is a valid number, 'displacement' will store the result

    while (1)
    {
        printf("\nInput the value of displacement: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            continue; // Check for a line in 'buffer'.

        // Eliminar el salto de línea
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character at the end of the input, if present and replace that wirh a '\0'

        is_valid = 1; // Assume the input is valid at first
        int i = 0;

        if (buffer[0] == '-' || buffer[0] == '+')
            i = 1; // If the first char is a - or + symbol skip it

        for (; buffer[i] != '\0'; i++)
        {
            if (!isdigit((unsigned char)buffer[i]))
            {
                is_valid = 0; // If the current character is not a digit, the input is invalid
                break;
            }
        }

        if (is_valid)
        {                                // If all characters (excluding optional sign) are digits:
            displacement = atoi(buffer); // Convert the validated string into an integer using 'atoi'
            return displacement;
        }
        else
        {
            printf("Invalid input. Please enter a valid number.\n");
        }
    }
}

char *encrypt(char *message, int message_length, int displacement)
{

    char *encrypted = malloc((message_length + 1) * sizeof(char)); // Allocate memory for de encrypted message

    if (encrypted == NULL)
    {
        printf("The memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < message_length; i++)
    {
        char c = message[i];

        if (c >= 'A' && c <= 'Z') // For uppercase chars
        {
            encrypted[i] = ((c - 'A' + displacement) % 26) + 'A';
        }
        else if (c >= 'a' && c <= 'z') // For lowercase chars
        {
            encrypted[i] = ((c - 'a' + displacement) % 26) + 'a';
        }
        else if (c >= '0' && c <= '9') // For numbers
        {
            encrypted[i] = ((c - '0' + displacement) % 10) + '0';
        }
        /*else if (c >= 32 && c <= 126) // For special characters as '?','!',etc.
        {
            encrypted[i] = ((c - 32 + displacement) % 95) + 32;
        }*/
        else
        {
            encrypted[i] = c; // Leave other characters unchanged as example chars with accentuation or special characters as '?','!',etc.
        }
    }

    encrypted[message_length] = '\0'; // Ends the string
    return encrypted;
}

char *decrypt(char *encrypted_message, int message_length, int displacement)
{
    char *decrypted = malloc((message_length + 1) * sizeof(char)); // Allocate memory for de decrypted message

    if (decrypted == NULL)
    {
        printf("Memory allocation failed for decryption\n");
        exit(1);
    }

    for (int i = 0; i < message_length; i++)
    {
        char c = encrypted_message[i];

        if (c >= 'A' && c <= 'Z') // For uppercase char
        {
            decrypted[i] = ((c - 'A' - displacement + 26) % 26) + 'A';
        }
        else if (c >= 'a' && c <= 'z') // For lowercase char
        {
            decrypted[i] = ((c - 'a' - displacement + 26) % 26) + 'a';
        }
        else if (c >= '0' && c <= '9') // for Numbers
        {
            decrypted[i] = ((c - '0' - displacement + 10) % 10) + '0';
        }
        /*else if (c >= 32 && c <= 126) // For special characters as '?','!',etc.
        {
            decrypted[i] = ((c - 32 - displacement + 95) % 95) + 32;
        }*/
        else
        {
            decrypted[i] = c; // Leave non-printable or extended chars as it is
        }
    }

    decrypted[message_length] = '\0'; // Ends the string
    return decrypted;
}