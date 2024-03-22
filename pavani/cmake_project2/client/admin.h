#ifndef ADMIN_S_H
#define ADMIN_S_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include "display_menu.h"
#include "debug_log.h"
#include "helper_func.h"

// Function prototype for the admin interface
void admin_interface(int client_socket);
void add_item(int client_socket); // Function prototype for adding an item
void remove_item(int client_socket); // Function prototype for removing an item
void update_item(int client_socket); // Function prototype for updating an item
void display_order_history(int client_socket); // Function prototype for displaying order history
#endif /* ADMIN_S_H */

