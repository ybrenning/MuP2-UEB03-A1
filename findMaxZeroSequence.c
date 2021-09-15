/**
 * File Name: findMaxZeroSequence.c
 * Author: Yannick Brenning
 * Date: 15.09.2021
 * Description: SoSe-21 MuP2-UEB03-A1
 */

#include "findMaxZeroSequence.h"

int main(int argc, char *argv[]) {
    /* Handle input errors and convert input */
    if (argc <= 1) {
        fprintf(stderr, "Please enter an argument\n");
        exit(1);
    } else if (argc > 2) {
        fprintf(stderr, "Too many arguments entered\n");
    }

    char *end;
    int64_t number = strtoll(argv[1], &end, 10);
    /* If the number is zero, check for an error */
    if (number == 0) {
        /* If a conversion error occurred, exit the program */
        if (errno == EINVAL) {
            fprintf(stderr, "Conversion error occurred: %d\n", errno);
            exit(1);
        }
    } printf("Argument provided: %lld\n", number);

    /* Allocating bit_count bits + 1 bit for the null-terminator */
    char *stringDualNumber = (char *) malloc((bit_count + 1) * sizeof(char));
    if (stringDualNumber == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    if (convertDezToDualString(number, stringDualNumber) == 1) exit(1);
    printDualString(stringDualNumber);
    printf("maxZeroSequence: %u", countMaxZeroSequence(stringDualNumber));

    return 0;
}

int convertDezToDualString(const int64_t number, char *stringDualNumber) {
    int bit; int64_t number_pos;
    /* If the number is out of bounds for the data type, return EXIT_FAILURE */
    if (number > INT_MAX || number < INT_MIN) {
        fprintf(stderr, "Number out of range. Please enter a %u-bit number\n", bit_count);
        return EXIT_FAILURE;
    }

    /* If number is negative, we want to first get the binary representation of
     * its absolute value and afterwards calculate the two's complement with
     * the function createComplementOnTwo. */
    number_pos = number < 0 ? number * (-1) : number;

    for (int i = bit_count - 1; i >= 0; i--) {
        /* Set the current bit to the bit at the end of the number
         * e.g. 11010010001000000100000000000100
         *      ^
         * would make bit equal to 00000000000000000000000000000001
         * and consequently set the last element of the C-String to '1':
         * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 1
         * as the loop continues, it builds a C-String with the digits in reversed order
         * of the original binary representative of the number argument
         * */
        bit = number_pos >> i;
        if (bit & 1) {
            stringDualNumber[i] = '1';
        } else {
            stringDualNumber[i] = '0';
        }
    } stringDualNumber[bit_count] = '\0';

    if (number < 0) createComplementOnTwo(stringDualNumber);
    return EXIT_SUCCESS;
}

void createComplementOnTwo(char *stringDualNumber) {
    int i = 0, j = 0;
    /* Invert all bits */
    while (stringDualNumber[i] != '\0') {
        if (stringDualNumber[i] == '1') {
            stringDualNumber[i] = '0';
        } else {
            stringDualNumber[i] = '1';
        } i++;
    }

    /* Add one to the inverted string. Keep in mind that the first
     * element of our C-String is the last digit of our binary number */
    for (j; j <= bit_count - 1; j++) {
        if (stringDualNumber[j] == '0') {
            stringDualNumber[j] = '1';
            return;
        }
    }
}

unsigned short countMaxZeroSequence(const char *stringDualNumber) {
    unsigned short i = 0, count = 0, max = 0;
    /* Loop through C-String and update max using a counter */
    while (stringDualNumber[i] != '\0') {
        if (stringDualNumber[i] == '0') {
            count++;
            if (count > max) max = count;
        } else if (stringDualNumber[i] == '1'){
            count = 0;
        } i++;
    }
    return max;
}

void printDualString(const char *stringDualNumber) {
    /* Print elems of C-String in reversed order to output
     * the binary representation */
    for (int i = bit_count - 1; i >= 0; i--) {
        printf("%c", stringDualNumber[i]);
    } printf("\n");
}