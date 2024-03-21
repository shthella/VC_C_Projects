#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sqlite3.h> // Include SQLite3 header for database handling
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"
#include <unistd.h>

void display_menu(int client_socket, int restaurant_id); // Declaration of display_menu function

#endif /* DISPLAY_MENU_H */

