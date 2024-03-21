#ifndef RECEIVE_MENU_H
#define RECEIVE_MENU_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "debug_log.h"

// Function prototype for receiving menu
void display_menu(int client_socket);

#endif /* RECEIVE_MENU_H */

