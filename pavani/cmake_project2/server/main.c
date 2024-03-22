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

#include "admin_s.h"
#include "customer_s.h"
#include "database.h"
#include "ordered_item.h"
#include "debug_log.h"

#define PORT 8080
#define MAX_PENDING_CONNECTIONS 10


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
    //fprintf(stderr, "%s\n", zErrMsg);

    sqlite3_free(zErrMsg);

  } else {
    debug_log(3, "Tables creation successfully\n");
    //fprintf(stdout, "Tables created successfully\n");

  }

  // Close database
  debug_log(2, "Close database\n");
  sqlite3_close(db);

}
// Define function prototypes
void * handle_client(void * arg);

int main(int argc, char * argv[]) {
  setDebugLevel(argc, argv); // Set debug level based on command-line arguments
  printf("Maximum number of clients connected are 10\n");

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

  server_addr.sin_addr.s_addr = INADDR_ANY;

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

  //printf("Server is listening on port %d...\n", PORT);
  printf("Waiting for client connection\n");

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
  printf("User type: %d\n",user_type);

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
    break;

    goto s1;
  }

  // Close the client socket
  debug_log(3, "Close the client socket\n");
  close(client_socket);

  debug_log(3, "Exit from thread\n");
  pthread_exit(NULL);

}
