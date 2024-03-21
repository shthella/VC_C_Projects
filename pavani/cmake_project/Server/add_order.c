#include "add_order.h"

void add_order_to_database(int restaurant_id, int customer_id, int item_id, int quantity, double total_price) {
  debug_log(2, "Add order details to databse\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for Add order details\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  char sql[500];
  debug_log(3, "SQL query to add order details to database\n");
  sprintf(sql, "INSERT INTO orders (restaurant_id, customer_id, item_id, quantity, total_price) VALUES (%d, %d, %d, %d, %.2f);",
    restaurant_id, customer_id, item_id, quantity, total_price);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for add order details to database\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

  } else {
    printf("Order added to the database successfully.\n");
  }
  debug_log(2, "Close database for adding order details\n");
  sqlite3_close(db);

}
