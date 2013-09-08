luvdbie: main.c deps/libuv/libuv.a deps/leveldb/leveldb-1.11.0/libleveldb.a
	gcc -I deps/libuv/include -o luvdbie main.c \
deps/libuv/libuv.a  deps/leveldb/leveldb-1.11.0/libleveldb.a -lrt -lm -lpthread
 
deps/libuv/libuv.a:
	$(MAKE) -C deps/libuv
 
deps/leveldb/leveldb-1.11.0/libleveldb.a:
	$(MAKE) -C deps/leveldb/leveldb-1.11.0

clean:
	rm luvdbie
	$(MAKE) clean deps/leveldb/leveldb-1.11.0

