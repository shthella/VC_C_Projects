#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mychardev"
#define BUF_LEN 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("0.1");

static int Major;
static char msg[BUF_LEN] = "Hello from the kernel";
static char *msg_ptr;


static int mychardev_open(struct inode *inode, struct file *filp) {
    msg_ptr = msg;
    return 0;
}

static ssize_t mychardev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    ssize_t bytes_read = 0;
    if (*f_pos >= BUF_LEN) // Check if we've reached the end of the message
        return 0; // End of file
    // Copy data from kernel buffer to user buffer
    bytes_read = min(count, (size_t)(BUF_LEN - *f_pos)); // Calculate bytes to read
    if (copy_to_user(buf, msg + *f_pos, bytes_read)) {
        return -EFAULT; // Error copying data to user space
    }
    *f_pos += bytes_read; // Update the file position
    return bytes_read;
}

static ssize_t mychardev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {
    ssize_t bytes_written = 0;
    if (*f_pos >= BUF_LEN) // Check if we've reached the end of the buffer
        return -ENOSPC; // No space left on device
    // Copy data from user buffer to kernel buffer
    bytes_written = min(count, (size_t)(BUF_LEN - *f_pos)); // Calculate bytes to write
    if (copy_from_user(msg + *f_pos, buf, bytes_written)) {
        return -EFAULT; // Error copying data from user space
    }
    *f_pos += bytes_written; // Update the file position
    return bytes_written;
}

static struct file_operations fops = {
    .owner = THIS_MODULE, 
    .read = mychardev_read,
    .write = mychardev_write,
    .open = mychardev_open,
    //.release = mychardev_release,
};

static int __init mychardev_init(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    printk(KERN_INFO "Registered char device with major number %d\n", Major);
    return 0;
}

static void __exit mychardev_exit(void) {
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_INFO "Unregistered char device\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);

