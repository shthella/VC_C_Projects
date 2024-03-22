#include "customer_s.h"

int getCustomerIdFromDatabase(const char * name) {
  debug_log(2, "Fetching customer_id from database\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int customer_id = -1; // Initialize customer_id to -1 as an error indicator

  // Open database
  debug_log(2, "Open database for fetching customer_id\n");
  if (sqlite3_open(DATABASE, & db) == SQLITE_OK) {
    char sql[256];
    debug_log(3, "SQL query for fetching the customer_id\n");
    sprintf(sql, "SELECT id FROM customers WHERE name = '%s';", name);

    // Prepare SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, & stmt, NULL) == SQLITE_OK) {
      // Execute SQL statement
      if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Retrieve customer_id from the result
        debug_log(3, "Retrieve customer_id from the result\n");
        customer_id = sqlite3_column_int(stmt, 0);

      }
    }

    // Finalize statement and close database
    debug_log(2, "Close database for fetching customer_id\n");
    sqlite3_finalize(stmt);
    sqlite3_close(db);

  }

  return customer_id;

}

double get_item_price(int restaurant_id, int item_id) {
  debug_log(2, "Getting item price from database\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;
  double price = -1; // Initialize price to -1 (indicating not found)

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database to fetch item price\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return price;
  }

  // Prepare SQL statement to select the price of the item based on its ID and restaurant ID
  debug_log(3, "SQL query to fetch item price from database\n");
  char * sql = "SELECT price FROM menu_items WHERE restaurant_id = ? AND id = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to open database to fetch item price\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return price;
  }

  // Bind the restaurant_id and item_id parameters to the prepared statement
  debug_log(3, "Bind the restauramnt_id and item_id parameters to the prepared statement\n");
  sqlite3_bind_int(stmt, 1, restaurant_id);

  sqlite3_bind_int(stmt, 2, item_id);

  // Execute the SQL statement
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Fetch the price of the item from the result set
    price = sqlite3_column_double(stmt, 0);

  }

  // Finalize the statement and close the database connection
  debug_log(2, "Close databse connection for fetching of item price\n");
  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return price;

}

// Function to check if an item exists in the menu for a given restaurant
int isItemInMenu(int restaurant_id, int item_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open the SQLite database
    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0; // Return false (0) indicating item not found due to database error
    }

    // Prepare the SQL statement to check if the item exists in the menu
    const char *sql = "SELECT COUNT(*) FROM menu_items WHERE restaurant_id = ? AND id = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0; // Return false (0) indicating item not found due to SQL error
    }

    // Bind the restaurant_id and item_id parameters to the prepared statement
    sqlite3_bind_int(stmt, 1, restaurant_id);
    sqlite3_bind_int(stmt, 2, item_id);

    // Execute the SQL statement
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0); // Get the count of rows returned
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // If count > 0, the item exists in the menu; otherwise, it does not
    return count > 0;
}

void add_order_to_database(int restaurant_id, int customer_id, int item_id, int quantity, double total_price) {
  debug_log(2, "Add order details to databse\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for Add order details\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  char sql[500];
  debug_log(3, "SQL query to add order details to database\n");
  sprintf(sql, "INSERT INTO orders (restaurant_id, customer_id, item_id, quantity, total_price) VALUES (%d, %d, %d, %d, %.2f);",
    restaurant_id, customer_id, item_id, quantity, total_price);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for add order details to database\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

  } else {
    printf("Order added to the database successfully.\n");
  }
  debug_log(2, "Close database for adding order details\n");
  sqlite3_close(db);

}

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

void place_order(int client_socket, int restaurant_id) {
    debug_log(2, "Entering to place order function\n");
    char name[100];
    char contact_number[20];

    // Receive customer details from the client
    debug_log(3, "Receive of customer details\n");
    memset(name, 0, sizeof(name));
    memset(contact_number, 0, sizeof(contact_number));

    recv(client_socket, name, sizeof(name), 0);
    recv(client_socket, contact_number, sizeof(contact_number), 0);

    // Database operations to insert customer details
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        debug_log(3, "Cannot open database to place order\n");
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[500];
    debug_log(3, "SQL query to insert the order into database\n");
    sprintf(sql, "INSERT INTO customers (restaurant_id, name, contact_number) VALUES (%d, '%s', '%s');",
            restaurant_id, name, contact_number);
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        debug_log(3, "SQL error for placing order\n");
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    int customer_id = getCustomerIdFromDatabase(name);

    OrderedItem ordered_items[100]; // Assuming a maximum of 100 items
    int num_items = 0;

    char continue_order;
    do {
        debug_log(3, "Receive order details from the customer\n");
        // Receive order details from the client
        int item_id;
        int quantity;
        order:

        recv(client_socket, &item_id, sizeof(item_id), 0);
        recv(client_socket, &quantity, sizeof(quantity), 0);

        // Check if the item ID exists in the menu for the selected restaurant
        if (isItemInMenu(restaurant_id, item_id)) {
            // Item exists in the menu, proceed with order placement
            debug_log(2, "Invoice generation\n");
            // Calculate total price, retrieve item details from the database
            double price = get_item_price(restaurant_id, item_id);

            double total_price = price * quantity;

            // Calculate total price with tax
            double total_price_with_tax = total_price * 1.1;

            // Save ordered item details
            debug_log(2, "Save ordered item details\n");
            ordered_items[num_items].item_id = item_id;
            ordered_items[num_items].quantity = quantity;
            ordered_items[num_items].price = price;
            ordered_items[num_items].total_price_with_tax = total_price_with_tax;
            num_items++;

            // Add order details to the database
            add_order_to_database(restaurant_id, customer_id, item_id, quantity, total_price_with_tax);

            const char *message = "Order Placed Successfully!\n";
            send(client_socket, message, strlen(message), 0);
        } else {
            // Item does not exist in the menu
            // Notify the customer and ask for a valid item ID
            debug_log(3, "Item ID is not present in the menu\n");
            const char *error_message = "Server Error: Item ID is not present in the menu. Please enter a valid item ID.";
            send(client_socket, error_message, strlen(error_message), 0);
            debug_log(3, "goto order\n");
            goto order; // Skip further processing for this invalid item ID
        }

        // Ask if the user wants to continue ordering
        debug_log(2, "Waiting for the customer response to continue order\n");
        recv(client_socket, &continue_order, sizeof(continue_order), 0);

    } while (continue_order == 'y');

    // Generate invoice once all items are ordered
    debug_log(3, "Call for generate invoice function\n");
    generate_invoice(client_socket, ordered_items, num_items);

    debug_log(2, "Close database for place order function\n");
    sqlite3_close(db);
}

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
