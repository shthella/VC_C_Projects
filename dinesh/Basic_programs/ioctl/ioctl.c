#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define BUF_SIZE 1024
#define WR_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('b','b',int32_t*)
 

int32_t val = 0;
dev_t dev = 0;
static struct cdev my_cdev;


static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .unlocked_ioctl = my_ioctl,
};

// Definition of my_ioctl
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case WR_DATA:
           copy_from_user(&val, (int32_t *)arg, sizeof(val));
           printk(KERN_INFO "val = %d\n", val);
            break;
        case RD_DATA:
            if (val == 42) {
		char buf[] = "I got the correct number";
                copy_to_user((char *)arg, buf, sizeof(buf)); 
            }
	   else
		{
		char buf[] = "I got the wrong number";
                copy_to_user((char *)arg, buf, sizeof(buf)); 
		}
            break;
    }
    return 0; // Return 0 on success
}

static int __init my_char_driver_init(void) {
    if (alloc_chrdev_region(&dev, 0, 1, "myioctl_dev") < 0) {
        printk(KERN_INFO "Failed to allocate major number\n");
        return -1;
    }
    printk(KERN_INFO "Major = %d Minor = %d\n", MAJOR(dev), MINOR(dev));
    cdev_init(&my_cdev, &fops);

    if (cdev_add(&my_cdev, dev, 1) < 0) {
        printk(KERN_INFO "Failed to add device to the system\n");
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    printk(KERN_INFO "Character device driver initialized\n");
    return 0;
}

static void __exit my_char_driver_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Character device driver removed\n");
}

module_init(my_char_driver_init);
module_exit(my_char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver with copy from/to user");
 

