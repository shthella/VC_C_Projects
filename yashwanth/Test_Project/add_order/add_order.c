#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "database.h"
#include "add_order.h"

// Function to add an order to the database
int add_order_to_database(int restaurant_id, int customer_id, int item_id, int quantity, double total_price) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open the database connection
    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1; // Return 1 to indicate failure
    }

    char sql[500];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (restaurant_id, customer_id, item_id, quantity, total_price) VALUES (%d, %d, %d, %d, %.2f);",
             restaurant_id, customer_id, item_id, quantity, total_price);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 2; // Return 2 to indicate failure
    } else {
        printf("Order added to the database successfully.\n");
        sqlite3_close(db);
        return 0; // Return 0 to indicate success
    }
}


