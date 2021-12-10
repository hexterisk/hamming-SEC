#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int encoded_array[32] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int parity[] = {1, 2, 4, 8, 16};

int parity_one[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
int parity_two[] = {2, 3, 6, 7, 10, 11, 14, 15, 18, 19, 22, 23, 26, 27, 30, 31};
int parity_three[] = {4, 5, 6, 7, 12, 13, 14, 15, 20, 21, 22, 23, 28, 29, 30, 31};
int parity_four[] = {8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 26, 27, 28, 29, 30, 31};
int parity_five[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

int valueinarray(int val, int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        if(arr[i] == val){
            return 1;
        }
    }
    return 0;
}

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

uint32_t hamming_error_check() {

    int i, p1 = encoded_array[1], p2 = encoded_array[2], p4 = encoded_array[4], p8 = encoded_array[8], p16 = encoded_array[16];

    for(i = 1; i < sizeof(encoded_array)/sizeof(encoded_array[0]); i++) {
        
        if (valueinarray(i, parity_one, sizeof(parity_one)/sizeof(parity_one[0]))) {
            if(i == 1) {
                continue;
            }
            p1 ^= encoded_array[i];
        }
    }

    for(i = 1; i < sizeof(encoded_array)/sizeof(encoded_array[0]); i++) {
        
        if (valueinarray(i, parity_two, sizeof(parity_two)/sizeof(parity_two[0]))) {
            if(i == 2) {
                continue;
            }
            p2 ^= encoded_array[i];
        }
    }

    for(i = 1; i < sizeof(encoded_array)/sizeof(encoded_array[0]); i++) {
        
        if (valueinarray(i, parity_three, sizeof(parity_three)/sizeof(parity_three[0]))) {
            if(i == 4) {
                continue;
            }
            p4 ^= encoded_array[i];
        }
    }

    for(i = 1; i < sizeof(encoded_array)/sizeof(encoded_array[0]); i++) {
        
        if (valueinarray(i, parity_four, sizeof(parity_four)/sizeof(parity_four[0]))) {
            if(i == 8) {
                continue;
            }
            p8 ^= encoded_array[i];
        }
    }

    for(i = 1; i < sizeof(encoded_array)/sizeof(encoded_array[0]); i++) {
        
        if (valueinarray(i, parity_five, sizeof(parity_five)/sizeof(parity_five[0]))) {
            if(i == 16) {
                continue;
            }
            p16 ^= encoded_array[i];
        }
    }

    if ((p1 + p2 + p4 + p8 + p16) == 0) {
        printf("No errors in the received encoding.\n");
    } else {
        int c = p1*1 + p2*2 + p4*4 + p8*8 + p16*16;
        printf("Error is at position: %d", c);
    }
}


void main(int argc, char **argv) {
 
	uint32_t input_number = (argc < 2) ? 67108863 : atoi(argv[1]);
    int i;
    char str[33];
    
    fgets(str, 33, stdin);

    for(i = 0; i < 31; i++) {
        encoded_array[31 - i] = str[i] - '0';
    }
    hamming_error_check();
}