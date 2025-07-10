#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert binary string to decimal integer
int binToDec(char *bin) {
    int dec = 0;
    while (*bin) {
        dec = (dec << 1) + (*bin++ - '0');
    }
    return dec;
}

// Function to convert decimal integer to binary string
void decToBin(int num, char *bin, int bits) {
    bin[bits] = '\0';
    int i;
    for (i = bits - 1; i >= 0; --i, num >>= 1) {
        bin[i] = (num & 1) ? '1' : '0';
    }
}

// Function to add two binary numbers
void add(char* A, const char* M, char* Sum, int length) {
    int carry = 0,i;
    // Iterating through the number A
    for (i = length - 1; i >= 0; i--) {
        // Adding the values at both the indices along with the carry
        int temp = (A[i] - '0') + (M[i] - '0') + carry;
        // If the binary number exceeds 1
        if (temp > 1) {
            Sum[i] = (temp % 2) + '0';
            carry = 1;
        } else {
            Sum[i] = temp + '0';
            carry = 0;
        }
    }
    Sum[length] = '\0';
}

// Function to subtract two binary numbers
void subtract(char* A, const char* M, char* Diff, int length) {
    int borrow = 0, i ;
    // Iterating through the number A
    for (i = length - 1; i >= 0; i--) {
        // Subtracting the values at both the indices along with the borrow
        int temp = (A[i] - '0') - (M[i] - '0') - borrow;
        // If the binary number goes below 0
        if (temp < 0) {
            Diff[i] = (temp + 2) + '0';
            borrow = 1;
        } else {
            Diff[i] = temp + '0';
            borrow = 0;
        }
    }
    Diff[length] = '\0';
}

// Function to left shift a binary number
void leftShift(char* A, char* Q, int length) {
	int i;
    for (i = 0; i < length - 1; i++) {
        A[i] = A[i + 1];
    }
    A[length - 1] = Q[0];
    for (i = 0; i < length - 1; i++) {
        Q[i] = Q[i + 1];
    }
    Q[length - 1] = '0';
}

// Function to print binary number
void printBinary(char* bin) {
    printf("%s", bin);
}

// Function to perform non-restoring division
void nonRestoringDivision(char* Q, char* M, char* A, int bits) {
    char temp[bits + 1];
    int count = bits;
    
    printf("Initial Values: A: %s Q: %s M: %s\n", A, Q, M);
    
    while (count > 0) {
        // Step 2: Check sign of A and perform the appropriate operation
        if (A[0] == '1') {
            leftShift(A, Q, bits);
            add(A, M, temp, bits);
            strcpy(A, temp);
            printf("After left shift and add: A: %s Q: %s\n", A, Q);
        } else {
            leftShift(A, Q, bits);
            subtract(A, M, temp, bits);
            strcpy(A, temp);
            printf("After left shift and subtract: A: %s Q: %s\n", A, Q);
        }

        // Step 3: Set Q0 based on the sign of A
        if (A[0] == '0') {
            Q[bits - 1] = '1';
        } else {
            Q[bits - 1] = '0';
        }

        count--;
    }

    // Step 5: Final correction of the remainder
    if (A[0] == '1') {
        add(A, M, temp, bits);
        strcpy(A, temp);
    }

    printf("\nQuotient(Q): ");
    printBinary(Q);
    printf(" Remainder(A): ");
    printBinary(A);
    printf("\n");
}

int main() {
    char dividend[65], divisor[65];
    int bitLength;

    printf("Enter the dividend (binary): ");
    scanf("%s", dividend);
    printf("Enter the divisor (binary): ");
    scanf("%s", divisor);

    bitLength = strlen(dividend);

    // Ensure that the binary numbers have the same length
    char Q[bitLength + 1];
    char M[bitLength + 1];
    char A[bitLength + 1];

    strcpy(Q, dividend);
    strcpy(M, divisor);
    memset(A, '0', bitLength);
    A[bitLength] = '\0';

    nonRestoringDivision(Q, M, A, bitLength);

    return 0;
}