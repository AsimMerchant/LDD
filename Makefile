obj-m += hello.o
obj-m += hello1.o


KDIR=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules_install

clean:
	 $(MAKE) -C $(KDIR) M=$(PWD) clean 
