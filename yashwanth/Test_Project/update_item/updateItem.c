#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "updateItem.h"
#include "database.h"

int update_item(int restaurant_id, int item_id, char *item_name, float price) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;


    rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 2;
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    char sql[500];
    sprintf(sql, "UPDATE menu_items SET item_name = '%s', price = %f WHERE id = %d AND restaurant_id = %d;", item_name, price, item_id, restaurant_id);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    } else {
        fprintf(stdout, "Item updated successfully\n");
        return 0;
    }

    sqlite3_close(db);
}
