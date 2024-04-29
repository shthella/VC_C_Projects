#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE "/dev/chardev"
#define MY_IOCTL_RESET _IO('k', 1)

int main() {
    int file_desc;
    char read_buf[1024];

    // Open the device file
    file_desc = open(DEVICE, O_RDWR);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE);
        exit(-1);
    }

    // Reset the device using ioctl
    printf("Resetting the device...\n");
    ioctl(file_desc, MY_IOCTL_RESET);

    // Close the device file
    close(file_desc);
    return 0;
}

