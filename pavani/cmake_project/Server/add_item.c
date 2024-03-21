#include "add_item.h"

void add_item(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to add item function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  // Open database
  debug_log(2, "Open database to add item\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database to add item\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  // Receive number of items to add
  int num_items;
  debug_log(3, "Receive number of items to add\n");
  recv(client_socket, & num_items, sizeof(num_items), 0);

  // Loop to receive and insert item details
  for (int i = 0; i < num_items; i++) {
    char item_name[100];
    float price;

    // Receive item name
    recv(client_socket, item_name, sizeof(item_name), 0);

    // Receive item price
    recv(client_socket, & price, sizeof(price), 0);

    // Insert item into the database
    char sql[500];
    debug_log(3, "SQL query to add item\n");
    sprintf(sql, "INSERT INTO menu_items (restaurant_id, item_name, price) VALUES (%d, '%s', %f);", restaurant_id, item_name, price);
    rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

    if (rc != SQLITE_OK) {
      if (strstr(zErrMsg, "UNIQUE constraint failed")) {
        // Send message to client indicating item already exists
        debug_log(3, "Item already exists\n");
        char message[] = "Item already exists in the menu\n";
        // send(client_socket, message, strlen(message), 0);

      } else {
        debug_log(3, "SQL error for add item\n");
        fprintf(stderr, "SQL error: %s\n", zErrMsg);

      }
      sqlite3_free(zErrMsg);
    } else {
      debug_log(3, "Item added successfully\n");
      fprintf(stdout, "Item added successfully\n");

    }
  }

  // Close database
  debug_log(2, "Close databse for add item\n");
  sqlite3_close(db);

}
