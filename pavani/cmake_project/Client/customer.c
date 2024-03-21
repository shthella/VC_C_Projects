#include "customer.h"

void customer_interface(int client_socket) {
  debug_log(1, "Entering into Customer interface\n");
  printf("\n");
  printf("\t---------------------------------------------\n");
  printf("\t\tWelcome to Customer Interface\t\n");
  printf("\t---------------------------------------------\n");
  printf("\n");

  int restaurant_id;
  char message[1024];
  int c;
  printf("Select Restaurant:\n");
  debug_log(2, "Selecting avaliable restaurants\n");
  display_restaurants(client_socket);

  printf("Enter restaurant choice: ");
  scanf("%d", & restaurant_id);
  getchar(); // Consume the newline character
  send(client_socket, & restaurant_id, sizeof(restaurant_id), 0);

  while (1) {

    debug_log(2, "Display of customer tasks\n");
    l2:
      printf("\nCustomer Options:\n");
    printf("1. Display Menu\n");
    printf("2. Place Order\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
    fgets(message, sizeof(message), stdin);

    // Check if the input is numeric
    if (isdigit(message[0])) {
      send_message(client_socket, message);

      c = atoi(message);

      switch (c) {
      case 1:
        debug_log(3, "Call of customer menu function\n");
        display_menu(client_socket);
        goto l2;
        break;
      case 2:
        debug_log(3, "Call of place order function\n");
        place_order(client_socket);

        break;
      case 3:
        debug_log(3, "Exit from the custome tasks\n");
        printf("Exiting...\n");

        break;
      default:
        debug_log(3, "Invalid choice\n");
        printf("Invalid choice\n");
        break;
      }
      if (c == 3) {
        break; // Break the loop if the user chose option 7 to exit
      }
    } else {
      // Input is not numeric
      printf("Invalid input. Please enter a numeric choice.\n");
    }
    debug_log(3, "Clear of input buffer for customer interface\n");
    clear_input_buffer(); // Clear input buffer

  }
}
