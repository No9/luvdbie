luvdbie: main.c libuv/libuv.a
	gcc -I libuv/include \
-lrt -lm -lpthread -o \
luvdbie main.c \
libuv/libuv.a -lpthread
 
libuv/libuv.a:
	$(MAKE) -C libuv
 
clean:
	rm libuv/libuv.a
	rm luvdbie
