#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate parity byte (XOR of all bytes)
unsigned char generate_parity(unsigned char message[], int size) {
    unsigned char parity = 0;
    for (int i = 0; i < size; i++) {
        parity ^= message[i]; // XOR each byte
    }
    return parity;
}

// Function to simulate random bit errors
void introduce_error(unsigned char message[], int size, int num_bits) {
    for (int n = 0; n < num_bits; n++) {
        int byte_index = rand() % size;
        int bit_index = rand() % 8;
        message[byte_index] ^= (1 << bit_index); // Flip the bit
    }
}

// Function to print a message in binary
void print_message(unsigned char message[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (message[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Initialize random seed

    // 8-byte message
    unsigned char message[8] = {0b10110011, 0b11001100, 0b11110000, 0b00001111,
                                0b01010101, 0b10101010, 0b11111111, 0b00000000};

    // Generate parity byte
    unsigned char parity_byte = generate_parity(message, 8);

    // Transmitted message = 8 bytes + parity byte
    unsigned char transmitted[9];
    for (int i = 0; i < 8; i++) transmitted[i] = message[i];
    transmitted[8] = parity_byte;

    printf("Original Message + Parity:\n");
    print_message(transmitted, 9);

    // ----- SIMULATION CASES -----

    // Case 1: No error
    printf("\nCase 1: No Error\n");
    unsigned char received1[9];
    for (int i = 0; i < 9; i++) received1[i] = transmitted[i];
    unsigned char calculated_parity1 = generate_parity(received1, 8);
    if (calculated_parity1 == received1[8])
        printf("No Error Detected ✅\n");
    else
        printf("Error Detected ❌\n");

    // Case 2: Single-bit error
    printf("\nCase 2: Single-bit Error\n");
    unsigned char received2[9];
    for (int i = 0; i < 9; i++) received2[i] = transmitted[i];
    introduce_error(received2, 9, 1); // flip 1 bit
    print_message(received2, 9);
    unsigned char calculated_parity2 = generate_parity(received2, 8);
    if (calculated_parity2 == received2[8])
        printf("No Error Detected ✅\n");
    else
        printf("Error Detected ❌\n");

    // Case 3: Two-bit errors
    printf("\nCase 3: Two-bit Errors\n");
    unsigned char received3[9];
    for (int i = 0; i < 9; i++) received3[i] = transmitted[i];
    introduce_error(received3, 9, 2); // flip 2 bits
    print_message(received3, 9);
    unsigned char calculated_parity3 = generate_parity(received3, 8);
    if (calculated_parity3 == received3[8])
        printf("No Error Detected ✅\n");
    else
        printf("Error Detected ❌\n");

    return 0;
}
