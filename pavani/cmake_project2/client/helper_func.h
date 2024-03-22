#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#include <stdio.h>
#include <string.h>
#include "debug_log.h"
#include <sys/socket.h>   // Include necessary standard libraries

// Function prototypes
void clear_input_buffer();
void send_message(int client_socket, const char * message);
int getInput(const char * prompt);

#endif /* HEADER_FILE_H */

