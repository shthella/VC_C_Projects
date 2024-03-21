#ifndef ITEM_PRICE_H
#define ITEM_PRICE_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

double get_item_price(int restaurant_id, int item_id); // Declaration of get_item_price function

#endif /* ITEM_PRICE_H */

