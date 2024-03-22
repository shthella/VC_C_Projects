#include "delete_rest.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

int handle_delete_restaurant(int restaurant_id) {
    // Open database connection
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1; // Return status code indicating failure
    }

    // Execute SQL statement to check if the restaurant ID exists
    char sql_check[100];
    sprintf(sql_check, "SELECT id FROM restaurants WHERE id = %d;", restaurant_id);

    rc = sqlite3_exec(db, sql_check, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1; // Return status code indicating failure
    }

    // If no rows are returned, the restaurant ID does not exist
    int exists = 0;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = 1;
        }
        sqlite3_finalize(stmt);
    }

    if (!exists) {
        sqlite3_close(db);
        return 1; // Return status code indicating restaurant ID not found
    }

    // Execute SQL statement to delete the restaurant
    char sql_delete[100];
    sprintf(sql_delete, "DELETE FROM restaurants WHERE id = %d;", restaurant_id);

    rc = sqlite3_exec(db, sql_delete, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1; // Return status code indicating failure
    }

    // Close database connection
    sqlite3_close(db);
    return 0; // Return status code indicating success
}

