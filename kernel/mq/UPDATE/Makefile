# this is a minimal makefile for demo purposes, keep it that way...
obj-m:=mq.o
mq-objs:=main.o
V?=0
KDIR?=/lib/modules/$(shell uname -r)/build
# in an embedded system:
#KDIR:=[where the system maker gave me kernel headers+makefile or the kernel itself which has a makefile]
#ARCH:=arm
#CROSS_COMPILE:=[path+common prefix to where the toolchain is]
# You could also use W=2 and W=3 for more warnings but most kernel headers
# fail those...
W?=1

.PHONY: all
all: modules get put user print_state

.PHONY: modules
modules:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) W=$(W) modules
.PHONY: clean
clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) clean
	rm -f *.stamp
	rm -f put get user

.PHONY: insmod
insmod:
	sudo insmod ./mq.ko
	sleep 1
	sudo chmod 666 /dev/mq*

.PHONY: rmmod
rmmod:
	sudo rmmod mq

USER_CFLAGS:=-O2 -Wall -Werror -pedantic
put: put.c
	gcc $(USER_CFLAGS) -o $@ $< 
get: get.c
	gcc $(USER_CFLAGS) -o $@ $<
user: user.c
	gcc $(USER_CFLAGS) -o $@ $< -lpthread
print_state: print_state.c
	gcc $(USER_CFLAGS) -o $@ $< -lpthread
