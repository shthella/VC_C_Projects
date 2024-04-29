#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE "/dev/mychardev"
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

    // Writing to the device
    printf("Writing to the device...\n");
    write(file_desc, "Hello from user space!", sizeof("Hello from user space!"));

    // Reading from the device
    printf("Reading from the device...\n");
    read(file_desc, read_buf, sizeof(read_buf));
    printf("Data read from the device: %s\n", read_buf);

    // Reset the device using ioctl
    printf("Resetting the device...\n");
    ioctl(file_desc, MY_IOCTL_RESET);

    // Close the device file
    close(file_desc);
    return 0;
}

