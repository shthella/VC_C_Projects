#include "display_menu.h"

void display_menu(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to display menu function\n");
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  // Open the SQLite database
  debug_log(2, "Open database\n");
  rc = sqlite3_open(DATABASE, &db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for display menu\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  // Prepare the SQL statement
  debug_log(3, "SQL query for display menu\n");
  const char *sql = "SELECT id, item_name, price FROM menu_items WHERE restaurant_id = ?;";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to prepare statement for display menu\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  // Bind the restaurant_id parameter to the SQL statement
  debug_log(3, "Bind the restaurant_id to the statement\n");
  sqlite3_bind_int(stmt, 1, restaurant_id);

  // Send each row of menu item information to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send each row of the menu item information to the client\n");
    // Extract data from the result row
    int id = sqlite3_column_int(stmt, 0);
    const char *item_name = (const char *)sqlite3_column_text(stmt, 1);
    double price = sqlite3_column_double(stmt, 2);

    // Create a buffer to send the data
    debug_log(3, "Creation of buffer to send data for display menu function\n");
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "ID: %d, Item: %s, Price: %.2f\n", id, item_name, price);

    // Send the data to the client
    int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
    if (bytes_sent < 0) {
      debug_log(3, "Error sending data to the client\n");
      perror("Error sending data");
      break;
    }
    // Wait for acknowledgment from the client
    char ack[10];
    int valread = recv(client_socket, ack, sizeof(ack) - 1, 0);
    if (valread < 0) {
      debug_log(3, "Error receiving acknowledgment from client\n");
      perror("Error receiving acknowledgment");
      break;
    }

    // Clear the acknowledgment buffer
    memset(ack, 0, sizeof(ack));
  }

  // Send the "END" message separately after sending all restaurant details
  const char *end_message = "END";
  int bytes_sent = send(client_socket, end_message, strlen(end_message), 0);
  if (bytes_sent < 0) {
    debug_log(3, "Error sending end message\n");
    perror("Error sending END message");
  }

  // Finalize the statement and close the database connection
  debug_log(2, "Close database for display menu\n");
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}
