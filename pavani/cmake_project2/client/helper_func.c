#include "helper_func.h"

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void send_message(int socket, const char *message) {
  debug_log(2, "Send Message\n");
  send(socket, message, strlen(message), 0);
}

int getInput(const char *prompt) {
  int value;
  while (1) {
    printf("%s", prompt);
    if (scanf("%d", & value) != 1) {
      // Clear input buffer in case of non-integer input
      while (getchar() != '\n');
      printf("Invalid input. Please enter a valid number.\n");
    } else {
      // Valid input
      break;
    }
  }
  return value;
}
