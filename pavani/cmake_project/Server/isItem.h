#ifndef MENU_CHECK_H
#define MENU_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

int isItemInMenu(int restaurant_id, int item_id); // Declaration of isItemInMenu function

#endif /* MENU_CHECK_H */

