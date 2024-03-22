#include "customer.h"

bool isValidYNInput(char input) {
  return (input == 'y' || input == 'Y' || input == 'n' || input == 'N');
}

char getYNInput(char prompt[]) {
  char input;
  do {
    printf("%s", prompt);
    scanf(" %c", & input);

    if (!isValidYNInput(input)) {
      while (getchar() != '\n');
      printf("Invalid input. Please enter 'y' or 'n'.\n");
    }
  } while (!isValidYNInput(input));
  return input;
}

void place_order(int client_socket) {
    debug_log(2, "Entering to place order function\n");

    // Send customer details
    char name[100];
    char contact_number[20];
    debug_log(3, "Creating variables for place order function\n");
    debug_log(3, "Sending customer details to server\n");
    printf("Enter name: ");
    scanf("%s", name);
    // Send item name to the server
    send(client_socket, name, sizeof(name), 0);

    // Read contact number
    printf("Enter contact_number: ");
    scanf("%s", contact_number);
    // Send item name to the server
    send(client_socket, contact_number, sizeof(contact_number), 0);

    // Send order details
    char continue_order = 'y';
    do {
        debug_log(3, "Sending order details to server\n");
        int item_id;
        int quantity;

        printf("Enter item ID: ");
        scanf("%d", &item_id);
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        send(client_socket, &item_id, sizeof(item_id), 0);
        send(client_socket, &quantity, sizeof(quantity), 0);

        // Wait for server response
        char response[1024];
        memset(response, 0, sizeof(response));
        recv(client_socket, response, sizeof(response)-1, 0);

        // Check if the response indicates an error
        if (strncmp(response, "Server Error:", 13) == 0) {
            printf("%s\n", response);  // Display the error message received from the server
            continue;  // Skip further processing for this invalid item ID
        }

        // Print the server response
        printf("%s\n", response);

        continue_order = getYNInput("Do you want to continue ordering? (y/n): ");

        send(client_socket, &continue_order, sizeof(continue_order), 0);

    } while (continue_order == 'y');

    // Receive and print the invoice
    char invoice[4096];
    memset(invoice, 0, sizeof(invoice));
    recv(client_socket, invoice, sizeof(invoice) - 1, 0);

    debug_log(3, "Receiving invoice details from server\n");
    printf("\t---------------------------------------------\n\n");
    printf("Invoice:\n%s\n", invoice);
    printf("\t---------------------------------------------\n");
    printf("\n\t*********Thank You Visit Again*****************\n");
}

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
