#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

#define MAX_ARRAY_SIZE 5

// Module Information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux driver with array parameter");
MODULE_VERSION("0.1");

// Define module parameter
static int my_array[MAX_ARRAY_SIZE] = {1, 2, 3, 4, 5};
static int array_size = MAX_ARRAY_SIZE;

// Register module parameter
module_param_array(my_array, int, &array_size, S_IRUGO);
MODULE_PARM_DESC(my_array, "An integer array parameter");

static int __init hello_init(void) {
    int i;
    printk(KERN_INFO "Hello, World!\n");
    printk(KERN_INFO "Array parameter:\n");
    for (i = 0; i < array_size; ++i) {
        printk(KERN_INFO "%d ", my_array[i]);
    }
    printk(KERN_INFO "\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

