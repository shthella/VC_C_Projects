#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"
#include "display_menu.h"

#define DAILY 1
#define WEEKLY 2
#define MONTHLY 3

void admin_interface(int client_socket); // Declaration of admin_interface function
void handle_add_restaurant(int client_socket); // Declaration of handle_add_restaurant function
void handle_delete_restaurant(int client_socket); // Declaration of handle_delete_restaurant function
void add_admin(int restaurant_id, char *username, char *password); // Declaration of add_admin function
int check_admin_credentials(int restaurant_id, char * username, char * password); // Declaration of check_admin_credentials function
void add_item(int client_socket, int restaurant_id); // Declaration of add_item function
void remove_item(int client_socket, int restaurant_id); // Function to remove an item from the menu
void update_item(int client_socket, int restaurant_id); // Function to update an item in the menu
void view_order_history(int restaurant_id, int client_socket, int time_interval); // Function to view order history within a specified time interval
void calculate_overall_sales(int restaurant_id, int client_socket, int time_interval); // Declaration of calculate_overall_sales function
#endif /* ADMIN_INTERFACE_H */

