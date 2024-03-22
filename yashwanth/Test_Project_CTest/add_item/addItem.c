#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "addItem.h"
#include "database.h"

int add_item(int restaurant_id, char *item_name, float price) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open(DATABASE, &db);
   

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            return 1;
            sqlite3_close(db);
            exit(EXIT_FAILURE);
        }
    char sql[500];
    sprintf(sql, "INSERT INTO menu_items (restaurant_id, item_name, price) VALUES (%d, '%s', %f);", restaurant_id, item_name, price);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 2;
    } else {
        fprintf(stdout, "Item added successfully\n");
        return 0; 
    }

    sqlite3_close(db);
}
