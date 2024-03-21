#ifndef UPDATE_ITEM_H
#define UPDATE_ITEM_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug_log.h"
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "header_file.h"

// Function prototype for updating an item
void update_item(int client_socket);

#endif /* UPDATE_ITEM_H */

