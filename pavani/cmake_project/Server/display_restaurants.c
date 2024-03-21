#include "display_restaurants.h"

void display_restaurants(int client_socket) {
  debug_log(2, "Entering to display restaurants function\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  // Open the database
  debug_log(2, "Open database for display restaurants\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for display restaurants\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  debug_log(3, "SQL query to fetch display of restaurants\n");
  const char * sql = "SELECT id, name FROM restaurants;";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Preparation of SQL statement\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  // Send each row of restaurant information to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send restaurant information to client\n");
    // Extract data from the result row
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);

    // Create a buffer to send the data
    debug_log(3, "Creation of a buffer to send the data\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "ID: %d, Name: %s\n", id, name);
    // Send the data to the client
    debug_log(3, "Send the data to the client\n");
    char ack[10];
    int valread;
    valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
    debug_log(3, "Receive data into acknowledgement buffer\n");
    if (valread > 0) {
      ack[valread] = '\0';
      int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
      sleep(1);
    }

  }
  // Send the "END" message separately after sending all restaurant details
  debug_log(3, "Send the end message seperately after sending all restaurant details\n");
  const char * end_message = "END";
  int bytes_sent;
  char ack[10];
  int valread;
  valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
  if (valread > 0) {
    ack[valread] = '\0';
    bytes_sent = send(client_socket, end_message, strlen(end_message), 0);
    sleep(1);
  }
  if (bytes_sent < 0) {
    debug_log(3, "Error sending end message for display restaurant\n");
    perror("Error sending END message");
  } else {
    debug_log(3, "End message sent for display restaurant\n");
    printf("End message sent.\n");
  }

  // Finalize the statement and close the database
  debug_log(2, "Close database for display restaurants function\n");
  sqlite3_finalize(stmt);

  sqlite3_close(db);

}
