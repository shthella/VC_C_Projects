#ifndef REMOVE_ITEM_H
#define REMOVE_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sqlite3.h>
#include "debug_log.h"
#include "database.h"

// Function to remove an item from the menu
void remove_item(int client_socket, int restaurant_id);

#endif /* REMOVE_ITEM_H */

