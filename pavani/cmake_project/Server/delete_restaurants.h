#ifndef HANDLE_DELETE_RESTAURANT_H
#define HANDLE_DELETE_RESTAURANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sqlite3.h> // Include SQLite3 header for database handling
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

void handle_delete_restaurant(int client_socket); // Declaration of handle_delete_restaurant function

#endif /* HANDLE_DELETE_RESTAURANT_H */

