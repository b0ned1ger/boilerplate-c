obj-m := boilcpu.o
boilmod-objs := bouilcpu.o 

obj-m := boilparent.o

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
