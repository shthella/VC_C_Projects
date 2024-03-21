#include "display_order_history.h"

void display_order_history(int client_socket) {
  debug_log(2, "Entering to order history function\n");
  char buffer[1024];
  int bytes_received;
  int time_interval;
  debug_log(3, "Variables created for order history function\n");
  printf("Select time interval:\n");
  printf("1. Daily\n");
  printf("2. Weekly\n");
  printf("3. Monthly\n");
  time_interval = getInput("Enter your choice: ");

  // Send request for order history with the desired time interval
  send(client_socket, & time_interval, sizeof(time_interval), 0);

  debug_log(3, "Sending request for order history with the desired time interval\n");
  // Receive order history data from the server
  debug_log(3, "Receive response from server to display order history\n");
  while (1) {

    // Clear the buffer for the next iteration
    memset(buffer, 0, sizeof(buffer));
    // Receive data from the server
    debug_log(3, "Clear the buffer and receive data from the server\n");
    char ack[] = "ACK";
    send(client_socket, ack, strlen(ack), 0);
    sleep(1);
    bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
      debug_log(3, "Error receiving data for display order history function\n");
      perror("Error receiving data");
      exit(EXIT_FAILURE);
    } else if (bytes_received == 0) {

      debug_log(3, "Server connection closed for display order history function\n");
      // Server closed the connection
      break;
    }

    // Check if it's the end of data message
    if (strncmp(buffer, "END", 3) == 0) {
      debug_log(3, "Waiting for end message for display order history function\n");

      break;
    }

    // Print received order history data
    printf("%s", buffer);

    debug_log(3, "Printing order history\n");

  }

  printf("Order history displayed.\n");
}
