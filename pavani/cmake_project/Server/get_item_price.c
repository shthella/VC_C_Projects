#include "get_item_price.h"

double get_item_price(int restaurant_id, int item_id) {
  debug_log(2, "Getting item price from database\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;
  double price = -1; // Initialize price to -1 (indicating not found)

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database to fetch item price\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return price;
  }

  // Prepare SQL statement to select the price of the item based on its ID and restaurant ID
  debug_log(3, "SQL query to fetch item price from database\n");
  char * sql = "SELECT price FROM menu_items WHERE restaurant_id = ? AND id = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to open database to fetch item price\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return price;
  }

  // Bind the restaurant_id and item_id parameters to the prepared statement
  debug_log(3, "Bind the restauramnt_id and item_id parameters to the prepared statement\n");
  sqlite3_bind_int(stmt, 1, restaurant_id);

  sqlite3_bind_int(stmt, 2, item_id);

  // Execute the SQL statement
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Fetch the price of the item from the result set
    price = sqlite3_column_double(stmt, 0);

  }

  // Finalize the statement and close the database connection
  debug_log(2, "Close databse connection for fetching of item price\n");
  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return price;

}
