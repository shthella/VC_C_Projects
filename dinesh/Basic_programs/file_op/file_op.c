#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "chardev_example"
#define BUF_LEN 1024

static char device_buffer[BUF_LEN];
static int device_open_count = 0;
static struct cdev my_cdev;
static dev_t dev;

static int device_open(struct inode *inode, struct file *file)
{
    if (device_open_count)
        return -EBUSY;

    device_open_count++;
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    device_open_count--;
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
	ssize_t bytes_read=0;
	if(device_buffer[0]=='\0')
	{	 char empty_buffer[BUF_LEN]="the buffer is empty\n";
		 bytes_read=sizeof(empty_buffer);
		if(copy_to_user(buffer,empty_buffer, length)!=0)
	{
		printk(KERN_ALERT "Failed update the information\n");
		return 0;
	}
	}
	else
	{	
		bytes_read=sizeof(device_buffer);
		if(copy_to_user(buffer,device_buffer, length)!=0)
	{
		printk(KERN_ALERT "Failed to read the device\n");
		return 0;
	}
	memset(device_buffer,'\0',sizeof(device_buffer));
	}

    return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
    ssize_t bytes_written = 0;


    if (copy_from_user(device_buffer, buffer, length)!=0)
	{
		printk(KERN_ALERT "Failed to write into the device\n");
		return 0;
	}
        
    return bytes_written;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int __init chardev_init(void)
{
    if (alloc_chrdev_region(&dev, 0, 1, "mychar_dev") < 0) {
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

static void __exit chardev_exit(void)
{
    unregister_chrdev(0, DEVICE_NAME);
    printk(KERN_INFO "chardev_example: device driver unregistered\n");
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Character device driver example");

