luvdbie: main.cpp deps/libuv/libuv.a deps/leveldb/leveldb-1.11.0/libleveldb.a
	g++ -I deps/libuv/include -I deps/leveldb/leveldb-1.11.0/include -o luvdbie main.cpp \
deps/libuv/libuv.a  deps/leveldb/leveldb-1.11.0/libleveldb.a -lrt -lm -lpthread 
 
deps/libuv/libuv.a:
	$(MAKE) -C deps/libuv
 
deps/leveldb/leveldb-1.11.0/libleveldb.a:
	$(MAKE) -C deps/leveldb/leveldb-1.11.0

clean:
	rm luvdbie
	rm deps/leveldb/leveldb-1.11.0/libleveldb.a
	rm deps/libuv/libuv.a
