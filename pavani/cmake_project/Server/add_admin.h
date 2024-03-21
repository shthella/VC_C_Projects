#ifndef ADD_ADMIN_H
#define ADD_ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "debug_log.h"
#include "database.h"

void add_admin(int restaurant_id, char *username, char *password); // Declaration of add_admin function

#endif /* ADD_ADMIN_H */

