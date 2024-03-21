#include "update_item.h"

void update_item(int client_socket) {
  debug_log(2, "Entering to update item function\n");
  int item_id;
  char item_name[100];
  float price;
  char message[2048];
  debug_log(3, "Created variables for update item function\n");
  // Read updated item details from the user
  item_id = getInput("Enter item ID to be updated: ");

  printf("Enter updated item name: ");
  scanf("%s", item_name);

  printf("Enter updated price: ");
  scanf("%f", & price);

  // Send updated item details to the server
  send(client_socket, & item_id, sizeof(item_id), 0);

  send(client_socket, item_name, sizeof(item_name), 0);

  send(client_socket, & price, sizeof(price), 0);

  debug_log(3, "Sending item details to server for update\n");
  // Receive response from the server
  recv(client_socket, message, sizeof(message) - 1, 0);
  debug_log(3, "Receive response from server that item updated\n");
  printf(" %s\n", message);

}
