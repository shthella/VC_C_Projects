
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_NODE "/dev/mychar_dev"

int main() {
    int fd;
    char write_buf[] = "Hello from user space!";
    char read_buf[1024];

    // Open the device file
    fd = open(DEVICE_NODE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device file");
        return -1;
    }

    // Write to the device
    if (write(fd, write_buf, strlen(write_buf)) < 0) {
        perror("Failed to write to the device");
        close(fd);
        return -1;
    }
    printf("Data written to device: %s\n", write_buf);

    // Read from the device
    if (read(fd, read_buf, sizeof(read_buf)) < 0) {
        perror("Failed to read from the device");
        close(fd);
        return -1;
    }
    printf("Data read from device: %s\n", read_buf);
	memset(read_buf,'\0',sizeof(read_buf));	
     if (read(fd, read_buf, sizeof(read_buf)) < 0) {
        perror("Failed to read from the device");
        close(fd);
        return -1;
    }
    printf("Data read from device 2nd time: %s\n", read_buf);

    // Close the device file
    close(fd);

    return 0;
}
