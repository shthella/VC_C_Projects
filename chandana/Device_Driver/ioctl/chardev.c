#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "chardev"
#define BUF_LEN 1024

#define MY_IOCTL_RESET _IO('k', 1) // Reset the device

static int majorNumber;
static char msg[BUF_LEN] = {0};
static short size_of_msg;
static int numberOpens = 0;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);
static long dev_ioctl(struct file *, unsigned int, unsigned long);

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
    .unlocked_ioctl = dev_ioctl,
};

static int __init chardev_init(void) {
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "Registered correctly with major number %d\n", majorNumber);
    return 0;
}

static void __exit chardev_exit(void) {
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "Goodbye, world!\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
    numberOpens++;
    printk(KERN_INFO "Device has been opened %d time(s)\n", numberOpens);
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int error_count = 0;
    error_count = copy_to_user(buffer, msg, size_of_msg);
    if (error_count == 0) {
        printk(KERN_INFO "Sent %d characters to the user\n", size_of_msg);
        return (size_of_msg = 0);
    } else {
        printk(KERN_INFO "Failed to send %d characters to the user\n", error_count);
        return -EFAULT;
    }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    strncpy(msg, buffer, len);
    size_of_msg = len;
    printk(KERN_INFO "Received %zu characters from the user\n", len);
    return len;
}

static int dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static long dev_ioctl(struct file *filep, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case MY_IOCTL_RESET:
            // Reset the device
            memset(msg, 0, BUF_LEN);
            size_of_msg = 0;
            printk(KERN_INFO "Device reset\n");
            break;
        default:
            return -EINVAL; // Invalid argument
    }
    return 0;
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver with ioctl support");
MODULE_VERSION("0.1");

