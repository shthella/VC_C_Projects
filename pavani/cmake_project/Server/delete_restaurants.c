#include "delete_restaurants.h"

void handle_delete_restaurant(int client_socket) {
  debug_log(2, "Entering handle_delete_restaurant function\n");
  char restaurant_id_str[20];
  int restaurant_id;
  char response[100];

  // Receive restaurant ID from the client
  debug_log(3, "Receiving restaurant ID from client\n");
  recv(client_socket, restaurant_id_str, sizeof(restaurant_id_str), 0);
  restaurant_id = atoi(restaurant_id_str);

  // Remove the restaurant from the database
  debug_log(3, "Remove restaurant from the database\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for deleting restaurant\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    // Send failure message to the client
    char * failureMsg = "Failed to delete restaurant. Database error.";
    debug_log(3, "Failed to delete restaurant. Database error\n");
    send(client_socket, failureMsg, strlen(failureMsg), 0);
    return;
  }

  // Execute SQL statement to delete the restaurant
  char sql[100];
  sprintf(sql, "DELETE FROM restaurants WHERE id = %d;", restaurant_id);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for deleting restaurant\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);

    // Send failure message to the client
    debug_log(3, "Failed to delete restaurant. SQL error\n");
    char * failureMsg = "Failed to delete restaurant. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);
    return;
  }

  // Send success message to the client
  debug_log(3, "Restaurant deleted successfully\n");
  char * successMsg = "Restaurant deleted successfully.";
  printf("Restaurant deleted successfully.\n");
  send(client_socket, successMsg, strlen(successMsg), 0);

  // Close database
  debug_log(2, "Close database after deleting restaurant\n");
  sqlite3_close(db);
 
}
