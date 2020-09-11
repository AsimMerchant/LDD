//Added 21/04/2020
#include <linux/init.h>
#include <linux/module.h>
//Added 28/04/2020
#include <linux/version.h>	// kernel version stamp
#include <linux/kernel.h>	// resolve kernel symbol calls
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include<linux/printk.h>
#include<linux/mm.h>
//Added 11/9/2020
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include<linux/cdev.h>
