#ifndef CALCULATE_OVERALL_SALES_H
#define CALCULATE_OVERALL_SALES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

#define DAILY 1
#define WEEKLY 2
#define MONTHLY 3

void calculate_overall_sales(int restaurant_id, int client_socket, int time_interval); // Declaration of calculate_overall_sales function

#endif /* CALCULATE_OVERALL_SALES_H */

