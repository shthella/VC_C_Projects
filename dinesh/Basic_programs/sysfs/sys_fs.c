#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "chardev_example"
//#define BUF_LEN 1024

//static char device_buffer[BUF_LEN];
static int device_open_count = 0;
static struct cdev my_cdev;
static dev_t dev;

volatile int etx_value = 0;

struct kobject *kobj_ref;

static ssize_t  sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t  sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count);
struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        pr_info("Sysfs - Read!!!\n");
        return sprintf(buf, "%d", etx_value);
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
        pr_info("Sysfs - Write!!!\n");
        sscanf(buf,"%d",&etx_value);
        return count;
}


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
	return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
    ssize_t bytes_written = 0;
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
  /*Creating a directory in /sys/kernel/ */
        kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);
 
        /*Creating sysfs file for etx_value*/
        if(sysfs_create_file(kobj_ref,&etx_attr.attr)){
                pr_err("Cannot create sysfs file......\n");
                goto r_sysfs;
    }
        pr_info("Device Driver Insert...Done!!!\n");
 	return 0;
r_sysfs:
        kobject_put(kobj_ref); 
        sysfs_remove_file(kernel_kobj, &etx_attr.attr);
	return -1;
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

