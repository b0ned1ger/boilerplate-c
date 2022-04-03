obj-m := boilmod.o boilmod2.o
boilmod-objs := hello.o func.o

obj-m += boilmod2.o

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

