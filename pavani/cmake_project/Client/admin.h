#ifndef ADMIN_S_H
#define ADMIN_S_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include "display_restaurants.h"
#include "add_item.h"
#include "remove_item.h"
#include "update_item.h"
#include "display_menu.h"
#include "display_order_history.h"
#include "debug_log.h"
#include "clear_input_buffer.h"

// Function to clear input buffer
void clear_input_buffer();

// Function prototype for the admin interface
void admin_interface(int client_socket);

#endif /* ADMIN_S_H */

