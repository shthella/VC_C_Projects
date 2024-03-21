#ifndef REMOVE_ITEM_H
#define REMOVE_ITEM_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug_log.h"
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "header_file.h"

// Function prototype for removing an item
void remove_item(int client_socket);

#endif /* REMOVE_ITEM_H */

