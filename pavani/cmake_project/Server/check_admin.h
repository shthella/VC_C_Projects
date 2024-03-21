#ifndef CHECK_ADMIN_CREDENTIALS_H
#define CHECK_ADMIN_CREDENTIALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

int check_admin_credentials(int restaurant_id, char * username, char * password); // Declaration of check_admin_credentials function

#endif /* CHECK_ADMIN_CREDENTIALS_H */

