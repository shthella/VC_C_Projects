#include "calculate_overall_sales.h"

void calculate_overall_sales(int restaurant_id, int client_socket, int time_interval) {
  debug_log(2, "Entering calculate overall sales fucntion\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;
  double total_sales = 0.0;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open databse for calculation overall sales\n");
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

  // Prepare SQL statement to select total sales for the specified restaurant_id within the time interval
  debug_log(3, "SQL query to display overall sales\n");
  const char * sql = "SELECT SUM(total_price) FROM orders WHERE restaurant_id = ? AND order_date BETWEEN ? AND ?";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to prepare statement for overall sales\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return;
  }
  debug_log(3, "Binding the statement with requried parameters\n");
  // Bind the restaurant_id parameter to the prepared statement
  sqlite3_bind_int(stmt, 1, restaurant_id);

  // Bind the start_date parameter to the prepared statement
  sqlite3_bind_text(stmt, 2, start_date, -1, SQLITE_STATIC);

  // Bind the current_date parameter to the prepared statement
  sqlite3_bind_text(stmt, 3, current_date, -1, SQLITE_STATIC);

  // Execute the SQL statement
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Fetch the total sales from the result set
    debug_log(3, "Fetching the total sales\n");
    total_sales = sqlite3_column_double(stmt, 0);

  }

  // Create a message to send to the client
  debug_log(3, "Creation of message  to send to the client\n");
  char message[1024];
  memset(message, 0, sizeof(message));
  snprintf(message, sizeof(message), "Overall Sales for Restaurant %d within the specified time interval: $%.2f\n", restaurant_id, total_sales);
  printf("%s\n", message);

  // Send the message to the client
  int bytes_sent = send(client_socket, message, strlen(message), 0);
  if (bytes_sent < 0) {
    debug_log(3, "Error sending data for the view order history function\n");
    perror("Error sending data");

  }

  // Finalize the statement and close the database connection
  debug_log(2, "Close database for the overall sales history\n");
  sqlite3_finalize(stmt);

  sqlite3_close(db);

}
