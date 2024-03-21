#include "isItem.h"

// Function to check if an item exists in the menu for a given restaurant
int isItemInMenu(int restaurant_id, int item_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open the SQLite database
    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0; // Return false (0) indicating item not found due to database error
    }

    // Prepare the SQL statement to check if the item exists in the menu
    const char *sql = "SELECT COUNT(*) FROM menu_items WHERE restaurant_id = ? AND id = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0; // Return false (0) indicating item not found due to SQL error
    }

    // Bind the restaurant_id and item_id parameters to the prepared statement
    sqlite3_bind_int(stmt, 1, restaurant_id);
    sqlite3_bind_int(stmt, 2, item_id);

    // Execute the SQL statement
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0); // Get the count of rows returned
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // If count > 0, the item exists in the menu; otherwise, it does not
    return count > 0;
}
