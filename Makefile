luvdbie: main.c libuv/libuv.a
	gcc -I deps/libuv/include -o luvdbie main.c \
deps/libuv/libuv.a -lrt -lm -lpthread
 
libuv/libuv.a:
	$(MAKE) -C deps/libuv
 
clean:
	rm deps/libuv/libuv.a
	rm luvdbie
