#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int requiredBits(int n) {
    if (n == 0) return 2; 
    return (int)(log2(n > 0 ? n + 1 : abs(n))) + 2;
}

void dectobinary(int nbit,int num, int arry[]){
	while(nbit>=0){

		if(num>0){
			arry[nbit-1] = num%2;
			num = num/2;
			nbit--;	
		}
		else{
			arry[nbit-1] = 0;
			nbit--;	
		}
	}
	
}


void twoComplement(int arry[], int nbit){
	int bitsum,i,carry=1;
	
	for(i=0;i<nbit;i++){
		arry[i] = !arry[i];
	}
	
	for(i=nbit-1;i>=0;i--){
		bitsum = arry[i]+carry;
		arry[i] = bitsum%2;
		carry = bitsum/2;
	}
}

void showbinary(int *p, int size) {
    int i;
    for (i = 0; i<size; i++) {
        printf("%d ", *(p+i));
    }
    printf("\n");
}


int addbinary(int arry1[],int arry2[],int nbit,int sum[]){
	int i, bitsum,carry =0;
	for(i=nbit-1;i>=0;i--){
		bitsum = arry1[i]+arry2[i]+carry;
		sum[i] = bitsum%2;
		carry = bitsum/2;
	}	
	return carry;
}

int binarytodec(int arry[], int nbit) {
    int result = 0, i;

    if (arry[0] == 1) {
        int temp[32];
        for (i = 0; i < nbit; i++) temp[i] = arry[i];
        twoComplement(temp, nbit);

        for (i = 0; i < nbit; i++) {
            result += temp[nbit - 1 - i] * (1 << i);
        }

        return -result;
    } else {
        for (i = 0; i < nbit; i++) {
            result += arry[nbit - 1 - i] * (1 << i);
        }

        return result;
    }
}




int main() {
    int num1, num2;
    int arry1[32] = {0}, arry2[32] = {0}, sum[32] = {0};

    printf("Enter the two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Dynamically calculate the number of bits needed
    int bits1 = requiredBits(num1);
    int bits2 = requiredBits(num2);
    int nbit = (bits1 > bits2) ? bits1 : bits2;

    if (nbit > 32) {
        printf("Number too large to handle in 32 bits.\n");
        return 1;
    }

    // Convert num1
    if (num1 < 0) {
        dectobinary(nbit, abs(num1), arry1);
        twoComplement(arry1, nbit);
    } else {
        dectobinary(nbit, num1, arry1);
    }
    printf("Binary of %d: ", num1);
    showbinary(arry1, nbit);

    // Convert num2
    if (num2 < 0) {
        dectobinary(nbit, abs(num2), arry2);
        twoComplement(arry2, nbit);
    } else {
        dectobinary(nbit, num2, arry2);
    }
    printf("Binary of %d: ", num2);
    showbinary(arry2, nbit);

    // Add both binaries
    int carry_out = addbinary(arry1, arry2, nbit, sum);
    printf("Sum in binary: ");
    showbinary(sum, nbit);

    int result = binarytodec(sum, nbit);
    printf("Decimal equivalent of sum: %d\n", result);
//overflow
    if ((num1 > 0 && num2 > 0 && result < 0) ||
        (num1 < 0 && num2 < 0 && result > 0)) {
        printf("Overflow Detected\n");
    }

    return 0;
}
