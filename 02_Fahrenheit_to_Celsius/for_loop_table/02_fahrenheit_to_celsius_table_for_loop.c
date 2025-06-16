// include <stdio.h> specifies the standard input/output library.
#include <stdio.h>
/*
    * This program converts a temperature from Fahrenheit to Celsius.
    * The formula used for conversion is:
    * C = (F - 32) * 5 / 9
    * where C is the temperature in Celsius and F is the temperature in Fahrenheit.
    * The program prints temperature conversion of Fahrenheit to celsius,
    * performs the conversion in increments of 20units from 0 to 300 (Fahrenheit), and then displays the result in Celsius.
    * Example table for conversion:
    * 
    * |------------+---------|
    * | Fahrenheit | Celsius |
    * +------------+---------|
    * |          0 |      17 |
    * |         20 |      -6 |
    * |         40 |       4 |
    * |         60 |      15 |
    * |         80 |      26 |
    * |        100 |      37 |
    * |        120 |      48 |
    * +------------+---------+
    * 
*/
int main() {
    int fahrenheit;
    float celsius;
    int lower, upper, step;

    lower = 0;   // Lower limit of the temperature table
    upper = 300; // Upper limit of the temperature table
    step = 20;   // Step size for the temperature increments

    // Print the table header
    printf("+------------+---------+\n");
    printf("| Fahrenheit | Celsius |\n");
    printf("+------------+---------+\n");

    // Convert Fahrenheit to Celsius using the formula
    celsius = (fahrenheit - 32.0) * 5.0 / 9.0;


    for (fahrenheit = lower; fahrenheit <= upper; fahrenheit += step) {
        // Convert the current Fahrenheit value to Celsius
        celsius = (fahrenheit - 32.0) * 5.0 / 9.0;

        // Print the current Fahrenheit and corresponding Celsius values
        // Note: The format specifiers %10d and %7.2f are used to align the output in the table.
        // %10d aligns the Fahrenheit value in a field of width 10,
        // %7.2f aligns the Celsius value in a field of width 7 with two decimal places.
        printf("| %10d | %7.2f |\n", fahrenheit, celsius);
    }

    // Print the table footer
    printf("+------------+---------+\n");

    return 0;
}