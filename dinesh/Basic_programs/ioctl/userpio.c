#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define BUF_SIZE 1024
#define WR_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('b','b',int32_t*)

int main() {
    int fd;
    int32_t value;
    char buf[BUF_SIZE];
    fd = open("/dev/myioctl_dev", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return -1;
    }
    printf("Enter a value to write to the device: ");
    scanf("%d", &value);
    if (ioctl(fd, WR_DATA, (int32_t*)&value) < 0) {
        perror("Failed to write data to the device");
        close(fd);
        return -1;
    }
    if (ioctl(fd, RD_DATA, buf) < 0) {
        perror("Failed to read data from the device");
        close(fd);
        return -1;
    }
    printf("Data read from device: %s\n", buf);
    close(fd);

    return 0;
}

