#include "display_menu.h"

void display_restaurants(int client_socket) {
    debug_log(2, "Display Restaurants\n");
    char buffer[1024];
    int bytes_received;
    debug_log(3, "Variables created for display restaurants function\n");

    // Receive restaurant data from the server
    while (1) {
        debug_log(3, "Receive restaurant data from the server\n");
        // Clear the buffer for the next iteration
        memset(buffer, 0, sizeof(buffer));

        // Send acknowledgment to the server
        debug_log(3, "Send acknowledgment to the server\n");
        char ack[] = "ACK";
        send(client_socket, ack, strlen(ack), 0);
        sleep(1);

        // Receive data from the server
        debug_log(3, "Receive data from the server\n");
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0) {
            debug_log(3, "Error receiving data for display restaurants function\n");
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        } else if (bytes_received == 0) {
            // Server closed the connection
            debug_log(3, "Server connection closed for display restaurants function\n");
            break;
        }

        // Check if it's the end of data message
        debug_log(3, "Checking for the end message from server\n");
        if (strncmp(buffer, "END", 3) == 0) {
            debug_log(3, "Received end message, exiting loop\n");
            break;
        }

        // Print received restaurant data
        printf("%s", buffer);
        debug_log(3, "Print received restaurant data\n");
    }

    printf("Restaurants displayed.\n");
}

void display_menu(int client_socket) {
  debug_log(2, "Entering to receive menu function\n");
  char buffer[1024];
  int bytes_received;

  // Receive menu data from the server
  while (1) {
    // Clear the buffer for the next iteration
    memset(buffer, 0, sizeof(buffer));

    // Receive data from the server
    bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
      debug_log(3, "Error receiving data\n");
      perror("Error receiving data");
      break;
    } else if (bytes_received == 0) {
      debug_log(3, "Server connection closed\n");
      // Server closed the connection
      break;
    }

    // Check if it's the end of data message
    if (strncmp(buffer, "END", 3) == 0) {
      break;
    }

    // Print received menu data
    printf("%s", buffer);

    // Send acknowledgment to the server
    char ack[10] = "ACK";
    send(client_socket, ack, strlen(ack), 0);
  }

  printf("\nMenu displayed.\n");
}
