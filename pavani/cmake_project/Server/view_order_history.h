#ifndef VIEW_ORDER_HISTORY_H
#define VIEW_ORDER_HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sys/socket.h> 
#include <time.h>
#include "debug_log.h"
#include "database.h"

#define DAILY 1
#define WEEKLY 2
#define MONTHLY 3

// Function to view order history within a specified time interval
void view_order_history(int restaurant_id, int client_socket, int time_interval);

#endif /* VIEW_ORDER_HISTORY_H */

