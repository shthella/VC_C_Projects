#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

//#include "addrest.h"
//#include "T1.h"
#include "addItem.h"
#include "T2.h"
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
		"CREATE TABLE restaurants ("
		    "id INTEGER PRIMARY KEY CHECK (id > 0),"
		    "name TEXT NOT NULL,"
		    "address TEXT NOT NULL,"
		    "contact_number TEXT NOT NULL"
		");"
		"CREATE TABLE admins ("
		    "id INTEGER PRIMARY KEY CHECK (id > 0),"
		    "restaurant_id INTEGER NOT NULL,"
		    "username TEXT NOT NULL,"
		    "password TEXT NOT NULL,"
		    "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
		");"
		"CREATE TABLE customers ("
		    "id INTEGER PRIMARY KEY CHECK (id > 0),"
		    "restaurant_id INTEGER NOT NULL,"
		    "name TEXT NOT NULL,"
		    "contact_number TEXT NOT NULL,"
		    "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
		");"
		"CREATE TABLE menu_items ("
		    "id INTEGER PRIMARY KEY CHECK (id > 0),"
		    "restaurant_id INTEGER NOT NULL,"
		    "item_name TEXT NOT NULL,"
		    "price REAL NOT NULL CHECK (price >= 0)," 
		    "UNIQUE (restaurant_id, item_name),"
		    "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
		");"
		"CREATE TABLE orders ("
		    "id INTEGER PRIMARY KEY CHECK (id > 0),"
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
// Function to handle SQLite3 errors
void handle_sqlite_error(int rc, sqlite3 *db) {
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
}

int main() {
	initialize_database();
	sqlite3_stmt *stmt;
	const char *sql;
	int rc;
	char input[100]; 
	int serverSocket;
	// Open database connection
	rc = sqlite3_open("test.db", &db);
	handle_sqlite_error(rc, db);
	sqlite3_db_config(db, SQLITE_DBCONFIG_LOOKASIDE, 512, 32);
	
	//test_addrest(db);
	test_additem(db);
	return 0;
}
