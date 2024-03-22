#include "debug_log.h"

int debug = 0; // Global variable to hold debug level

char ip_addr[20];

// Function to set debug level based on command-line arguments
void setDebugLevel(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [IP Address] [-v debug_level]\n", argv[0]);
        printf("Using default IP address: 127.0.0.1\n");
        strcpy(ip_addr, "127.0.0.1"); // Default IP address
    } else {
        strcpy(ip_addr, argv[1]); // Copy the provided IP address
    }

    // Check for debug level argument and set debug level accordingly
    if (argc >= 4 && strcmp(argv[2], "-v") == 0) {
        if (strcmp(argv[3], "1") == 0 || strcmp(argv[3], "2") == 0 || strcmp(argv[3], "3") == 0) {
            debug = atoi(argv[3]);
            printf("Debug level set to: %d\n", debug);
        } else {
            printf("Invalid input!\n Input format is -v 1 or -v 2 or -v 3 only\n");
            exit(1);
        }
    } else {
        debug = 1; // Default debug level
        printf("Debug level set to default: %d\n", debug);
    }
}

void debug_log(int level, const char * message) {
  if (debug >= level) {
    printf("Debug: %s\n", message);
  }
}
