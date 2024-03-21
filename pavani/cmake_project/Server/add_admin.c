#include "add_admin.h"

void add_admin(int restaurant_id, char * username, char * password) {
  debug_log(2, "Entering to add admin function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for add admin\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  char sql[500];
  // Modified SQL statement to enforce uniqueness of restaurant_id and username combination
  debug_log(3, "SQL query to add admin\n");
  sprintf(sql, "INSERT INTO admins (restaurant_id, username, password) "
    "SELECT %d, '%s', '%s' "
    "WHERE NOT EXISTS (SELECT 1 FROM admins WHERE restaurant_id = %d AND username = '%s');",
    restaurant_id, username, password, restaurant_id, username);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "%s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    debug_log(3, "Admin added successfully\n");
    fprintf(stdout, "admin added successfully\n");

  }
  debug_log(2, "Close database for add admin\n");
  sqlite3_close(db);

}
