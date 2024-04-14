#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Function
void send_uart(uint8_t *data, size_t size);
uint8_t calculate_checksum(uint8_t *data, size_t size);
void construct_and_send_command(uint8_t version, uint8_t cmd, uint8_t feedback);

int main() {
    uint8_t version, cmd, feedback;

    // Initialize UART
    // init_uart(9600, NO_PARITY, ONE_STOP_BIT);

    printf("Enter command version (HEX): ");
    scanf("%hhx", &version);

    printf("Enter command ID (HEX): ");
    scanf("%hhx", &cmd);

    printf("Enter feedback (1 for feedback, 0 for no feedback): ");
    scanf("%hhx", &feedback);

    // Construct the command and send it
    construct_and_send_command(version, cmd, feedback);

    return 0;
}

void send_uart(uint8_t *data, size_t size) {
    printf("Sending via UART: ");
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

uint8_t calculate_checksum(uint8_t *data, size_t size) {
    uint8_t sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

void construct_and_send_command(uint8_t version, uint8_t cmd, uint8_t feedback) {
    uint8_t message[10];  // Adjust size as needed for different commands
    size_t len = 6;  // Length of data after 'Len' byte

    message[0] = 0x7E;  // Start byte
    message[1] = version;
    message[2] = len;
    message[3] = cmd;
    message[4] = feedback;
    message[5] = 0x00;  // para1, not used
    message[6] = 0x00;  // para2, not used
    message[7] = calculate_checksum(&message[1], len);  // Calculate checksum for the message
    message[8] = 0xEF;  // End byte

    send_uart(message, sizeof(message));
}
