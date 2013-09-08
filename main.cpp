#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <uv.h>
#include <unistd.h>
#include "leveldb/db.h"

uv_loop_t *loop;
leveldb::DB* db;

uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size) {
    return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void luvdbie_write(uv_write_t *req, int status) {
    if (status == -1) {
        fprintf(stderr, "Write error %s\n", uv_err_name(uv_last_error(loop)));
    }
    char *base = (char*) req->data;
    free(base);
    free(req);
}

void luvdbie_read(uv_stream_t *client, ssize_t nread, uv_buf_t buf) {
    if (nread == -1) {
        if (uv_last_error(loop).code != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(uv_last_error(loop)));
        uv_close((uv_handle_t*) client, NULL);
        return;
    }
    uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
    req->data = (void*) buf.base;
    buf.len = nread;
    char messagetype = buf.base[0];
    unsigned int keylength = 0;
    unsigned int valuelength = 0;
    unsigned int curPos = 2;
    //Ignore message type and first !
    std::string keyl;
    //std::string vall;
    for(int i = 2; i < 32; i++){ 
        if(buf.base[i] == '!') {
           if(keylength == 0) {
              keyl = std::string(buf.base + curPos, buf.base + i);
              keylength = atoi(keyl.c_str());
              curPos = i + 1;  
              
              std::cout << "key: " << keyl << "$" << std::endl; 
              break;        
           }
        }
    }

   //Test for empty key and empty value....
   leveldb::Status s = db->Put(leveldb::WriteOptions(), 
                               std::string(buf.base + curPos, keylength), 
                               std::string(buf.base + curPos + keylength, buf.len));
    
   uv_write(req, client, &buf, 1, luvdbie_write);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status == -1) {
        // error!
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, luvdbie_read);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}


#define OPTIONS "c"
int main(int argc, char *argv[]) {
    // Open database
    char c; //for managing getopt
    while ((c = getopt(argc, argv, OPTIONS)) != -1){
        switch (c) {
           case 'c':
              break;
        }       
    }
    
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in bind_addr = uv_ip4_addr("0.0.0.0", 8085);
    uv_tcp_bind(&server, bind_addr);
    int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_err_name(uv_last_error(loop)));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}
