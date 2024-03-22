#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>

#include "debug_log.h"
#include "admin.h"
#include "customer.h"
#include "helper_func.h"

#define PORT 8080
#define DAILY 1
#define WEEKLY 2
#define MONTHLY 3

int main(int argc, char * argv[]) {
  setDebugLevel(argc, argv); // Set debug level based on command-line arguments

  debug_log(1, "Enter into main function\n");
  int client_socket;
  struct sockaddr_in server_addr;
  char message[2048];
  char buffer[2048];
  debug_log(2, "Variables created for main function execution\n");
  // Create client socket
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  debug_log(3, "Creation of client socket connection\n");
  if (client_socket == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }
  debug_log(3, "Initialize server address structure\n");
  // Initialize server address structure
  memset( & server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(ip_addr);
  server_addr.sin_port = htons(PORT);

  debug_log(3, "Connect to the server for the main function\n");
  // Connect to the server
  if (connect(client_socket, (struct sockaddr * ) & server_addr, sizeof(server_addr)) == -1) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }

  // Send user type to the server
  debug_log(2, "Send user type to the server\n");
  s1:

    printf("Select User Type:\n");
  printf("1. Admin\n");
  printf("2. Customer\n");
  printf("3. Exit\n");
  printf("Enter choice: ");
  fgets(message, sizeof(message), stdin);
  if (isdigit(message[0])) {
    send_message(client_socket, message);

    int user_type = atoi(message);

    switch (user_type) {
    case 1:
      debug_log(3, "Call of admin interface function\n");
      admin_interface(client_socket);

      goto s1;
      break;
    case 2:
      debug_log(3, "Call of customer interface function\n");
      customer_interface(client_socket);

      goto s1;
      break;
    case 3:
      debug_log(3, "Exit from user interface\n");
      printf("Exiting...\n");
      break;
    default:
      debug_log(3, "Invalid choice\n");
      printf("Invalid Choice\n");
      break;
      goto s1;
    }
  } else {
    // Input is not numeric
    debug_log(2, "Input is not numeric\n");
    printf("Invalid input. Please enter a numeric choice.\n");

    goto s1;
  }
  debug_log(3, "Close the client socket connection\n");
  // Close the client socket
  close(client_socket);

  return 0;

}
