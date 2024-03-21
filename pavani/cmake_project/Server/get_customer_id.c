#include "get_customer_id.h"

int getCustomerIdFromDatabase(const char * name) {
  debug_log(2, "Fetching customer_id from database\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int customer_id = -1; // Initialize customer_id to -1 as an error indicator

  // Open database
  debug_log(2, "Open database for fetching customer_id\n");
  if (sqlite3_open(DATABASE, & db) == SQLITE_OK) {
    char sql[256];
    debug_log(3, "SQL query for fetching the customer_id\n");
    sprintf(sql, "SELECT id FROM customers WHERE name = '%s';", name);

    // Prepare SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, & stmt, NULL) == SQLITE_OK) {
      // Execute SQL statement
      if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Retrieve customer_id from the result
        debug_log(3, "Retrieve customer_id from the result\n");
        customer_id = sqlite3_column_int(stmt, 0);

      }
    }

    // Finalize statement and close database
    debug_log(2, "Close database for fetching customer_id\n");
    sqlite3_finalize(stmt);
    sqlite3_close(db);

  }

  return customer_id;

}
