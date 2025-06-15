// include <stdio.h> specifies the standard input/output library.
#include <stdio.h>
/*
    * This program converts a temperature from Fahrenheit to Celsius.
    * The formula used for conversion is:
    * C = (F - 32) * 5 / 9
    * where C is the temperature in Celsius and F is the temperature in Fahrenheit.
    * The program prompts the user to enter a temperature in Fahrenheit,
    * performs the conversion, and then displays the result in Celsius.
    * Example table for conversion:
    * 
    * |------------|---------|
    * | Fahrenheit | Celsius |
    * |------------|---------|
    * | 0          | -17     |
    * | 20         | -6      |
    * | 40         | 4       |
    * | 60         | 15      |
    * | 80         | 26      |
    * | 100        | 37      |
    * | 120        | 48      |
    * |------------|---------|
    * 
*/
int main() {
    float fahrenheit, celsius;

    // Prompt the user to enter a temperature in Fahrenheit
    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);

    // Convert Fahrenheit to Celsius using the formula
    celsius = (fahrenheit - 32.0) * 5.0 / 9.0;

    // Display the result
    printf("Temperature in Celsius: %.2f\n", celsius);

    // Print the table header
    printf("|------------|---------|\n");
    printf("| Fahrenheit | Celsius |\n");
    printf("|------------|---------|\n");

    // Print the current Fahrenheit and corresponding Celsius values
    // Note: The format specifiers %10d and %7d are used to align the output in the table.
    // %10d aligns the Fahrenheit value in a field of width 10,
    // %7d aligns the Celsius value in a field of width 7.
    // .2f is used to display the values with two decimal places.
    printf("| %10.2f | %7.2f |\n", fahrenheit, celsius);
    // Print the table footer
    printf("|------------|---------|\n");
    return 0;
}