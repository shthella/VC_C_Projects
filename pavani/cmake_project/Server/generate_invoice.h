#ifndef GENERATE_INVOICE_H
#define GENERATE_INVOICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "debug_log.h" // Include the header file for debug logging
#include "ordered_item.h"

void generate_invoice(int client_socket, OrderedItem ordered_items[], int num_items); // Declaration of generate_invoice function

#endif /* GENERATE_INVOICE_H */

