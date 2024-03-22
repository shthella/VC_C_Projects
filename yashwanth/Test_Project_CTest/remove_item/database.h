#ifndef DATABASE_H
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#define DATABASE_H
#define DATABASE "test.db"

void initialize_database();
void handle_sqlite_error(int rc, sqlite3 *db);
//int add_item(int restaurant_id, char *item_name, float price);
//int add_restaurant(char *name, char *address, char *contact_number);
int remove_item(int restaurant_id, int item_id);
//void test_additem(sqlite3 *db);
//void test_addrest(sqlite3 *db);
void test_remitem(sqlite3 *db);
void printest(int b, int n, int r);

#endif /* DATABASE_H */

