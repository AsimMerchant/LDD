#include "kernHeaders.h"

static unsigned char *ptr;
static unsigned char *pa;
static int entry(void)
{
	
	pr_alert("Size of struct page %ld\n",sizeof(struct page));

	pr_alert("Size of a page=%u\n",PAGE_SIZE);

	pr_alert("Page shift=%u\n",PAGE_SHIFT);

	pr_alert("Page mask=%x\n",PAGE_MASK);

	pr_alert("Number of physical pages=%ld\n",get_num_physpages());

	ptr=kmalloc(100,GFP_KERNEL);

	pr_alert("Logical addr=%lx\n",ptr);
	
	pr_alert("PAGE_OFFSET=%lx\n",PAGE_OFFSET);

	pr_alert("ptr-PAGE_OFFSET=%lx\n",ptr-PAGE_OFFSET);

	pa=(unsigned char *)__pa(ptr);
	pr_alert("Physical address=%lx\n",pa);
	return 0;
}

static void escape(void)
{
	kfree(ptr);
	pr_alert("Exit\n");
}

module_init(entry);
module_exit(escape);
MODULE_LICENSE("GPL");

