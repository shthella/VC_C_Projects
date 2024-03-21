#include "view_order_history.h"

void view_order_history(int restaurant_id, int client_socket, int time_interval) {
  debug_log(2, "Entering to order history function\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for view order history function\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  // Get the current date
  debug_log(3, "According to time period\n");
  time_t t = time(NULL);
  struct tm * tm_info = localtime( & t);
  char current_date[20];
  strftime(current_date, sizeof(current_date), "%Y-%m-%d", tm_info);

  // Construct the appropriate date based on the time interval
  char start_date[20];
  if (time_interval == DAILY) {
    // For daily interval, start date is yesterday
    t -= 86400; // 86400 seconds in a day
    tm_info = localtime( & t);

    strftime(start_date, sizeof(start_date), "%Y-%m-%d", tm_info);

  } else if (time_interval == WEEKLY) {
    // For weekly interval, start date is 7 days ago
    t -= 7 * 86400; // 7 days * 86400 seconds/day
    tm_info = localtime( & t);

    strftime(start_date, sizeof(start_date), "%Y-%m-%d", tm_info);

  } else if (time_interval == MONTHLY) {
    // For monthly interval, start date is the first day of the current month
    strftime(start_date, sizeof(start_date), "%Y-%m-01", tm_info);

  }

  // Prepare SQL statement to retrieve order history within the specified time interval
  char sql[500];
  debug_log(3, "SQL query for view order history function\n");
  sprintf(sql, "SELECT * FROM orders WHERE restaurant_id = %d AND order_date BETWEEN '%s' AND '%s';", restaurant_id, start_date, current_date);

  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to execute query for view order history function\n");
    fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return;
  }

  // Send order history data to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send order history data to the client\n");
    // Extract data from the result row
    // Assuming the structure of the orders table, adjust as per your schema
    int order_id = sqlite3_column_int(stmt, 0);

    int customer_id = sqlite3_column_int(stmt, 2);

    int item_id = sqlite3_column_int(stmt, 3);

    int quantity = sqlite3_column_int(stmt, 4);

    double total_price = sqlite3_column_double(stmt, 5);

    // Create a message to send to the client
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    debug_log(3, "Creation of a message to sent to client\n");
    sprintf(buffer, "Order ID: %d, Customer ID: %d, Item ID: %d, Quantity: %d, Total Price: %.2f\n",
      order_id, customer_id, item_id, quantity, total_price);
    char ack[10];
    int valread;
    valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
    if (valread > 0) {
      ack[valread] = '\0';
      int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
      sleep(1);
    }

  }

  // Send an empty message to indicate the end of data
  debug_log(3, "Sending of end message for the order history display function\n");
  // Send the "END" message separately after sending all restaurant details
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
    debug_log(3, "Error e=sending end meesage for the view order function\n");
    perror("Error sending END message");
  } else {
    printf("End message sent.\n");
  }

  sqlite3_finalize(stmt);

  debug_log(2, "Close database for the view order function\n");
  sqlite3_close(db);

}
