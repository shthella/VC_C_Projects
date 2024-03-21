#ifndef ADD_ITEM_H
#define ADD_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <sys/socket.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

void add_item(int client_socket, int restaurant_id); // Declaration of add_item function

#endif /* ADD_ITEM_H */

