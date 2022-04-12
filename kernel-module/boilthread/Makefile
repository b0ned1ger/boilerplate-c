obj-m := boilthread.o
boilmod-objs := bouilthread.o 

obj-m := boilthread.o

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
