#include "place_order.h"

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
