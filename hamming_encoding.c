#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int data_array[27];
int bit_array[32];
int hamming_array[32] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int encoded_array[32] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int parity[] = {1, 2, 4, 8, 16};

int parity_one[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
int parity_two[] = {2, 3, 6, 7, 10, 11, 14, 15, 18, 19, 22, 23, 26, 27, 30, 31};
int parity_three[] = {4, 5, 6, 7, 12, 13, 14, 15, 20, 21, 22, 23, 28, 29, 30, 31};
int parity_four[] = {8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 26, 27, 28, 29, 30, 31};
int parity_five[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

void reverseArray(int arr[], int start, int end) {
    int temp, i;

    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }

}

int valueinarray(int val, int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        if(arr[i] == val){
            return 1;
        }
    }
    return 0;
}

uint32_t hamming_encode() {
    
    int i, j;

    for(i = 1, j = 1; j < sizeof(hamming_array)/sizeof(hamming_array[0]); j++) {
        if (j == 1) {
            continue;
        } else if (j == 2) {
            continue;
        } else if (j == 4) {
            continue;
        } else if (j == 8) {
            continue;
        } else if (j == 16) {
            continue;
        } else {
            hamming_array[j] = data_array[i];
            i += 1;
        }
    }

    int p1 = hamming_array[3], p2 = hamming_array[3], p4 = hamming_array[5], p8 = hamming_array[9], p16 = hamming_array[17];
    
    for(i = 1; i < sizeof(hamming_array)/sizeof(hamming_array[0]); i++) {
        
        if (valueinarray(i, parity, sizeof(parity)/sizeof(parity[0]))) {
            continue;
        }

        if (valueinarray(i, parity_one, sizeof(parity_one)/sizeof(parity_one[0]))) {
            if (i == 3) {
                continue;
            }
            p1 ^= hamming_array[i];
        }

        if (valueinarray(i, parity_two, sizeof(parity_two)/sizeof(parity_two[0]))) {
            if (i == 3) {
                continue;
            }
            p2 ^= hamming_array[i];
        }

        if (valueinarray(i, parity_three, sizeof(parity_three)/sizeof(parity_three[0]))) {
            if (i == 5) {
                continue;
            }
            p4 ^= hamming_array[i];
        }

        if (valueinarray(i, parity_four, sizeof(parity_four)/sizeof(parity_four[0]))) {
            if (i == 9) {
                continue;
            }
            p8 ^= hamming_array[i];
        }

        if (valueinarray(i, parity_five, sizeof(parity_five)/sizeof(parity_five[0]))) {
            if (i == 17) {
                continue;
            }
            p16 ^= hamming_array[i];
        }
    }
    printf("\n");

    hamming_array[1] = p1;
    hamming_array[2] = p2;
    hamming_array[4] = p4;
    hamming_array[8] = p8;
    hamming_array[16] = p16;
}

void main(int argc, char **argv) {
 
	uint32_t input_number = (argc < 2) ? 68129 : atoi(argv[1]);
	if (input_number >= (1 << 26)) {
		printf("Use a smaller number < %d\n", (1 << 26));
		return;
	}
	printf("Value: %d\n", input_number);
	printf("Binary:\n");
	printf("\tdddddddddddddddddddddddddd\n");
	printf("\t");
    for (int i = 25; i >= 0; i--) {
        data_array[i + 1] = (input_number & (1 << i)) >> i;
		printf("%d", data_array[i + 1]);
    }
    printf("\n");

	hamming_encode();

	printf("encoded:\n");
	printf("\tddddddddddddddd ddddddd ddd d\n");
	printf("\t");
    for (int i = 31; i >= 1; i--) {
		printf("%d", hamming_array[i]);
        encoded_array[i] = hamming_array[i];
    }
    printf("\n");
	printf("\t               p       p   p pp\n");

    return;
}