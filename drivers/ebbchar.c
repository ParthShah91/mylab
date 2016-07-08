/**
 * @file   ebbchar.c
 * @author Derek Molloy
 * @date   7 April 2015
 * @version 0.1
 * @brief   An introductory character driver to support the second article of my series on
 * Linux loadable kernel module (LKM) development. This module maps to /dev/ebbchar and
 * comes with a helper C program that can be run in Linux user space to communicate with
 * this the LKM.
 * @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.
 */

#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <asm/uaccess.h>          // Required for the copy to user function
#define  DEVICE_NAME "ebbchar"    ///< The device will appear at /dev/ebbchar using this value
#define  CLASS_NAME  "ebb"        ///< The device class -- this is a character device driver

MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Derek Molloy");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux char driver for the BBB");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            ///< A version number to inform users

struct sample_struct 
{
	int			a;
	char			c;
	struct list_head	list;
};

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init ebbchar_init(void){
	int ret = 0;
	struct list_head *tmp;
	struct sample_struct *nodePtr;
	struct sample_struct node[10];

	// Create a linked list
	node[0].a = 18;
	node[0].c = 'j';
	INIT_LIST_HEAD(&node[0].list); 
	node[1].a = 26;
	node[1].c = 'p';
	INIT_LIST_HEAD(&node[1].list); 

	list_add(&node[1].list, &node[0].list);

	list_for_each(tmp, &node[0].list) 
	{
		nodePtr = list_entry(tmp, struct sample_struct, list);
		printk("a = %d\n", nodePtr->a);
		printk("c = %c\n", nodePtr->c);
	}	
	nodePtr = list_entry(tmp, struct sample_struct, list);
	printk("a = %d\n", nodePtr->a);
	printk("c = %c\n", nodePtr->c);
	return 0;
}

/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit ebbchar_exit(void){
	printk(KERN_INFO "EBBChar: Goodbye from the LKM!\n");
}


/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(ebbchar_init);
module_exit(ebbchar_exit);
