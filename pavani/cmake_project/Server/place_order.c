#include "place_order.h"

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
