obj-m += chardev.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all: chardev ioctl_program

chardev:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

ioctl_program: ioctl_program.c
	gcc -o ioctl_program ioctl_program.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -f ioctl_program

