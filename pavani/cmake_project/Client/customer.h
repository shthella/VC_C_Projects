#ifndef CUSTOMER_INTERFACE_H
#define CUSTOMER_INTERFACE_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "debug_log.h"
#include "display_restaurants.h"
#include "display_menu.h"
#include "place_order.h"
#include "header_file.h"
#include "clear_input_buffer.h"

// Function prototype for customer_interface function
void customer_interface(int client_socket);

#endif /* CUSTOMER_INTERFACE_H */

