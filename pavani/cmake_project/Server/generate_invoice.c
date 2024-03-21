#include "generate_invoice.h"

void generate_invoice(int client_socket, OrderedItem ordered_items[], int num_items) {
  // Prepare the bill in a formatted string
  debug_log(2, "Entering to generate invoice function\n");
  char invoice[4096];
  sprintf(invoice, "\n\n======= Invoice =======\n\n");

  double total_bill = 0.0;

  // Iterate over ordered items and add them to the bill
  for (int i = 0; i < num_items; ++i) {
    debug_log(2, "Collection of all the items and calculation of total bill\n");
    total_bill += ordered_items[i].total_price_with_tax;
    sprintf(invoice + strlen(invoice), "Item ID: %d | Quantity: %d | Price: $%.2f | Total Price with Tax: $%.2f\n",
      ordered_items[i].item_id, ordered_items[i].quantity, ordered_items[i].price, ordered_items[i].total_price_with_tax);

  }

  // Add total bill amount to the invoice
  debug_log(2, "Invoice generation\n");
  sprintf(invoice + strlen(invoice), "\nTotal Bill: $%.2f\n\n", total_bill);

  // Send the invoice to the client
  debug_log(3, "Sending invoice to customer\n");
  int bytes_sent = send(client_socket, invoice, strlen(invoice), 0);

  if (bytes_sent < 0) {
    debug_log(3, "Error sending invoice to customer\n");
    perror("Error sending invoice");

    return;
  }
}
