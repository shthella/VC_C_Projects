#ifndef CUSTOMER_ID_H
#define CUSTOMER_ID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

int getCustomerIdFromDatabase(const char * name); // Declaration of getCustomerIdFromDatabase function

#endif /* CUSTOMER_ID_H */

