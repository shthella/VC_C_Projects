#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/socket.h>
#include "debug_log.h" // Include the header file for debug logging
#include "add_restaurants.h" // Include the header file for adding restaurants
#include "display_restaurants.h" // Include the header file for displaying restaurants
#include "delete_restaurants.h" // Include the header file for deleting restaurants
#include "add_admin.h" // Include the header file for adding admin
#include "check_admin.h" // Include the header file for checking admin credentials
#include "add_item.h" // Include the header file for adding items
#include "remove_item.h" // Include the header file for removing items
#include "update_item.h" // Include the header file for updating items
#include "view_order_history.h" // Include the header file for viewing order history
#include "calculate_overall_sales.h" // Include the header file for calculating overall sales
#include "display_menu.h" // Include the header file for displaying menu

void admin_interface(int client_socket); // Declaration of admin_interface function

#endif /* ADMIN_INTERFACE_H */

