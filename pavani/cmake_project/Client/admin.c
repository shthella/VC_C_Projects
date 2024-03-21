#include "admin.h"

// Admin Interface
void admin_interface(int client_socket) {

  debug_log(1, "Entering to admin interface\n");
  printf("\t---------------------------------------------\n");
  printf("\tWelcome to Admin Interface\t\n");
  printf("\t---------------------------------------------\n");
  printf("\n");
  int choice;
  do {

    // Display admin menu options
    debug_log(2, "Display of admin menu options\n");
    char message[1024];
    printf("1. Add Restaurant\n");
    printf("2. Display Restaurant\n");
    printf("3. Delete Restaurant\n");
    printf("4. Sign In\n");
    printf("5. Log In\n");
    printf("6. Exit\n");
    printf("\nEnter your choice: ");
    fgets(message, sizeof(message), stdin);

    // Check if the input is numeric
    if (isdigit(message[0])) {
      debug_log(3, "Sending the choice to server\n");
      send(client_socket, message, strlen(message), 0);

      choice = atoi(message);
      char name[100];
      char address[100];
      char contact_number[20];
      switch (choice) {
      case 1:
        debug_log(3, "Selection of adding restaurants choice\n");
        debug_log(3, "Sending restaurant details to server\n");
        printf("\t**** Enter Restaurant Details ****\n");
        printf("\n");
        printf("Enter restaurant name: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        printf("Enter restaurant address: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        printf("Enter contact number: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        // Receive response from server
        debug_log(3, "Receiving response from server\n");
        memset(message, 0, sizeof(message));
        recv(client_socket, message, sizeof(message) - 1, 0);

        printf("Server response: %s\n", message);

        break;
      case 2:
        debug_log(3, "Selection of display restaurants choice\n");
        printf("\t**** Available Restaurants ****\n");
        display_restaurants(client_socket);

        break;

      case 3:
        char id[20];
        char response[100];
        
        // Prompt user to enter restaurant ID to delete
	printf("Enter Restaurant ID to delete: ");
	fgets(id, sizeof(id), stdin);
	
	// Send restaurant ID to server
        send(client_socket, id, strlen(id), 0);
        
        // Receive response from server
	memset(response, 0, sizeof(response));
	recv(client_socket, response, sizeof(response), 0);
	printf("Server response: %s\n", response);

        break;

      case 4:
        printf("\t **** Sign In ****\n");

        char message[1024];
        printf("Enter Restaurant ID: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        char username[50], password[50];
        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0'; // Remove newline character

        // Send username to server
        send_message(client_socket, username);

        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove newline character

        // Send password to server
        send_message(client_socket, password);
        printf("Sign In Successfull!\n");
        break;
      case 5:
        printf("\t**** Log in *****\n");

        int restaurant_id;
        printf("Enter Restaurant ID: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        restaurant_id = atoi(message);
        // Receive prompts for username and password and send them to the server
        debug_log(3, "Authentication of admin credentials\n");

        retry:

          // Read username
          debug_log(3, "Verfication of admin username\n");
        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0'; // Remove newline character

        // Send username to server
        send_message(client_socket, username);

        // Read password
        debug_log(3, "Verfiaction of admin password\n");
        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove newline character

        // Send password to server
        send_message(client_socket, password);

        memset(message, 0, sizeof(message));
        recv(client_socket, message, sizeof(message) - 1, 0);

        printf("Server response: %s\n", message);

        if (strcmp(message, "Credentials are correct. Admin authenticated.") == 0) {
          printf("Login Successful\n");
          printf("\n");

          // Perform admin tasks
          int b;
          while (1) {
            debug_log(2, "Admin tasks\n");
            l1:
              printf("Admin tasks:\n");
            printf("1. Add item\n");
            printf("2. Remove item\n");
            printf("3. Update item\n");
            printf("4. View order history\n");
            printf("5. Overall Sales\n");
            printf("6. Display Menu\n");
            printf("7. Exit\n");
            printf("\nEnter option: ");

            fgets(message, sizeof(message), stdin);

            // Check if the input is not empty
            if (isdigit(message[0])) {
              send_message(client_socket, message);

              b = atoi(message);

              switch (b) {
              case 1:
                debug_log(3, "Call of add item function\n");
                add_item(client_socket);

                debug_log(3, "Call of Receive menu function\n");
                display_menu(client_socket);

                break;
              case 2:
                debug_log(3, "Call of remove item function\n");
                remove_item(client_socket);

                break;
              case 3:
                debug_log(3, "Call of update item function\n");
                update_item(client_socket);

                break;
              case 4:
                debug_log(3, "Call of display order function\n");
                display_order_history(client_socket);

                break;
              case 5:
                int time_interval;
                debug_log(3, "Overall Sales display\n");
                // Get the time interval from the user
                printf("Enter the time interval (1 for DAILY, 2 for WEEKLY, 3 for MONTHLY): ");
                scanf("%d", & time_interval);
                send(client_socket, & time_interval, sizeof(time_interval), 0);

                memset(message, 0, sizeof(message));
                recv(client_socket, message, sizeof(message) - 1, 0);

                printf("Server response: %s\n", message);
                break;
              case 6:
                debug_log(3, "Call of receive menu function\n");
                display_menu(client_socket);
                goto l1;
                break;
              case 7:
                debug_log(3, "Exit from admin tasks\n");
                printf("Exiting...\n\n");
                break;
              default:
                debug_log(3, "Invalid choice\n");
                printf("Invalid Choice\n\n");
              }

              if (b == 7) {
                break; // Break the loop if the user chose option 7 to exit
              }
            } else {
              debug_log(2, "Input is not numeric\n");
              // Input is not numeric
              printf("Invalid input. Please enter a numeric choice.\n");
            }

            debug_log(3, "Clear input buffer for admin interface\n");
            clear_input_buffer(); // Clear input buffer
          }
        } else {
          debug_log(3, "Invalid username and password\n");
          printf("Invalid Username or Password\n");
          printf("Retry: \n");

          goto retry;
        }

        break;

      case 6:
        printf("Exiting....\n");
        break;
      default:
        debug_log(3, "Invalid choice\n");
        printf("Invalid choice\n");
        break;

      }
    } else {
      // Input is not numeric

      printf("Invalid input. Please enter a numeric choice.\n");

    }
  } while (choice != 6);

}
