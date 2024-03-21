#ifndef HANDLE_ADD_RESTAURANT_H
#define HANDLE_ADD_RESTAURANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/socket.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

void handle_add_restaurant(int client_socket); // Declaration of handle_add_restaurant function

#endif /* HANDLE_ADD_RESTAURANT_H */

