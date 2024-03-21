#include "remove_item.h"

void remove_item(int client_socket) {
  debug_log(2, "Entering to remove item function\n");
  int item_id;
  char message[2048];
  debug_log(3, "Variables created for remove item function\n");
  // Read item ID from the user
  item_id = getInput("Enter item ID to be removed: ");
  // Send item ID to the server
  send(client_socket, & item_id, sizeof(item_id), 0);

  debug_log(3, "Sending item_id to server to remove item\n");
  // Receive response from the server
  recv(client_socket, message, sizeof(message) - 1, 0);

  debug_log(3, "Receive response from server that item removed\n");
  printf("Server response: %s\n", message);
}
