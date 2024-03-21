#ifndef CUSTOMER_INTERFACE_H
#define CUSTOMER_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "display_restaurants.h" // Include the header file for customer_restaurants function
#include "display_menu.h" // Include the header file for customer_menu function
#include "place_order.h" // Include the header file for place_order function
#include "debug_log.h" // Include the header file for debug logging

void customer_interface(int client_socket); // Declaration of customer_interface function

#endif /* CUSTOMER_INTERFACE_H */

