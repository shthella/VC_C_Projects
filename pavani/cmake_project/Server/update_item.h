#ifndef UPDATE_ITEM_H
#define UPDATE_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sqlite3.h>
#include "debug_log.h"
#include "database.h"

// Function to update an item in the menu
void update_item(int client_socket, int restaurant_id);

#endif /* UPDATE_ITEM_H */

