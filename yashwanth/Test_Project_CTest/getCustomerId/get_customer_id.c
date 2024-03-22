#include "get_customer_id.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "database.h"
#include "get_customer_id.h"

int getCustomerIdFromDatabase(const char *name) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int customer_id = -1; // Initialize customer_id to -1 as an error indicator

    // Open database
    if (sqlite3_open(DATABASE, &db) == SQLITE_OK) {
        char sql[256];
        sprintf(sql, "SELECT id FROM customers WHERE name = '%s';", name);

        // Prepare SQL statement
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            // Execute SQL statement
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                // Retrieve customer_id from the result
                customer_id = sqlite3_column_int(stmt, 0);
            }
        }

        // Finalize statement and close database
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    return customer_id;
}

