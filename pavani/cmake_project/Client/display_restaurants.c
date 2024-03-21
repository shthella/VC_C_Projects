#include "display_restaurants.h"

void display_restaurants(int client_socket) {
  debug_log(2, "Display Restaurants\n");
  char buffer[1024];
  int bytes_received;
  debug_log(3, "Variables created for display restaurants function\n");
  int i = 0;

  // Receive order history data from the server
  while (1) {
    debug_log(3, "Receive order history data from the server\n");
    // Clear the buffer for the next iteration
    memset(buffer, 0, sizeof(buffer));
    debug_log(3, "Clear of Buffer\n");
    // Receive data from the server
    debug_log(3, "Receive data from the server\n");
    char ack[] = "ACK";
    send(client_socket, ack, strlen(ack), 0);
    sleep(1);

    bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    debug_log(3, "Received restaurant details from server\n");
    if (bytes_received < 0) {
      debug_log(3, "Error receiving data for display restaurants function\n");
      perror("Error receiving data\n");
      exit(EXIT_FAILURE);
    } else if (bytes_received == 0) {
      // Server closed the connection
      debug_log(3, "Server connection closed for display restaurants function\n");
      break;

    }

    // Check if it's the end of data message
    debug_log(3, "Checking for the end message from server\n");
    if (strncmp(buffer, "END", 3) == 0) {
      debug_log(3, "Waiting for end message\n");
      break;

    }

    // Print received restaurants data
    printf("%s", buffer);
    debug_log(3, "Print received restaurants data\n");

  }

  printf("Restaurants displayed.\n");
}
