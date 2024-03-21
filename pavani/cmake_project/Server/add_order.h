#ifndef ADD_ORDER_TO_DATABASE_H
#define ADD_ORDER_TO_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

void add_order_to_database(int restaurant_id, int customer_id, int item_id, int quantity, double total_price); // Declaration of add_order_to_database function

#endif /* ADD_ORDER_TO_DATABASE_H */

