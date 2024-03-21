#include "add_item.h"

void add_item(int client_socket) {
  debug_log(2, "Entering to add item function\n");
  int num_items;
  num_items = getInput("Enter the number of items to add: ");

  // Send the number of items to the server
  send(client_socket, & num_items, sizeof(num_items), 0);

  debug_log(3, "Sending number of items to server\n");
  // Loop to send each item detail to the server
  for (int i = 0; i < num_items; i++) {

    char item_name[100];
    float price;

    printf("Enter Item Details for Item %d:\n", i + 1);
    printf("Item Name: ");
    scanf("%s", item_name);
    debug_log(3, "Send of item details toserver\n");
    // Send item name to the server
    send(client_socket, item_name, sizeof(item_name), 0);

    printf("Price: ");
    scanf("%f", & price);

    // Send price to the server
    send(client_socket, & price, sizeof(price), 0);

  }
}
