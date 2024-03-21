#include "display_menu.h"

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
