#include "admin_s.h"

void handle_add_restaurant(int client_socket) {
  debug_log(2, "Handle add restaurants function\n");
  char name[100];
  char address[100];
  char contact_number[20];
  char message[2048];
  debug_log(2, "Variable creation for handle restaurant function\n");
  // Receive restaurant details from the client
  debug_log(3, "Receive restaurant details from the client\n");
  memset(name, 0, sizeof(name));
  memset(address, 0, sizeof(address));
  memset(contact_number, 0, sizeof(contact_number));

  // Send prompts to the client and receive inputs
  debug_log(3, "Sending prompts to the client and receive inputs\n");
  recv(client_socket, name, sizeof(name) - 1, 0);

  recv(client_socket, address, sizeof(address) - 1, 0);

  recv(client_socket, contact_number, sizeof(contact_number) - 1, 0);

  // Add restaurant logic
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open databse for handle add restaurant\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    debug_log(2, "Cannot open database for handle restaurant\n");
    sqlite3_close(db);

    // Send failure message to the client
    char * failureMsg = "Failed to add restaurant. Database error.";
    debug_log(3, "Failed to add restaurant. Database error\n");
    send(client_socket, failureMsg, strlen(failureMsg), 0);

    return;
  }

  char sql[1000];
  debug_log(3, "Insertion of restaurant details\n");
  sprintf(sql, "BEGIN TRANSACTION;"
    "INSERT INTO restaurants (name, address, contact_number) VALUES ('%s', '%s', '%s');"
    "COMMIT;", name, address, contact_number);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);

    // Send failure message to the client
    debug_log(3, "Failed to add restaurant. SQL error\n");
    char * failureMsg = "Failed to add restaurant. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);

  } else {
    // Send success message to the client

    printf("Restaurant added successfully.\n");
    char * successMsg = "Restaurant added successfully.";
    send(client_socket, successMsg, strlen(successMsg), 0);

  }
  debug_log(2, "Close database\n");
  sqlite3_close(db);
}

void handle_delete_restaurant(int client_socket) {
  debug_log(2, "Entering handle_delete_restaurant function\n");
  char restaurant_id_str[20];
  int restaurant_id;
  char response[100];

  // Receive restaurant ID from the client
  debug_log(3, "Receiving restaurant ID from client\n");
  recv(client_socket, restaurant_id_str, sizeof(restaurant_id_str), 0);
  restaurant_id = atoi(restaurant_id_str);

  // Remove the restaurant from the database
  debug_log(3, "Remove restaurant from the database\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for deleting restaurant\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    // Send failure message to the client
    char * failureMsg = "Failed to delete restaurant. Database error.";
    debug_log(3, "Failed to delete restaurant. Database error\n");
    send(client_socket, failureMsg, strlen(failureMsg), 0);
    return;
  }

  // Execute SQL statement to delete the restaurant
  char sql[100];
  sprintf(sql, "DELETE FROM restaurants WHERE id = %d;", restaurant_id);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for deleting restaurant\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);

    // Send failure message to the client
    debug_log(3, "Failed to delete restaurant. SQL error\n");
    char * failureMsg = "Failed to delete restaurant. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);
    return;
  }

  // Send success message to the client
  debug_log(3, "Restaurant deleted successfully\n");
  char * successMsg = "Restaurant deleted successfully.";
  printf("Restaurant deleted successfully.\n");
  send(client_socket, successMsg, strlen(successMsg), 0);

  // Close database
  debug_log(2, "Close database after deleting restaurant\n");
  sqlite3_close(db);
 
}

void add_admin(int restaurant_id, char * username, char * password) {
  debug_log(2, "Entering to add admin function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for add admin\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  char sql[500];
  // Modified SQL statement to enforce uniqueness of restaurant_id and username combination
  debug_log(3, "SQL query to add admin\n");
  sprintf(sql, "INSERT INTO admins (restaurant_id, username, password) "
    "SELECT %d, '%s', '%s' "
    "WHERE NOT EXISTS (SELECT 1 FROM admins WHERE restaurant_id = %d AND username = '%s');",
    restaurant_id, username, password, restaurant_id, username);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "%s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    debug_log(3, "Admin added successfully\n");
    fprintf(stdout, "admin added successfully\n");

  }
  debug_log(2, "Close database for add admin\n");
  sqlite3_close(db);

}

int check_admin_credentials(int restaurant_id, char * username, char * password) {
  debug_log(2, "Entering to check admin credentials\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for checking admin credentials\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  char sql[500];
  // SQL statement to check admin credentials
  debug_log(3, "SQL query to check admin credentials\n");
  sprintf(sql, "SELECT COUNT(*) FROM admins WHERE restaurant_id = ? AND username = ? AND password = ?");

  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  sqlite3_bind_int(stmt, 1, restaurant_id);
  sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);

  int count = 0;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    count = sqlite3_column_int(stmt, 0);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  debug_log(3, "Close database after checking admin credentials\n");

  return count;
}

void add_item(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to add item function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  // Open database
  debug_log(2, "Open database to add item\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database to add item\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  // Receive number of items to add
  int num_items;
  debug_log(3, "Receive number of items to add\n");
  recv(client_socket, & num_items, sizeof(num_items), 0);

  // Loop to receive and insert item details
  for (int i = 0; i < num_items; i++) {
    char item_name[100];
    float price;

    // Receive item name
    recv(client_socket, item_name, sizeof(item_name), 0);

    // Receive item price
    recv(client_socket, & price, sizeof(price), 0);

    // Insert item into the database
    char sql[500];
    debug_log(3, "SQL query to add item\n");
    sprintf(sql, "INSERT INTO menu_items (restaurant_id, item_name, price) VALUES (%d, '%s', %f);", restaurant_id, item_name, price);
    rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

    if (rc != SQLITE_OK) {
      if (strstr(zErrMsg, "UNIQUE constraint failed")) {
        // Send message to client indicating item already exists
        debug_log(3, "Item already exists\n");
        char message[] = "Item already exists in the menu\n";
        // send(client_socket, message, strlen(message), 0);

      } else {
        debug_log(3, "SQL error for add item\n");
        fprintf(stderr, "SQL error: %s\n", zErrMsg);

      }
      sqlite3_free(zErrMsg);
    } else {
      debug_log(3, "Item added successfully\n");
      fprintf(stdout, "Item added successfully\n");

    }
  }

  // Close database
  debug_log(2, "Close databse for add item\n");
  sqlite3_close(db);

}

void remove_item(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to remove item function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  // Open database
  debug_log(2, "Open database for remove item\n");
  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for remove item\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  // Receive item ID to be removed
  int item_id;
  debug_log(3, "Receiving item_id to remove\n");
  recv(client_socket, & item_id, sizeof(item_id), 0);

  // Prepare SQL statement to delete the item
  char sql[500];
  debug_log(3, "SQL query to remove item\n");
  sprintf(sql, "DELETE FROM menu_items WHERE id = %d AND restaurant_id = %d;", item_id, restaurant_id);

  // Execute the SQL statement
  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for remove item\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

    // Send failure message to the client
    debug_log(3, "Failed to remove item. SQL error\n");
    char * failureMsg = "Failed to remove item. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);

  } else {
    // Send success message to the client
    debug_log(3, "Item removed successfully\n");
    printf("Item removed successfully\n");
    char * successMsg = "Item removed successfully.";
    send(client_socket, successMsg, strlen(successMsg), 0);

  }

  // Close database
  debug_log(2, "Close database for remove item\n");
  sqlite3_close(db);

}

void update_item(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to update item function\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  // Open database
  debug_log(2, "Open databse for update item\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for update item\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);

  }

  // Receive updated item details from the client
  int item_id;
  char item_name[100];
  float price;

  recv(client_socket, & item_id, sizeof(item_id), 0);
  recv(client_socket, item_name, sizeof(item_name), 0);
  recv(client_socket, & price, sizeof(price), 0);

  // Prepare SQL statement to update the item
  char sql[500];
  debug_log(3, "SQL query for update item\n");
  sprintf(sql, "UPDATE menu_items SET item_name = '%s', price = %f WHERE id = %d AND restaurant_id = %d;", item_name, price, item_id, restaurant_id);

  // Execute the SQL statement
  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for update item\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

    // Send failure message to the client
    debug_log(3, "Failed to update item. SQL error\n");
    char * failureMsg = "Failed to update item. SQL error.";
    send(client_socket, failureMsg, strlen(failureMsg), 0);

  } else {
    // Send success message to the client
    debug_log(3, "Item updated successfully\n");
    printf("Item updated successfully\n");
    char * successMsg = "Item updated successfully.";
    send(client_socket, successMsg, strlen(successMsg), 0);

  }

  // Close database
  debug_log(2, "Close database\n");
  sqlite3_close(db);

}

void view_order_history(int restaurant_id, int client_socket, int time_interval) {
  debug_log(2, "Entering to order history function\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for view order history function\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  // Get the current date
  debug_log(3, "According to time period\n");
  time_t t = time(NULL);
  struct tm * tm_info = localtime( & t);
  char current_date[20];
  strftime(current_date, sizeof(current_date), "%Y-%m-%d", tm_info);

  // Construct the appropriate date based on the time interval
  char start_date[20];
  if (time_interval == DAILY) {
    // For daily interval, start date is yesterday
    t -= 86400; // 86400 seconds in a day
    tm_info = localtime( & t);

    strftime(start_date, sizeof(start_date), "%Y-%m-%d", tm_info);

  } else if (time_interval == WEEKLY) {
    // For weekly interval, start date is 7 days ago
    t -= 7 * 86400; // 7 days * 86400 seconds/day
    tm_info = localtime( & t);

    strftime(start_date, sizeof(start_date), "%Y-%m-%d", tm_info);

  } else if (time_interval == MONTHLY) {
    // For monthly interval, start date is the first day of the current month
    strftime(start_date, sizeof(start_date), "%Y-%m-01", tm_info);

  }

  // Prepare SQL statement to retrieve order history within the specified time interval
  char sql[500];
  debug_log(3, "SQL query for view order history function\n");
  sprintf(sql, "SELECT * FROM orders WHERE restaurant_id = %d AND order_date BETWEEN '%s' AND '%s';", restaurant_id, start_date, current_date);

  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to execute query for view order history function\n");
    fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return;
  }

  // Send order history data to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send order history data to the client\n");
    // Extract data from the result row
    // Assuming the structure of the orders table, adjust as per your schema
    int order_id = sqlite3_column_int(stmt, 0);

    int customer_id = sqlite3_column_int(stmt, 2);

    int item_id = sqlite3_column_int(stmt, 3);

    int quantity = sqlite3_column_int(stmt, 4);

    double total_price = sqlite3_column_double(stmt, 5);

    // Create a message to send to the client
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    debug_log(3, "Creation of a message to sent to client\n");
    sprintf(buffer, "Order ID: %d, Customer ID: %d, Item ID: %d, Quantity: %d, Total Price: %.2f\n",
      order_id, customer_id, item_id, quantity, total_price);
    char ack[10];
    int valread;
    valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
    if (valread > 0) {
      ack[valread] = '\0';
      int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
      sleep(1);
    }

  }

  // Send an empty message to indicate the end of data
  debug_log(3, "Sending of end message for the order history display function\n");
  // Send the "END" message separately after sending all restaurant details
  const char * end_message = "END";
  int bytes_sent;
  char ack[10];
  int valread;
  valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
  if (valread > 0) {
    ack[valread] = '\0';
    bytes_sent = send(client_socket, end_message, strlen(end_message), 0);
    sleep(1);
  }
  if (bytes_sent < 0) {
    debug_log(3, "Error e=sending end meesage for the view order function\n");
    perror("Error sending END message");
  } else {
    printf("End message sent.\n");
  }

  sqlite3_finalize(stmt);

  debug_log(2, "Close database for the view order function\n");
  sqlite3_close(db);

}

void calculate_overall_sales(int restaurant_id, int client_socket, int time_interval) {
  debug_log(2, "Entering calculate overall sales fucntion\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;
  double total_sales = 0.0;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open databse for calculation overall sales\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  // Get the current date
  debug_log(3, "According to time period\n");
  time_t t = time(NULL);
  struct tm * tm_info = localtime( & t);
  char current_date[20];
  strftime(current_date, sizeof(current_date), "%Y-%m-%d", tm_info);

  // Construct the appropriate date based on the time interval
  char start_date[20];
  if (time_interval == DAILY) {
    // For daily interval, start date is yesterday
    t -= 86400; // 86400 seconds in a day
    tm_info = localtime( & t);
    strftime(start_date, sizeof(start_date), "%Y-%m-%d", tm_info);

  } else if (time_interval == WEEKLY) {
    // For weekly interval, start date is 7 days ago
    t -= 7 * 86400; // 7 days * 86400 seconds/day
    tm_info = localtime( & t);
    strftime(start_date, sizeof(start_date), "%Y-%m-%d", tm_info);

  } else if (time_interval == MONTHLY) {
    // For monthly interval, start date is the first day of the current month
    strftime(start_date, sizeof(start_date), "%Y-%m-01", tm_info);

  }

  // Prepare SQL statement to select total sales for the specified restaurant_id within the time interval
  debug_log(3, "SQL query to display overall sales\n");
  const char * sql = "SELECT SUM(total_price) FROM orders WHERE restaurant_id = ? AND order_date BETWEEN ? AND ?";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to prepare statement for overall sales\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return;
  }
  debug_log(3, "Binding the statement with requried parameters\n");
  // Bind the restaurant_id parameter to the prepared statement
  sqlite3_bind_int(stmt, 1, restaurant_id);

  // Bind the start_date parameter to the prepared statement
  sqlite3_bind_text(stmt, 2, start_date, -1, SQLITE_STATIC);

  // Bind the current_date parameter to the prepared statement
  sqlite3_bind_text(stmt, 3, current_date, -1, SQLITE_STATIC);

  // Execute the SQL statement
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Fetch the total sales from the result set
    debug_log(3, "Fetching the total sales\n");
    total_sales = sqlite3_column_double(stmt, 0);

  }

  // Create a message to send to the client
  debug_log(3, "Creation of message  to send to the client\n");
  char message[1024];
  memset(message, 0, sizeof(message));
  snprintf(message, sizeof(message), "Overall Sales for Restaurant %d within the specified time interval: $%.2f\n", restaurant_id, total_sales);
  printf("%s\n", message);

  // Send the message to the client
  int bytes_sent = send(client_socket, message, strlen(message), 0);
  if (bytes_sent < 0) {
    debug_log(3, "Error sending data for the view order history function\n");
    perror("Error sending data");

  }

  // Finalize the statement and close the database connection
  debug_log(2, "Close database for the overall sales history\n");
  sqlite3_finalize(stmt);

  sqlite3_close(db);

}

void admin_interface(int client_socket) {
  // Implement the admin interface logic here
  debug_log(1, "Entering to admin interface\n");
  char message[1024];
  int choice;
  do {
    debug_log(2, "Receive of choice from admin\n");
    memset(message, 0, sizeof(message));
    recv(client_socket, message, sizeof(message) - 1, 0);

    choice = atoi(message);
    printf("Admin Choice: %d\n", choice);

    switch (choice) {
    case 1:
      debug_log(3, "Call of handle add restaurant function\n");
      handle_add_restaurant(client_socket);
      break;

    case 2:
      debug_log(3, "Call of display restaurants function\n");
      display_restaurants(client_socket);
      break;

    case 3:
      debug_log(3, "Call of delete restaurants function\n");
      handle_delete_restaurant(client_socket);
      break;

    case 4:
      int restaurant_id;
      debug_log(2, "Receive of restaurant_id from admin\n");
      recv(client_socket, message, sizeof(message) - 1, 0);

      restaurant_id = atoi(message);
      char username[50], password[50];
      recv(client_socket, username, sizeof(username) - 1, 0);

      recv(client_socket, password, sizeof(password) - 1, 0);
      add_admin(restaurant_id, username, password);
      break;
    case 5:

      debug_log(2, "Receive of restaurant_id from admin\n");
      recv(client_socket, message, sizeof(message) - 1, 0);

      restaurant_id = atoi(message);

      debug_log(3, "Receive of admin username and password\n");
      retry:
        recv(client_socket, username, sizeof(username) - 1, 0);

      recv(client_socket, password, sizeof(password) - 1, 0);

      debug_log(3, "Add admin function to add admin details to database\n");
      if (check_admin_credentials(restaurant_id, username, password)) {
        printf("Credentials are correct. Admin authenticated.\n");
        char * successMsg = "Credentials are correct. Admin authenticated.";
        send(client_socket, successMsg, strlen(successMsg), 0);

        int b;
        do {
          debug_log(2, "Choice for admin tasks\n");
          memset(message, 0, sizeof(message));
          recv(client_socket, message, sizeof(message) - 1, 0);

          b = atoi(message);
          printf("Admin Tasks: %d", b);
          switch (b) {
          case 1:
            debug_log(3, "Call of add item function\n");
            add_item(client_socket, restaurant_id);

            debug_log(3, "Call of display menu function\n");
            display_menu(client_socket, restaurant_id);

            break;
          case 2:
            debug_log(3, "Call of remove item function\n");
            remove_item(client_socket, restaurant_id);

            break;

          case 3:
            debug_log(3, "Call of update item function\n");
            update_item(client_socket, restaurant_id);

            break;
          case 4:
            // Receive time interval request from client
            debug_log(3, "Receive time interval request from client for view order history\n");
            int time_interval;
            recv(client_socket, & time_interval, sizeof(time_interval), 0);

            // Call view_order_history function with the requested time interval
            debug_log(3, "Call of view order history function\n");
            view_order_history(restaurant_id, client_socket, time_interval);

            break;
          case 5:
            debug_log(3, "Receive time interval request from client for calculate overall sales history\n");
            recv(client_socket, & time_interval, sizeof(time_interval), 0);

            debug_log(3, "Call of overall sales history function\n");
            calculate_overall_sales(restaurant_id, client_socket, time_interval);

            break;
          case 6:
            debug_log(3, "Call of display menu function\n");
            display_menu(client_socket, restaurant_id);

            break;
          case 7:
            debug_log(3, "Exit from admin tasks\n");
            printf("Exiting..\n");

            break;
          default:
            debug_log(3, "Invalid choice\n");
            printf("Invalid Choice\n");
            break;

          }
        } while (b != 7);
      } else {
        printf("Invalid credentials. Admin not authenticated.\n");
        char * successMsg = "Invalid credentials. Admin not authenticated.";
        send(client_socket, successMsg, strlen(successMsg), 0);
        printf("Retry: \n");
        goto retry;
      }

      break;
    case 6:
      printf("Exiting....\n");
      break;
    default:
      // Invalid choice
      debug_log(3, "Invalid choice\n");
      printf("Invalid choice \n");

    }
  } while (choice != 6);

}
