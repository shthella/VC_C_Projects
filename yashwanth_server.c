#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define PORT 8080
#define MAX_PENDING_CONNECTIONS 10
#define DATABASE "restaurant.db"
#define DAILY 1
#define WEEKLY 2
#define MONTHLY 3

int debug = 0; // Global variable to hold debug level
char *ip_address; // Declaration of ip_address variable


void setIP() {
    char input[256];
    printf("Enter the IP address: ");
    fgets(input, sizeof(input), stdin);
    // Remove trailing newline character
    input[strcspn(input, "\n")] = '\0';
    ip_address = strdup(input);
    printf("IP address set to: %s\n", ip_address);
}


void setDebugLevel(int argc, char * argv[]) {
  if (argc <= 3) {
    if (argc == 1) {
      printf("\n");
    } else if (argc == 2) {
      if (!strcmp(argv[1], "-v") == 0) {
        printf("Invalid input! Enter -v\n");
        exit(1);
      } else {
        debug = 2;
        printf("Debug level set to: %d\n", debug);
      }
    } else if (argc == 3) {
      if (!strcmp(argv[1], "-v") && (strcmp(argv[2], "1") == 0 || strcmp(argv[2], "2") == 0 || strcmp(argv[2], "3") == 0)) {
        debug = atoi(argv[2]);
        printf("Debug level set to: %d\n", debug);
      } else {
        printf("Invalid input!\n Input format is -v 1 or -v 2 or -v 3 only\n");
        exit(1);
      }
    } else {
      debug = 2;
      printf("Debug level set to: %d\n", debug);
    }
  }
}

void debug_log(int level, const char * message) {
  if (debug >= level) {
    printf("Debug[%d]: %s\n", level, message);
  }
}

typedef struct {
  int restaurant_id;
  char * username;
  char * password;
} AdminCredentials;

AdminCredentials adminCredentials[] = {
  {
    1,
    "admin1",
    "password1"
  },
  {
    2,
    "admin2",
    "password2"
  },
  // Add more restaurant-admin mappings as needed
};

int numAdminCredentials = sizeof(adminCredentials) / sizeof(adminCredentials[0]);

typedef struct {
  int item_id;
  int quantity;
  double price;
  double total_price_with_tax;
}
OrderedItem;

// Function to initialize the database
void initialize_database() {
  debug_log(2, "Initialize of the database restaurant.db\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  debug_log(2, "Variables creation for database\n");
  debug_log(2, "Open database\n");
  int rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(2, "Cannot open database\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    exit(EXIT_FAILURE);

  }
  debug_log(2, " SQL queries for the tables creation in database\n");
  char * sql =
  "CREATE TABLE restaurants (" //restaurant table
  "id INTEGER PRIMARY KEY,"
  "name TEXT NOT NULL,"
  "address TEXT,"
  "contact_number TEXT"
  ");"
  "CREATE TABLE admins (" //Admin table
  "id INTEGER PRIMARY KEY,"
  "restaurant_id INTEGER NOT NULL,"
  "username TEXT NOT NULL,"
  "password TEXT NOT NULL,"
  "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
  ");"
  "CREATE TABLE customers (" //customer table
  "id INTEGER PRIMARY KEY,"
  "restaurant_id INTEGER NOT NULL,"
  "name TEXT NOT NULL,"
  "contact_number TEXT,"
  "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
  ");"
  "CREATE TABLE menu_items (" //menu table
  "id INTEGER PRIMARY KEY,"
  "restaurant_id INTEGER NOT NULL,"
  "item_name TEXT NOT NULL,"
  "price REAL NOT NULL,"
  "UNIQUE (restaurant_id, item_name),"
  "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)"
  ");"
  "CREATE TABLE orders (" //orders table
  "id INTEGER PRIMARY KEY,"
  "restaurant_id INTEGER NOT NULL,"
  "customer_id INTEGER NOT NULL,"
  "item_id INTEGER NOT NULL,"
  "quantity INTEGER NOT NULL,"
  "total_price REAL NOT NULL,"
  "order_date DATE DEFAULT CURRENT_DATE,"
  "FOREIGN KEY (restaurant_id) REFERENCES restaurants(id),"
  "FOREIGN KEY (customer_id) REFERENCES customers(id),"
  "FOREIGN KEY (item_id) REFERENCES menu_items(id)"
  ");";

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);
  debug_log(2, "SQL executed sucessfully\n");

  if (rc != SQLITE_OK) {
    debug_log(3, "Checking of tables creation\n");
    fprintf(stderr, "%s\n", zErrMsg);

    sqlite3_free(zErrMsg);

  } else {
    debug_log(3, "Tables creation successfully\n");
    fprintf(stdout, "Tables created successfully\n");

  }

  // Close database
  debug_log(2, "Close database\n");
  sqlite3_close(db);

}
// Define function prototypes
void * handle_client(void * arg);

// Function to add restaurants into database
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
    debug_log(3, "Restaurant added successfully\n");
    printf("Restaurant added successfully.\n");
    char * successMsg = "Restaurant added successfully.";
    char *ip_address; // Declaration of ip_address variable
    send(client_socket, successMsg, strlen(successMsg), 0);

  }
  debug_log(2, "Close database\n");
  sqlite3_close(db);
}

void display_restaurants(int client_socket) {
  debug_log(2, "Entering to display restaurants function\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  // Open the database
  debug_log(2, "Open database for display restaurants\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for display restaurants\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  debug_log(3, "SQL query to fetch display of restaurants\n");
  const char * sql = "SELECT id, name FROM restaurants;";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Preparation of SQL statement\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  // Send each row of restaurant information to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send restaurant information to client\n");
    // Extract data from the result row
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);

    // Create a buffer to send the data
    debug_log(3, "Creation of a buffer to send the data\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "ID: %d, Name: %s\n", id, name);
    // Send the data to the client
    debug_log(3, "Send the data to the client\n");
    char ack[10];
    int valread;
    valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
    debug_log(3, "Receive data into acknowledgement buffer\n");
    if (valread > 0) {
      ack[valread] = '\0';
      int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
      sleep(1);
    }

  }
  // Send the "END" message separately after sending all restaurant details
  debug_log(3, "Send the end message seperately after sending all restaurant details\n");
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
  	debug_log(3, "Error sending end message for display restaurant\n");
    perror("Error sending END message");
  } else {
  	debug_log(3, "End message sent for display restaurant\n");
    printf("End message sent.\n");
  }

  // Finalize the statement and close the database
  debug_log(2, "Close database for display restaurants function\n");
  sqlite3_finalize(stmt);

  sqlite3_close(db);

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
  debug_log(2, "Close database for add item\n");
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

void display_menu(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to display menu function\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  // Open the SQLite database
  debug_log(2, "Open database\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open databse for display menu\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  // Prepare the SQL statement
  debug_log(3, "SQL query for display menu\n");
  const char * sql = "SELECT id, item_name, price FROM menu_items WHERE restaurant_id = ?;";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to prepare statement for display menu\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  // Bind the restaurant_id parameter to the SQL statement
  debug_log(3, "Bind the restaurant_id to the statement\n");
  sqlite3_bind_int(stmt, 1, restaurant_id);

  // Send each row of menu item information to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send each row of the menu item information to the client\n");
    // Extract data from the result row
    int id = sqlite3_column_int(stmt, 0);
    const char * item_name = (const char * ) sqlite3_column_text(stmt, 1);
    double price = sqlite3_column_double(stmt, 2);

    // Create a buffer to send the data
    debug_log(3, "Creation of buffer to send data for display menu function\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "ID: %d, Item: %s, Price: %.2f\n", id, item_name, price);
    // Send the data to the client
    debug_log(3, "Send the data to the client for the display menu function\n");
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
  debug_log(3, "Send an empty message to indicate the end of data\n");
  // Send the "END" message separately after sending all restaurant details
  debug_log(3, "Send the end message separately after sending all restaurant details\n");
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
  	debug_log(3, "Error sending end message for the display menu function\n");
    perror("Error sending END message");
  } else {
    printf("End message sent.\n");
  }
  // Finalize the statement and close the database connection
  debug_log(2, "Close database for display menu\n");
  sqlite3_finalize(stmt);

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
  debug_log(3, "Binding the restaurant_id, username, password\n");
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

void admin_interface(int client_socket) {
  // Implement the admin interface logic here
  debug_log(1, "Entering to admin interface\n");
  char message[1024];
  int choice;
  do {
    debug_log(2, "Receive of choice from admin\n");
    recv(client_socket, message, sizeof(message) - 1, 0);

    choice = atoi(message);
    printf("%d\n", choice);

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
    	int restaurnat_id;
    	debug_log(2, "Receive of restaurant_id from admin\n");
    	rec(client_socket, message, sizeof(message) -1, 0);
    	
    	restaurant_id = atoi(message);
    	char username[50], password[50];
    	debug_log(3, "Receive of username from admin\n");
    	recv(client_socket, username, sizeof(password) - 1, 0);
    	debug_log(3, "Receive of password from admin\n");
    	recv(client_socket, password, sizeof(password) - 1, 0);
    	add_admin(restaurant_id, username, password);
    	break;
    case 4:
      // Exit the admin interface
      debug_log(3, "Exit from admin interface\n");
      printf("Exiting...\n");

      break;
    default:
      // Invalid choice
      debug_log(3, "Invalid choice\n");
      printf("Invalid choice \n");

    }
  } while (choice != 4);
  int restaurant_id;
  debug_log(2, "Receive of restaurant_id from admin\n");
  recv(client_socket, message, sizeof(message) - 1, 0);

  restaurant_id = atoi(message);

  char username[50], password[50];
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
        printf("%d\n", b);
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

        }
      } while (b != 7);
    }
  }
}

int getCustomerIdFromDatabase(const char * name) {
  debug_log(2, "Fetching customer_id from database\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int customer_id = -1; // Initialize customer_id to -1 as an error indicator

  // Open database
  debug_log(2, "Open database for fetching customer_id\n");
  if (sqlite3_open(DATABASE, & db) == SQLITE_OK) {
    char sql[256];
    debug_log(3, "SQL query for fetching the customer_id\n");
    sprintf(sql, "SELECT id FROM customers WHERE name = '%s';", name);

    // Prepare SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, & stmt, NULL) == SQLITE_OK) {
      // Execute SQL statement
      if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Retrieve customer_id from the result
        debug_log(3, "Retrieve customer_id from the result\n");
        customer_id = sqlite3_column_int(stmt, 0);

      }
    }

    // Finalize statement and close database
    debug_log(2, "Close database for fetching customer_id\n");
    sqlite3_finalize(stmt);
    sqlite3_close(db);

  }

  return customer_id;

}

void customer_restaurants(int client_socket) {
  debug_log(2, "Entering to display restaurants function\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;

  // Open the database
  debug_log(2, "Open database for display restaurants\n");
  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for display restaurants\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }
  debug_log(3, "SQL query to fetch display of restaurants\n");
  const char * sql = "SELECT id, name FROM restaurants;";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Preparation of SQL statement\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  // Send each row of restaurant information to the client
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    debug_log(3, "Send restaurant information to client\n");
    // Extract data from the result row
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);

    // Create a buffer to send the data
    debug_log(3, "Creation of a buffer to send the data\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "ID: %d, Name: %s\n", id, name);
    // Send the data to the client
    debug_log(3, "Send the data to the client\n");
    char ack[10];
    int valread;
    valread = recv(client_socket, ack, sizeof(ack) - 1, 0); // Receive data into ack buffer
    debug_log(3, "Receive data into acknowledgement buffer\n");
    if (valread > 0) {
      ack[valread] = '\0';
      int bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
      sleep(1);
    }

  }
  // Send the "END" message separately after sending all restaurant details
  debug_log(3, "Send the end message seperately after sending all restaurant details\n");
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
    debug_log(3, "Error sending end message for display restaurant\n");
    perror("Error sending END message");
  } else {
    debug_log(3, "End message sent for display restaurant\n");
    printf("End message sent.\n");
  }

  // Finalize the statement and close the database
  debug_log(2, "Close database for display restaurants function\n");
  sqlite3_finalize(stmt);

  sqlite3_close(db);

}

void add_order_to_database(int restaurant_id, int customer_id, int item_id, int quantity, double total_price) {
  debug_log(2, "Add order details to databse\n");
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database for Add order details\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  char sql[500];
  debug_log(3, "SQL query to add order details to database\n");
  sprintf(sql, "INSERT INTO orders (restaurant_id, customer_id, item_id, quantity, total_price) VALUES (%d, %d, %d, %d, %.2f);",
    restaurant_id, customer_id, item_id, quantity, total_price);

  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for add order details to database\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);

  } else {
    printf("Order added to the database successfully.\n");
  }
  debug_log(2, "Close database for adding order details\n");
  sqlite3_close(db);

}

double get_item_price(int restaurant_id, int item_id) {
  debug_log(2, "Getting item price from database\n");
  sqlite3 * db;
  sqlite3_stmt * stmt;
  int rc;
  double price = -1; // Initialize price to -1 (indicating not found)

  rc = sqlite3_open(DATABASE, & db);

  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database to fetch item price\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return price;
  }

  // Prepare SQL statement to select the price of the item based on its ID and restaurant ID
  debug_log(3, "SQL query to fetch item price from database\n");
  char * sql = "SELECT price FROM menu_items WHERE restaurant_id = ? AND id = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, & stmt, NULL);

  if (rc != SQLITE_OK) {
    debug_log(3, "Failed to open database to fetch item price\n");
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return price;
  }

  // Bind the restaurant_id and item_id parameters to the prepared statement
  debug_log(3, "Bind the restauramnt_id and item_id parameters to the prepared statement\n");
  sqlite3_bind_int(stmt, 1, restaurant_id);

  sqlite3_bind_int(stmt, 2, item_id);

  // Execute the SQL statement
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    // Fetch the price of the item from the result set
    price = sqlite3_column_double(stmt, 0);

  }

  // Finalize the statement and close the database connection
  debug_log(2, "Close databse connection for fetching of item price\n");
  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return price;

}

void generate_invoice(int client_socket, OrderedItem ordered_items[], int num_items) {
  // Prepare the bill in a formatted string
  debug_log(2, "Entering to generate invoice function\n");
  char invoice[4096];
  sprintf(invoice, "\n\n======= Invoice =======\n\n");

  double total_bill = 0.0;

  // Iterate over ordered items and add them to the bill
  for (int i = 0; i < num_items; ++i) {
    debug_log(2, "Collection of all the items and calculation of total bill\n");
    total_bill += ordered_items[i].total_price_with_tax;
    sprintf(invoice + strlen(invoice), "Item ID: %d | Quantity: %d | Price: $%.2f | Total Price with Tax: $%.2f\n",
      ordered_items[i].item_id, ordered_items[i].quantity, ordered_items[i].price, ordered_items[i].total_price_with_tax);

  }

  // Add total bill amount to the invoice
  debug_log(2, "Invoice generation\n");
  sprintf(invoice + strlen(invoice), "\nTotal Bill: $%.2f\n\n", total_bill);

  // Send the invoice to the client
  debug_log(3, "Sending invoice to customer\n");
  int bytes_sent = send(client_socket, invoice, strlen(invoice), 0);

  if (bytes_sent < 0) {
    debug_log(3, "Error sending invoice to customer\n");
    perror("Error sending invoice");

    return;
  }
}

void place_order(int client_socket, int restaurant_id) {
  debug_log(2, "Entering to place order function\n");
  char name[100];
  char contact_number[20];

  // Receive customer details from the client
  debug_log(3, "Receive of customer details\n");
  memset(name, 0, sizeof(name));
  memset(contact_number, 0, sizeof(contact_number));

  recv(client_socket, name, sizeof(name), 0);
  recv(client_socket, contact_number, sizeof(contact_number), 0);

  // Database operations to insert customer details
  sqlite3 * db;
  char * zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DATABASE, & db);
  if (rc != SQLITE_OK) {
    debug_log(3, "Cannot open database to place order\n");
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return;
  }

  char sql[500];
  debug_log(3, "SQL query to insert the order into databse\n");
  sprintf(sql, "INSERT INTO customers (restaurant_id, name, contact_number) VALUES (%d, '%s', '%s');",
    restaurant_id, name, contact_number);
  rc = sqlite3_exec(db, sql, 0, 0, & zErrMsg);

  if (rc != SQLITE_OK) {
    debug_log(3, "SQL error for placing order\n");
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);

    return;
  }

  int customer_id = getCustomerIdFromDatabase(name);

  OrderedItem ordered_items[100]; // Assuming a maximum of 100 items
  int num_items = 0;

  char continue_order;
  do {
    debug_log(3, "Receive order details from the customer\n");
    // Receive order details from the client
    int item_id;
    int quantity;

    recv(client_socket, & item_id, sizeof(item_id), 0);

    recv(client_socket, & quantity, sizeof(quantity), 0);

    debug_log(2, "Invoice generation\n");
    // Calculate total price, retrieve item details from the database
    double price = get_item_price(restaurant_id, item_id);

    double total_price = price * quantity;

    // Calculate total price with tax
    double total_price_with_tax = total_price * 1.1;

    // Save ordered item details
    debug_log(2, "Save ordered item details\n");
    ordered_items[num_items].item_id = item_id;
    ordered_items[num_items].quantity = quantity;
    ordered_items[num_items].price = price;
    ordered_items[num_items].total_price_with_tax = total_price_with_tax;
    num_items++;
    add_order_to_database(restaurant_id, customer_id, item_id, quantity, total_price_with_tax);

    // Ask if the user wants to continue ordering
    debug_log(2, "Waiting for the customer response to continue order\n");
    recv(client_socket, & continue_order, sizeof(continue_order), 0);

  } while (continue_order == 'y');

  // Add order details to the database

  // Generate invoice once all items are ordered
  debug_log(3, "Call for generate invoice function\n");
  generate_invoice(client_socket, ordered_items, num_items);

  debug_log(2, "Close databse for place order function\n");
  sqlite3_close(db);

}

void customer_interface(int client_socket) {
  debug_log(1, "Entering to customer interface\n");
  int restaurant_id;
  char message[1024];
  // Display restaurants to customer, to select restaurants
  debug_log(2, "Call for display restaurant function\n");
  display_restaurants(client_socket);

  //recieving from customer
  debug_log(3, "Receiving restaurant choice from customer\n");
  recv(client_socket, & restaurant_id, sizeof(restaurant_id), 0);

  int c;
  do {
    debug_log(2, "Choice for Customer tasks\n");
    memset(message, 0, sizeof(message));
    recv(client_socket, message, sizeof(message) - 1, 0);

    c = atoi(message);
    printf("%d\n", c);
    switch (c) {
    case 1:
      debug_log(3, "Call for customer menu function\n");
      display_menu(client_socket, restaurant_id);

      break;
    case 2:
      debug_log(3, "Call for place order function\n");
      place_order(client_socket, restaurant_id);

      break;
    case 3:
      debug_log(3, "Exit from customer tasks\n");
      printf("Exiting...\n");

      break;
    default:
      debug_log(3, "Invalid Choice\n");
      printf("Invalid choice\n");

    }
  } while (c != 3);

}

/*int main(int argc, char * argv[]) {
  setDebugLevel(argc, argv); // Set debug level based on command-line arguments

  debug_log(1, "Enter into main function\n");
  // Create server socket
  debug_log(3, "Create server socket\n");
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  char message[1024];
  // Initialize database and other necessary components
  debug_log(2, "Initialize database\n");
  initialize_database();

  // Create server socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    debug_log(3, "Socket creation failed\n");
    perror("Socket creation failed");

    exit(EXIT_FAILURE);
  }

  // Set the SO_REUSEADDR socket option
  debug_log(3, "Address initialize\n");
  int optval = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, & optval, sizeof(optval)) == -1) {
    perror("Setting SO_REUSEADDR failed");
    exit(EXIT_FAILURE);
  }

  // Initialize server address structure
  debug_log(3, "Initialize server address structure\n");
  server_addr.sin_family = AF_INET;

  server_addr.sin_addr.s_addr = inet_addr("192.168.29.111"); // place the ip address of the client system

  server_addr.sin_port = htons(PORT);

  // Bind the server socket to the specified address and port
  debug_log(3, "Bind the server socket to the specified address and port\n");
  if (bind(server_socket, (struct sockaddr * ) & server_addr, sizeof(server_addr)) == -1) {
    debug_log(3, "Binding failed\n");
    perror("Binding failed");
    exit(EXIT_FAILURE);

  }

  // Listen for incoming connections
  debug_log(3, "Listen for incoming connections\n");
  if (listen(server_socket, MAX_PENDING_CONNECTIONS) == -1) {
    debug_log(3, "Listen failed\n");
    perror("Listen failed");
    exit(EXIT_FAILURE);

  }

  printf("Server is listening on port %d...\n", PORT);

  // Accept incoming connections and handle clients
  while (1) {
    debug_log(3, "Accept incoming conections and handle clients\n");
    client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr * ) & client_addr, & client_addr_len);

    if (client_socket == -1) {
      debug_log(3, "Accept failed\n");
      perror("Accept failed");
      exit(EXIT_FAILURE);

    }

    printf("Client connected \n");

    // Create a new thread to handle the client
    debug_log(3, "Create a new thread to handle the client\n");
    pthread_t thread_id;
    if (pthread_create( & thread_id, NULL, handle_client, (void * ) & client_socket) < 0) {
      debug_log(3, "Could not create thread\n");
      perror("Could not create thread");

      return 1;
    }
  }
  return 0;
}*/

int main(int argc, char *argv[]) {
    // If IP address is not provided, prompt the user for it
    if (argc < 2 || strcmp(argv[1], "-ip") != 0) {
        setIP();
    } else {
         
        // IP address provided as a command-line argument
        if (argc != 3) {
            fprintf(stderr, "Usage: %s -ip <ip_address>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        ip_address = argv[2];
        printf("IP address set to: %s\n", ip_address);
    }

    setDebugLevel(argc, argv); // Set debug level based on command-line arguments
    debug_log(1, "Enter into main function\n");
    // Create server socket
    debug_log(3, "Create server socket\n");
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    char message[1024];
    // Initialize database and other necessary components
    debug_log(2, "Initialize database\n");
    initialize_database();

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        debug_log(3, "Socket creation failed\n");
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the SO_REUSEADDR socket option
    debug_log(3, "Address initialize\n");
    int optval = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("Setting SO_REUSEADDR failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    debug_log(3, "Initialize server address structure\n");
    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = inet_addr(ip_address); // Set IP address here

    server_addr.sin_port = htons(PORT);

    // Bind the server socket to the specified address and port
    debug_log(3, "Bind the server socket to the specified address and port\n");
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        debug_log(3, "Binding failed\n");
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    debug_log(3, "Listen for incoming connections\n");
    if (listen(server_socket, MAX_PENDING_CONNECTIONS) == -1) {
        debug_log(3, "Listen failed\n");
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);
    printf("Maximum connections limited to server are 10\n");

    // Accept incoming connections and handle clients
    while (1) {
        debug_log(3, "Accept incoming conections and handle clients\n");
        client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket == -1) {
            debug_log(3, "Accept failed\n");
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Client connected \n");

        // Create a new thread to handle the client
        debug_log(3, "Create a new thread to handle the client\n");
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_socket) < 0) {
            debug_log(3, "Could not create thread\n");
            perror("Could not create thread");
            return 1;
        }
    }
    return 0;
}

// Thread function to handle a client
void * handle_client(void * arg) {
  debug_log(1, "Entering to handle client function\n");
  int client_socket = * ((int * ) arg);
  char message[1024];
  int user_type;
  s1:
    // Receive user type from the client
    debug_log(2, "Receive of user type\n");
  memset(message, 0, sizeof(message));
  recv(client_socket, message, sizeof(message) - 1, 0);

  user_type = atoi(message);

  // Handle client requests based on user type
  switch (user_type) {
  case 1:
    debug_log(2, "Call of admin interface\n");
    admin_interface(client_socket);

    goto s1;
    break;
  case 2:
    debug_log(2, "Call of customer interface\n");
    customer_interface(client_socket);

    goto s1;
    break;
  case 3:
    debug_log(2, "Exit from user type\n");
    printf("Exiting..\n");

    break;
  default:
    debug_log(2, "Invalid choice\n");
    printf("Invalid choice\n");

    goto s1;
  }

  // Close the client socket
  debug_log(3, "Close the client socket\n");
  close(client_socket);

  debug_log(3, "Exit from thread\n");
  pthread_exit(NULL);

}
