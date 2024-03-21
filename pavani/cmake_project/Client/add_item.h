#ifndef ADD_ITEM_H
#define ADD_ITEM_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug_log.h"
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "header_file.h"

// Function prototype for adding an item
int getInput(const char * prompt);
void add_item(int client_socket);


#endif /* ADD_ITEM_H */

