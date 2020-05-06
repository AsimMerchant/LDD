#include "kernHeaders.h"

struct proc_dir_entry *some_file; 
char *message=NULL;
int len;
int prochello_open (struct inode *_inode, struct file *_file)
{
	pr_alert("Opened\n");
	return 0;
}

ssize_t prochello_read (struct file *_file, char __user *udata, size_t size, loff_t *offset)
{
	int err,data_size;
	char *data=PDE_DATA(file_inode(_file));
	
	pr_alert("Read Operation performed in %s and offset at this point is %d\n",__func__, (int)(*offset);
	if(size==0)
	{
		pr_alert("Nothing to read-read call will end here\n");
		return size;
	}
	
	data_size=strlen(data);
	pr_alert("Requested read size=%d===size of the message Buffer(len) during initialization=%d===Size of data(data_size) when read from inode =%d\n",(int)size, len,data_size);
	err=copy_to_user(udata,data,len+1);
	if(err)
		pr_alert("Error in copy_to_user");
	else
		pr_alert("Success copy_to_user");

	return len+1;
}

static struct file_operations fops = {

.open = prochello_open,
.read = prochello_read,
.write = prochello_write,
.release = prochello_close,

};

static int prochello_init(void)
{
	char *data="First  invocation after loading";
	message=kmalloc(1024,GFP_KERNEL); // always use macros to define size
	len=strlen(data);
	strncpy(message,data,len+1)
	pr_alert("Value of message during %s is %s\n", __func__,message); 
	some_file=proc_create_data("newprochello", S_IRWXU | S_IRWXG | S_IRWXO, NULL,&fops, message);
	if (some_file)
	{
		pr_alert("Success\n");
		return 0;
	}
	return 42;
}

static void prochello_exit(void)
{
	remove_proc_entry("newprochello",NULL);
}

module_init(prochello_init);
module_exit(prochello_exit);
MODULE_LICENSE("GPL");

