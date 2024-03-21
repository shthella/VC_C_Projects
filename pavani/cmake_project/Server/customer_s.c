#include "customer_s.h"

void customer_interface(int client_socket) {
  debug_log(1, "Entering to customer interface\n");
  int restaurant_id;
  char message[1024];
  // Display restaurants to customer, to select restaurants
  debug_log(2, "Call for display restaurant function\n");
  display_restaurants(client_socket);

  //recieving from customer
  debug_log(3, "Receiving restaurant choice from customer\n");
  recv(client_socket, & restaurant_id, sizeof(restaurant_id), 0);

  int c;
  do {
    debug_log(2, "Choice for Customer tasks\n");
    memset(message, 0, sizeof(message));
    recv(client_socket, message, sizeof(message) - 1, 0);

    c = atoi(message);
    printf("Customer Choice: %d\n", c);
    switch (c) {
    case 1:
      debug_log(3, "Call for customer menu function\n");
      display_menu(client_socket, restaurant_id);

      break;
    case 2:
      debug_log(3, "Call for place order function\n");
      place_order(client_socket, restaurant_id);

      break;
    case 3:
      debug_log(3, "Exit from customer tasks\n");
      printf("Exiting...\n");

      break;
    default:
      debug_log(3, "Invalid Choice\n");
      printf("Invalid choice\n");
      break;

    }
  } while (c != 3);

}
