#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "database.h"
//#include "addrest.h"
//#include "T1.h"
//#include "addItem.h"
//#include "T2.h"
//#include "remItem.h"
//#include "T3.h"
//#include "updateItem.h"
//#include "T4.h"
#include "T5.h"
#include "add_order.h"
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
        "CREATE TABLE restaurants ("
            "id INTEGER PRIMARY KEY,"
            "name TEXT NOT NULL,"
            "address TEXT NOT NULL,"
            "contact_number TEXT NOT NULL"
        ");"
        "CREATE TABLE admins ("
            "id INTEGER PRIMARY KEY,"
            "restaurant_id INTEGER NOT NULL,"
            "username TEXT NOT NULL,"
            "password TEXT NOT NULL,"
            "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
        ");"
        "CREATE TABLE customers ("
            "id INTEGER PRIMARY KEY,"
            "restaurant_id INTEGER NOT NULL,"
            "name TEXT NOT NULL,"
            "contact_number TEXT NOT NULL,"
            "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
        ");"
        "CREATE TABLE menu_items ("
            "id INTEGER PRIMARY KEY,"
            "restaurant_id INTEGER NOT NULL,"
            "item_name TEXT NOT NULL,"
            "price REAL NOT NULL CHECK (price >= 0)," 
            "UNIQUE (restaurant_id, item_name),"
            "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
        ");"
        "CREATE TABLE orders ("
            "id INTEGER PRIMARY KEY,"
            "restaurant_id INTEGER NOT NULL,"
            "customer_id INTEGER NOT NULL,"
            "item_id INTEGER NOT NULL,"
            "quantity INTEGER NOT NULL CHECK (quantity > 0)," 
            "total_price REAL NOT NULL CHECK (total_price >= 0), "
            "order_date DATE DEFAULT CURRENT_DATE,"
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
sqlite3 *db;
int main() {
    initialize_database();
    sqlite3_stmt *stmt;
    const char *sql;
    int rc;
    rc = sqlite3_open("test.db", &db);
    sqlite3_db_config(db, SQLITE_DBCONFIG_LOOKASIDE, 512, 32);
    // Run test cases for add_order function
    test_add_order(db); 
    //test_delete_restaurant(db);
    //test_get_customer_id();
    	//test_addrest(db);
	//test_additem(db);
	//test_remitem(db);
	//test_updateItem(db);
    return 0;
}

