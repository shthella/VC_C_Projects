#include "debug_log.h"

int debug = 0; // Global variable to hold debug level

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
      debug = 1;
      printf("Debug level set to: %d\n", debug);
    }
  }
}

void debug_log(int level, const char * message) {
  if (debug >= level) {
    printf("Debug: %s\n", message);
  }
}
