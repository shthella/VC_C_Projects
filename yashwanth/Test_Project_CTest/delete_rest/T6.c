#include "T6.h" 
#include "delete_rest.h"
#include "database.h"
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <sqlite3.h>

void printest(int test_case_number, int test_number, int result) {
    if (result == 0) {
        printf("Test case TID%d_%d - passed\n", test_case_number, test_number);
    } else {
        printf("Test case TID%d_%d - failed\n", test_case_number, test_number);
    }
}

void test_delete_restaurant(sqlite3 *db) {
    // Test case: Test deleting a valid restaurant
    int r1 = handle_delete_restaurant(1);
    printest(1, 1, r1);

    // Test case: Test deleting a non-existing restaurant
    int r2 = handle_delete_restaurant(9999);
    printest(1, 2, r2);

    // Add more test cases as needed
}

