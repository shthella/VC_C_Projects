#ifndef CUSTOMER_INTERFACE_H
#define CUSTOMER_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sqlite3.h>
#include "database.h"
#include "ordered_item.h"
#include "debug_log.h"
#include "display_menu.h"

void customer_interface(int client_socket); // Declaration of customer_interface function
void place_order(int client_socket, int restaurant_id); // Function to place an order
int getCustomerIdFromDatabase(const char * name); // Declaration of getCustomerIdFromDatabase function
double get_item_price(int restaurant_id, int item_id); // Declaration of get_item_price function
double get_item_price(int restaurant_id, int item_id); // Declaration of get_item_price function
void add_order_to_database(int restaurant_id, int customer_id, int item_id, int quantity, double total_price); // Declaration of add_order_to_database function
void generate_invoice(int client_socket, OrderedItem ordered_items[], int num_items); // Declaration of generate_invoice function
#endif /* CUSTOMER_INTERFACE_H */

