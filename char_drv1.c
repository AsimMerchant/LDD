#include "kernHeaders.h"

#define FIRSTMINOR 0
#define DEVICES 1
#define DEVNAME "testcDev"

static dev_t chardev;
static struct cdev *char_drv_cdev;
static int inuse=0;
static char *data;

static int char_drv_open(struct inode *inode, struct file *filep)
{
	if(inuse)
	{
		pr_alert("Already open\n");
		return -1;
	}
	inuse=1;
	pr_info("Successfully opened\n");
	return 0;
}

static ssize_t char_drv_read(struct file *filep, char __user *ubuffer, size_t size, loff_t *offset)
{
	int err;
	pr_info("Offset in read is %d",*offset);
	err=copy_to_user(ubuffer,data+*offset,size);
	if(err)
	{
		*offset=size-err;
		return size-err;
	}
	pr_info("Read success\n");
	return size;
}

static ssize_t char_drv_write(struct file *filep, const char __user *ubuffer, size_t size, loff_t *offset)
{
	int err,i;
	pr_info("Offset in write is %d",*offset);

	err=copy_from_user(data+*offset,ubuffer,size);
	if(err)
	{
		*offset=size-err;
		return size-err;
	}
	
	pr_info("Write success\n");
	
	for(i=0;i<strlen(data);i++)
        {
                pr_info("%c\n",data[i]);
        }
	
	return size;
}

static int char_drv_release(struct inode *inode, struct file *filep)
{
	inuse=0;
	pr_info("Closed\n");
	return 0;
}

static struct file_operations fops = {
	.owner=THIS_MODULE,
	.open=char_drv_open,
	.read=char_drv_read,
	.write=char_drv_write,
	.release=char_drv_release
};

static int __init char_drv1_init(void)
{
	int status;
	
	status=alloc_chrdev_region(&chardev,FIRSTMINOR,DEVICES,DEVNAME);
	pr_info("alloc_chrdev_region status=%d\n",status);
	if(status<0)
	{
		pr_alert("Failed alloc_chrdev_region\n");
		return status;
	}
	
	char_drv_cdev=cdev_alloc();
	if(char_drv_cdev==NULL)
	{
		pr_alert("Failed cdev_alloc\n");
		return 1;
	}
	
	cdev_init(char_drv_cdev,&fops);

	status=cdev_add(char_drv_cdev, chardev, DEVICES);
	pr_info("cdev_add status=%d\n",status);
	if(status<0)
	{
		pr_alert("Failed to add cdev\n");
		return status;
	}
	
	pr_info("Successfully registered device with minor number as %d, look into /proc/devices for major number which should be %d\n",MINOR(chardev),MAJOR(chardev));
	
	data=kmalloc(100,GFP_KERNEL);
	return 0;
}

static void char_drv1_exit(void)
{
	cdev_del(char_drv_cdev);
	unregister_chrdev_region(chardev, DEVICES);	
	kfree(data);
	pr_info("Exit\n");
}

module_init(char_drv1_init);
module_exit(char_drv1_exit);
MODULE_LICENSE("GPL");

