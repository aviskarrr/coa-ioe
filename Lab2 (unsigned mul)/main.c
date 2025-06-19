#include <stdio.h>
#include <conio.h>

// Function to perform binary addition
int binaryAddition(int a, int b) {
    int carry = 0, result = 0, bit = 1;
    while (a != 0 || b != 0) {
        int bit_a = a % 10;
        int bit_b = b % 10;

        // Add the bits along with the carry
        int sum = bit_a + bit_b + carry;

        // Update the result
        result += (sum % 2) * bit;

        // Calculate the carry for the next bit
        carry = sum / 2;

        // Move to the next bit
        a /= 10;
        b /= 10;
        bit *= 10;
    }

    // Add the carry if exists
    result += carry * bit;
    return result;
}

// Function to perform logical shift left
int logicalShiftLeft(int num) {
    return num * 10; // Equivalent to shifting left by 1 position
}

// Function to perform logical shift right
int logicalShiftRight(int num) {
    return num / 10; // Equivalent to shifting right by 1 position
}

// Function to perform Booth's multiplication algorithm
int boothMultiply(int multiplicand, int multiplier) {
    int accumulator = 0;
    int bitMask = 1;

    // Iterate over each bit of the multiplier
    while (multiplier != 0) {
        // Step 2: Test Y0; if it is 1, add content of X to the accumulator A
        if (multiplier % 10 == 1) {
            accumulator = binaryAddition(accumulator, multiplicand);
        }

        // Step 3: Logical Shift the content of X left one position and content of Y right one position
        multiplicand = logicalShiftLeft(multiplicand);
        multiplier = logicalShiftRight(multiplier);

        // Move the bit mask to the next bit
        bitMask *= 10;
    }

    return accumulator;
}

// Function to convert binary number to decimal
int binaryToDecimal(int binary) {
    int decimal = 0, base = 1;
    while (binary != 0) {
        int lastDigit = binary % 10;
        decimal += lastDigit * base;
        binary /= 10;
        base *= 2;
    }
    return decimal;
}

int main() {
    int multiplicand, multiplier;
    printf("Enter the multiplicand (binary): ");
    scanf("%d", &multiplicand);
    printf("Enter the multiplier (binary): ");
    scanf("%d", &multiplier);

    // Step 1: Clear the accumulator (sum)
    int product = boothMultiply(multiplicand, multiplier);

    printf("Product of the two binary numbers: %d (binary)\n", product);
    printf("Product in decimal: %d\n", binaryToDecimal(product));

    getch();
    return 0;
}
