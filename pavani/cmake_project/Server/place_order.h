#ifndef PLACE_ORDER_H
#define PLACE_ORDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>
#include "get_customer_id.h"
#include "get_item_price.h"
#include "isItem.h"
#include "add_order.h"
#include "generate_invoice.h"
#include "debug_log.h"
#include "ordered_item.h"

// Function to place an order
void place_order(int client_socket, int restaurant_id);

#endif /* PLACE_ORDER_H */

