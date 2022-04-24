obj-m := boilio.o
boilmod-objs := bouilio.o 

obj-m += boilrtc.o

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
