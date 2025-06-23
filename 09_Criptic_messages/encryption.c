#include <stdio.h>
#include <stdlib.h>

char menu();

char* encrypt(char* message, int message_length);
char* decrypt(char* encrypted_message, int message_length);

void handle_file_encryption();
void handle_file_decryption();

// ANSI escape sequence to clear the screen
const char *CLEAR_SCREEN = "\033[H\033[J";


int main()
{
    char choice;

    while (1) {
        
        printf("%s",CLEAR_SCREEN);
        
        choice = menu(); //Shows the main menu

        switch (choice) {
            case '1':
                printf("%s",CLEAR_SCREEN);
                handle_file_encryption();
                break;
            case '2':
                printf("%s",CLEAR_SCREEN);
                handle_file_decryption();
                break;
            case '3':
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

char menu(){
    printf("\n=== Secure Message Program ===\n");
    printf("1. Encrypt a file\n");
    printf("2. Decrypt a file\n");
    printf("3. Exit\n");
    printf("===========================\n");
    printf("Enter your choice: ");
    return getchar();
}


char* encrypt(char* message, int message_length){
    
    printf("\nEnter password for encryption (100 character max.): "); // Ask user for a password

    // Read the user password
    char password[100];
    int pass_length = 0, c;
    while ((c = getchar()) != '\n' && c != EOF && pass_length < 99) {
        password[pass_length++] = c;
    }
    password[pass_length] = '\0';

    char* encrypted = malloc((message_length + 1) * sizeof(char)); // Stores the encrypted message
    if (encrypted == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Encrypt the message caracters by using XOR between the message and the password 
     for (int j = 0; j < message_length; j++) { // Loop through each character of the original message
        encrypted[j] = message[j] ^ password[j % pass_length]; // Encrypt the current character using XOR with the corresponding character of the password and in case the message is longer than the password, wrap around using j % pass_length
    }
    encrypted[message_length] = '\0'; // Ends encrypted the message

    /*
    printf("\nEncrypted message (raw bytes):\n");
    for (int j = 0; j < message_length; j++) {
        // Show the output as hex to avoid problems with the terminal display
        printf("%02x ", (unsigned char)encrypted[j]);
    }
    */
    printf("\n");

    return encrypted; //return the message

}

char* decrypt(char* encrypted_message, int message_length) {

    printf("\nEnter password for decryption (must match the one used for encryption): ");

    // Read the user password
    char password[100];
    int pass_length = 0, c;
    while ((c = getchar()) != '\n' && c != EOF && pass_length < 99) {
        password[pass_length++] = c;
    }
    password[pass_length] = '\0';

    // Allocate memory for decrypted message
    char* decrypted = malloc((message_length + 1) * sizeof(char));
    if (decrypted == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Apply XOR decryption (same as encryption)
    for (int j = 0; j < message_length; j++) {
        decrypted[j] = encrypted_message[j] ^ password[j % pass_length];
    }
    decrypted[message_length] = '\0';


    // Show decrypted message
    //printf("\nDecrypted message:\n%s\n", decrypted);
    
    return decrypted;
}

void handle_file_encryption(){
    char filename[256]; // Stores the filename
    printf("\nEnter the filename to encrypt: ");
    scanf("%s", filename);
    getchar();

    FILE *file = fopen(filename, "rb"); // Open the file
    if (!file) {
        printf("Could not open file.\n");
        return;
    }

    fseek(file, 0, SEEK_END); // Go to the end of the file
    int length = ftell(file); // Get the size of the file (in bytes)
    rewind(file); // Return to the beginig of the file

    char *content = malloc(length + 1); // Allocate the memory needed for handling the content
    fread(content, 1, length, file); // Starts reading the content 1 byte at a time for "length" bytes in total from this "file"
    fclose(file); // Colse the file 
    content[length] = '\0'; // Set the end of the string

    char *encrypted = encrypt(content, length);

    char output_file[256]; // Store the output filename
    sprintf(output_file, "%s.enc", filename); // Format a string, stores that string into output_file, "%s.enc" uses the name of filename and appends the .enc
    FILE *outfile = fopen(output_file, "wb"); // Opens a new file in writting binary mode (w = writting; b = binary mode) 
    if (!outfile) {
        printf("Could not create output file.\n");
        free(content);
        free(encrypted);
        return;
    }

    fwrite(encrypted, 1, length, outfile); // Writes into outfile the content of encrypted 1 byte at the time for "length" bytes in total
    fclose(outfile); // Closes the file

    printf("\nEncrypted content saved to: %s\n", output_file);

    free(content); // Frees the space in memory
    free(encrypted); // Frees the space in memory
    content=encrypted=NULL; // Set to NULL the values stored in content and encrypted so nothing can be retrieve from it
}

void handle_file_decryption(){
    char filename[256];
    printf("\nEnter the filename to decrypt: ");
    scanf("%s", filename);
    getchar(); // limpia salto de línea

    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Could not open file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);

    char *content = malloc(length + 1);
    fread(content, 1, length, file);
    fclose(file);
    content[length] = '\0';

    char *decrypted = decrypt(content, length);

    char output_file[256];
    sprintf(output_file, "%s.dec", filename);
    FILE *outfile = fopen(output_file, "w");
    if (!outfile) {
        printf("Could not create output file.\n");
        free(content);
        free(decrypted);
        return;
    }

    fwrite(decrypted, 1, length, outfile);
    fclose(outfile);

    printf("\nDecrypted content saved to: %s\n", output_file);

    free(content);
    free(decrypted);
    content=decrypted=NULL;
}