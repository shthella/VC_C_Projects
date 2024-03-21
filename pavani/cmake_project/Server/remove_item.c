#include "remove_item.h"

void remove_item(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to remove item function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  // Open database
  debug_log(2, "Open database for remove item\n");
  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for remove item\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  // Receive item ID to be removed
  int item_id;
  debug_log(3, "Receiving item_id to remove\n");
  recv(client_socket, & item_id, sizeof(item_id), 0);

  // Prepare SQL statement to delete the item
  char sql[500];
  debug_log(3, "SQL query to remove item\n");
  sprintf(sql, "DELETE FROM menu_items WHERE id = %d AND restaurant_id = %d;", item_id, restaurant_id);

  // Execute the SQL statement
  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for remove item\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

    // Send failure message to the client
    debug_log(3, "Failed to remove item. SQL error\n");
    char * failureMsg = "Failed to remove item. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);

  } else {
    // Send success message to the client
    debug_log(3, "Item removed successfully\n");
    printf("Item removed successfully\n");
    char * successMsg = "Item removed successfully.";
    send(client_socket, successMsg, strlen(successMsg), 0);

  }

  // Close database
  debug_log(2, "Close database for remove item\n");
  sqlite3_close(db);

}

