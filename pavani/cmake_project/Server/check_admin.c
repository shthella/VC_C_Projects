#include "check_admin.h"

int check_admin_credentials(int restaurant_id, char * username, char * password) {
  debug_log(2, "Entering to check admin credentials\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for checking admin credentials\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  char sql[500];
  // SQL statement to check admin credentials
  debug_log(3, "SQL query to check admin credentials\n");
  sprintf(sql, "SELECT COUNT(*) FROM admins WHERE restaurant_id = ? AND username = ? AND password = ?");

  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  sqlite3_bind_int(stmt, 1, restaurant_id);
  sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);

  int count = 0;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    count = sqlite3_column_int(stmt, 0);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  debug_log(3, "Close database after checking admin credentials\n");

  return count;
}
