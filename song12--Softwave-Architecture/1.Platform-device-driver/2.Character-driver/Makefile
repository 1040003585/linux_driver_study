obj-m := character-driver_p.o

# obj-m += character-driver_p.o            #generate module file
CURRENT_PATH := $(shell pwd)             #current path	
LINUX_KERNEL := $(shell uname -r)        #kernel version

# you ubuntu system kernel code path
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)

# $make: build and output .ko file
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

# $make clean: clean obj and bin file
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean 

