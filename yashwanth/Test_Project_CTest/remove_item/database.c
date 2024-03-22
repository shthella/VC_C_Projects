#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "database.h"

#define DATABASE "test.db"

void initialize_database() {
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    char *sql = 
        "CREATE TABLE restaurants ("           //restaurant table
        "id INTEGER PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "address TEXT,"
        "contact_number TEXT"
        ");"
        "CREATE TABLE admins ("                 //Admin table
        "id INTEGER PRIMARY KEY,"
        "restaurant_id INTEGER NOT NULL,"
        "username TEXT NOT NULL,"
        "password TEXT NOT NULL,"
        "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"      
        ");"
        "CREATE TABLE customers ("                //customer table
        "id INTEGER PRIMARY KEY,"
        "restaurant_id INTEGER NOT NULL,"
        "name TEXT NOT NULL,"
        "contact_number TEXT,"
        "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
        ");"
        "CREATE TABLE menu_items ("        //menu table
        "id INTEGER PRIMARY KEY,"
        "restaurant_id INTEGER NOT NULL,"
        "item_name TEXT NOT NULL,"
        "price REAL NOT NULL,"
        "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
        ");"
        "CREATE TABLE orders ("            //orders table
        "id INTEGER PRIMARY KEY,"
        "restaurant_id INTEGER NOT NULL,"
        "customer_id INTEGER NOT NULL,"
        "item_id INTEGER NOT NULL,"
        "quantity INTEGER NOT NULL,"
        "total_price REAL NOT NULL,"
        "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id),"
        "FOREIGN KEY (customer_id) REFERENCES customers(id),"
        "FOREIGN KEY (item_id) REFERENCES menu_items(id)"
        ");";
        
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Tables created successfully\n");
    }

    sqlite3_close(db);
}


