#include <linux/kernel.h>
#include <linux/module.h>

static int cscull_major = 0;
static int cscull_minor = 0;
static int cscull_nr_devices = 0;
struct cscull_dev my_sd;

struct cscull_dev {
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned int size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
}

static int cscull_init(void)
{
	int result;
	dev_t dev;
	
	if (cscull_major) {
		dev = MKDEV(cscull_major, cscull_minor);
		result = register_chardev_region(dev, cscull_nr_devices,
						 "cscull");
	} else {
		dev = alloc_chardev_region(&dev, 0, 1, "cscull");
		result = cscull_major = MAJOR(dev);
	}
	
	if (result < 0) {
		printk(KERN_DEBUG "Can't allocate device\n");
		return result;
	}
	
	
}


MODULE_LICENSE("GPL");
module_init(cscull_init);
module_exit(cscull_exit);
