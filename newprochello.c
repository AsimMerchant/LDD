#include "kernHeaders.h"

struct proc_dir_entry *some_file; 
char *message=NULL;
int len;
int prochello_open (struct inode *_inode, struct file *_file)
{
	pr_alert("Opened\n");
	return 0;
}

int prochello_close (struct inode *_inode, struct file *_file)
{
	pr_alert("Closed\n");
	return 0;
}


ssize_t prochello_read (struct file *_file, char __user *udata, size_t size, loff_t *offset)
{
	int err,data_size;
	char *data=PDE_DATA(file_inode(_file));
	
	pr_alert("Read Operation performed in %s and offset at this point is %d\n",__func__, (int)(*offset));
	if(size==0)
	{
		pr_alert("Nothing to read-read call will end here\n");
		return size;
	}
	if((int)(*offset)>len)
		return 0;
	
	data_size=strlen(data);
	pr_alert("Requested read size=%d===size of the message Buffer(len) during initialization=%d===Size of data(data_size) when read from inode =%d\n",(int)size, len,data_size);
	err=copy_to_user(udata,data,len+1);
	if(err)
		pr_alert("Error in copy_to_user");
	else
		pr_alert("Success copy_to_user");
	*offset=len+1;
	return len+1;
}

ssize_t prochello_write (struct file *_file, const char __user *udata, size_t size, loff_t *offset)
{
	char *data=PDE_DATA(file_inode(_file));
	int err,i;
	pr_alert("Offset at the time of write=%d",(int)(*offset));
	pr_alert("Requested write data size(size)=%d",(int)size);
	if((int)size==0)
	{
		pr_alert("Requested write is 0 so we terminate the call here");
		return size;
	}
	if(udata==NULL)
	{
		pr_alert("No data from user as udata = NULL");
		return 0;
	}
	
	err=copy_from_user(data,udata,size+1);
	if(err)
		pr_alert("eror copy_from_user");
	else
		pr_alert("Success copy_from_user");
	for(i=0;i<size;i++)
	{
		pr_alert("%c ",udata[i]);
	}
	data[size]='\0';
	len=size;
	*offset=size;
	return size-err;
}

static struct file_operations fops = {

.open = prochello_open,
.read = prochello_read,
.write = prochello_write,
.release = prochello_close,

};

static int prochello_init(void)
{
	char *data="First invocation after loading";
	message=kmalloc(1024,GFP_KERNEL); // always use macros to define size
	len=strlen(data);
	strncpy(message,data,len+1);
	message[len]='\0';
	pr_alert("message[len]=%c",message[len]);
	pr_alert("message[len-1]=%c",message[len-1]);
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

