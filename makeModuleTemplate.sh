echo '
#include "kernHeaders.h"

static int entry(void)
{
	return 0;
}

static void escape(void)
{
	pr_alert("Exit\n");
}

module_init(entry);
module_exit(escape);
MODULE_LICENSE("GPL");
' > $1
