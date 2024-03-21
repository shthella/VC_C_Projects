#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "addrest.h"
#include "database.h"

int add_restaurant(char *name, char *address, char *contact_number) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
      
    rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

   char sql[1000];
    sprintf(sql, "BEGIN TRANSACTION;"
                 "INSERT INTO restaurants (name, address, contact_number) VALUES ('%s', '%s', '%s');"
                 "COMMIT;", name, address, contact_number);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        return 1;
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Restaurant added successfully\n");
        return 0;
    }

    sqlite3_close(db);
}
