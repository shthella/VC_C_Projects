#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "remItem.h"
#include "database.h"

int item_exists(sqlite3 *db, int restaurant_id, int item_id) {
    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql, "SELECT COUNT(*) FROM menu_items WHERE id = %d AND restaurant_id = %d;", item_id, restaurant_id);
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1; // Error occurred
    }
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count;
}

int remove_item(int restaurant_id, int item_id) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Check if item exists
    int item_count = item_exists(db, restaurant_id, item_id);
    if (item_count == -1) {
        sqlite3_close(db);
        return 2; // Error occurred while checking existence
    } else if (item_count == 0) {
        fprintf(stdout, "Item not found in the database\n");
        sqlite3_close(db);
        return 3; // Item not found
    }

    char sql[200];
    sprintf(sql, "DELETE FROM menu_items WHERE id = %d AND restaurant_id = %d;", item_id, restaurant_id);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 4; // Error occurred during deletion
    } else {
        fprintf(stdout, "Item removed successfully\n");
        sqlite3_close(db);
        return 0; // Success
    }
}

