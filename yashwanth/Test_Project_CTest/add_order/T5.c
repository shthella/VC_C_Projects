#include <stdio.h>
#include "add_order.h" 
#include "T5.h"
#include "database.h"
#include <stdlib.h>
#include <sqlite3.h>

#include <sys/socket.h>

void printest(int test_case_number, int test_number, int result) {
    if (result == 0) {
        printf("Test case TID%d_%d - passed\n", test_case_number, test_number);
    } else {
        printf("Test case TID%d_%d - failed\n", test_case_number, test_number);
    }
}

void test_add_order(sqlite3 *db) {
    int r1 = add_order_to_database(1, 100, 500, 3, 25.75); // Test valid data
    printest(1, 1, r1);

    int r2 = add_order_to_database(1, 100, 500, -3, 25.75); // Test invalid negative quantity
    printest(1, 2, r2);

    int r3 = add_order_to_database(1, 100, -500, 3, 25.75); // Test invalid negative item ID
    printest(1, 3, r3);

    int r4 = add_order_to_database(1, -100, 500, 3, 25.75); // Test invalid negative customer ID
    printest(1, 4, r4);

    int r5 = add_order_to_database(-1, 100, 500, 3, 25.75); // Test invalid negative restaurant ID
    printest(1, 5, r5);

    // Add more test cases as needed
}

