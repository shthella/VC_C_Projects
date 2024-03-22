#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <sqlite3.h>
#include "database.h"
#include "get_customer_id.h" 
#include "T7.h"

// Function to print test results
void printest(int test_case_number, int test_number, int result) {
    if (result == 0) {
        printf("Test case TID%d_%d - passed\n", test_case_number, test_number);
    } else {
        printf("Test case TID%d_%d - failed\n", test_case_number, test_number);
    }
}

// Test cases for getCustomerIdFromDatabase function
void test_get_customer_id(sqlite3 *db) {
    // Test case 1: Test fetching customer ID for an existing customer
    const char *existing_customer_name = "ram";
    int customer_id = getCustomerIdFromDatabase(existing_customer_name);
    if (customer_id != -1) {
        printf("Customer ID for '%s': %d\n", existing_customer_name, customer_id);
    } else {
        printf("Customer '%s' not found in the database\n", existing_customer_name);
    }
    printest(1, 1, (customer_id != -1) ? 0 : 1);

    // Test case 2: Test fetching customer ID for a non-existing customer
    const char *non_existing_customer_name = "sita";
    customer_id = getCustomerIdFromDatabase(non_existing_customer_name);
    if (customer_id != -1) {
        printf("Customer ID for '%s': %d\n", non_existing_customer_name, customer_id);
    } else {
        printf("Customer '%s' not found in the database\n", non_existing_customer_name);
    }
    printest(1, 2, (customer_id == -1) ? 0 : 1);

    // Add more test cases as needed
}

