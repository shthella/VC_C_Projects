#include "add_restaurants.h"

// Function to add restaurants into database
void handle_add_restaurant(int client_socket) {
  debug_log(2, "Handle add restaurants function\n");
  char name[100];
  char address[100];
  char contact_number[20];
  char message[2048];
  debug_log(2, "Variable creation for handle restaurant function\n");
  // Receive restaurant details from the client
  debug_log(3, "Receive restaurant details from the client\n");
  memset(name, 0, sizeof(name));
  memset(address, 0, sizeof(address));
  memset(contact_number, 0, sizeof(contact_number));

  // Send prompts to the client and receive inputs
  debug_log(3, "Sending prompts to the client and receive inputs\n");
  recv(client_socket, name, sizeof(name) - 1, 0);

  recv(client_socket, address, sizeof(address) - 1, 0);

  recv(client_socket, contact_number, sizeof(contact_number) - 1, 0);

  // Add restaurant logic
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open databse for handle add restaurant\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    debug_log(2, "Cannot open database for handle restaurant\n");
    sqlite3_close(db);

    // Send failure message to the client
    char * failureMsg = "Failed to add restaurant. Database error.";
    debug_log(3, "Failed to add restaurant. Database error\n");
    send(client_socket, failureMsg, strlen(failureMsg), 0);

    return;
  }

  char sql[1000];
  debug_log(3, "Insertion of restaurant details\n");
  sprintf(sql, "BEGIN TRANSACTION;"
    "INSERT INTO restaurants (name, address, contact_number) VALUES ('%s', '%s', '%s');"
    "COMMIT;", name, address, contact_number);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);

    // Send failure message to the client
    debug_log(3, "Failed to add restaurant. SQL error\n");
    char * failureMsg = "Failed to add restaurant. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);

  } else {
    // Send success message to the client

    printf("Restaurant added successfully.\n");
    char * successMsg = "Restaurant added successfully.";
    send(client_socket, successMsg, strlen(successMsg), 0);

  }
  debug_log(2, "Close database\n");
  sqlite3_close(db);
}
