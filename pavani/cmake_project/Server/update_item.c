#include "update_item.h"

void update_item(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to update item function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  // Open database
  debug_log(2, "Open databse for update item\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for update item\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  // Receive updated item details from the client
  int item_id;
  char item_name[100];
  float price;

  recv(client_socket, & item_id, sizeof(item_id), 0);
  recv(client_socket, item_name, sizeof(item_name), 0);
  recv(client_socket, & price, sizeof(price), 0);

  // Prepare SQL statement to update the item
  char sql[500];
  debug_log(3, "SQL query for update item\n");
  sprintf(sql, "UPDATE menu_items SET item_name = '%s', price = %f WHERE id = %d AND restaurant_id = %d;", item_name, price, item_id, restaurant_id);

  // Execute the SQL statement
  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for update item\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

    // Send failure message to the client
    debug_log(3, "Failed to update item. SQL error\n");
    char * failureMsg = "Failed to update item. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);

  } else {
    // Send success message to the client
    debug_log(3, "Item updated successfully\n");
    printf("Item updated successfully\n");
    char * successMsg = "Item updated successfully.";
    send(client_socket, successMsg, strlen(successMsg), 0);

  }

  // Close database
  debug_log(2, "Close database\n");
  sqlite3_close(db);

}
