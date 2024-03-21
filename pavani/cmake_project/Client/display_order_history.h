#ifndef DISPLAY_ORDER_HISTORY_H
#define DISPLAY_ORDER_HISTORY_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug_log.h"
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "header_file.h"

// Function prototype for displaying order history
void display_order_history(int client_socket);

#endif /* DISPLAY_ORDER_HISTORY_H */

