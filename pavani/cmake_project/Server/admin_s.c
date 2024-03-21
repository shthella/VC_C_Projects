#include "admin_s.h"

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
