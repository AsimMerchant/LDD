#include "kernHeaders.h"
#define FIRSTMINOR 0
#define DEVICES 1
#define DEVNAME "testcDev"

static dev_t *chardev;
static cdev *char_drv_cdev;
static int inuse=0;



static struct file_operations fops = {
	.owner=THIS_MODULE,
	.open=char_drv_open
	.read=char_drv_read
	.write=char_drv_write
	.release=char_drv_release
};

static int char_drv1_init(void)
{
	int status;
	status=alloc_chrdev_region(chardev,FIRSTMINOR,DEVICES,DEVNAME);
	if(!status)
	{
		pr_info("Failed alloc_chrdev_region\n");
		unregister_chrdev_region(*chardev, DEVICES);
		return status;
	}
	char_drv_cdev=cdev_alloc();
	cdev_init(char_drv_cdev,&fops);

	status=cdev_add(char_drv_cdev, *chardev, DEVICES);
	{
		pr_alert("Failed to add cdev\n");
		unregister_chrdev_region(*chardev, DEVICES);
		cdev_del(char_drv_cdev);
		return status;
	}
	pr_info("Successfully registered device with minor number as %d, look into /proc/devices for major number which should be %d\n",MINOR(*chardev),MAJOR(*chardev));
	return 0;
}

static void char_drv1_exit(void)
{
	cdev_del(char_drv_cdev);
	unregister_chrdev_region(*chardev, DEVICES);	
	pr_info("Exit\n");
}

module_init(char_drv1_init);
module_exit(char_drv1_exit);
MODULE_LICENSE("GPL");

