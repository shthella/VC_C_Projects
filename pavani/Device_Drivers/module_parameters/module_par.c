#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

// Module Information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux driver with parameters");
MODULE_VERSION("0.1");

// Define module parameters
static int my_int_param = 123;
static char *my_string_param = "default_string";

// Register module parameters
module_param(my_int_param, int, S_IRUGO); // integer parameter
MODULE_PARM_DESC(my_int_param, "An integer parameter");
module_param(my_string_param, charp, S_IRUGO); // string parameter
MODULE_PARM_DESC(my_string_param, "A string parameter");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello, World!\n");
    printk(KERN_INFO "Integer parameter: %d\n", my_int_param);
    printk(KERN_INFO "String parameter: %s\n", my_string_param);
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

