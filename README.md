The Treasure Box Library
========================

TBOX is a mutli-platform c library for unix, windows, mac, ios, android, etc.

It includes asio, stream, network, container, algorithm, object, memory, database, string, charset, math, libc, libm, utils and other library modules.


features
--------

### the stream io library
-	supports file, data, http and socket source
-	supports the stream filter for gzip charset and ..
-	implements the multi-stream transfer using asio	

### the asynchronous io library
-	supports reactor and proactor mode
-	using epoll, poll, select ,kqueue and iocp os system api

### the database library
-	supports mysql and sqlite3 database and enumerates data using the iterator mode

### the xml parser library
-	supports DOM and SAX mode and supports xpath.

### the serialization and deserialization library. 
-	supports xml, json, bplist, xplist, binary formats

### the memory library
-	implements some memory pools for optimizating memory.
-	supports fast memory error detecting. it can detect the following types of bugs for the debug mode:
 - out-of-bounds accesses to heap and globals
 - use-after-free
 -	double-free, invalid free
 -	memory leaks

### the container library
-	implements hash table, single list, double list, vector, stack, queue
	and min/max heap. supports iterator mode for algorithm.

### the algorithm library
-	using the iterator mode
-	implements find, binary find and reverse find algorithm.
-	implements sort, bubble sort, quick sort, heap sort and insert sort algorithm. 
-	implements count, walk items, reverse walk items, for_all and rfor_all.

### the network library
-	implements dns(cached), ssl(openssl and polarssl), http and cookies
-	supports asynchronous io mode for dns, ssl and http using the asio and stream library

### the platform library
-	implements timer, faster and lower precision timer
-	implements atomic and atomic64 operation
-	implements spinlock, mutex, event, semaphore, thread and thread pool 
-	implements file, socket operation

### the charset library
-	supports utf8, utf16, gbk, gb2312, uc2 and uc4
-	supports big endian and little endian mode

### the zip library
-	supports gzip, zlibraw, zlib formats using the zlib library if exists
-	implements lzsw, lz77 and rlc algorithm

### the utils library
-	implements base32, base64, md5 and sha algorithm
-	implements assert and trace output for the debug mode

### the math library
-	implements random generator
-	implements fast fixed-point calculation, supports 6-bits, 16-bits, 30-bits fixed-point number

### the libc library
-	implements lightweight libc library interfaces, the interface name contains tb_xxx prefix for avoiding conflict.
-	implements strixxx strrxxx wcsixxx wcsrxxx interface extension.
-	optimizates some frequently-used interface, .e.g. memset, memcpy, strcpy ... 
-	implements memset_u16, memset_u32, memset_u64 extension interfaces.

### the libm library
-	implements lightweight libm library interfaces, the interface name contains tb_xxx prefix for avoiding conflict.
-	supports float and double type.

contact
-------

- email:   	    
	- waruqi@gmail.com
	- waruqi@126.com
- source:  	    
	- [github](https://github.com/waruqi/tbox)
	- [coding](https://coding.net/u/waruqi/p/tbox/git)
	- [oschina](http://git.oschina.net/tboox/tbox)
- website: 	    
	- http://www.tboox.org
	- http://www.tboox.net
- download:
 	- [github](https://github.com/waruqi/tbox/archive/master.zip)
 	- [coding](https://coding.net/u/waruqi/p/tbox/git/archive/master)
 	- [oschina](http://git.oschina.net/tboox/tbox/repository/archive?ref=master)
- document:
	- [github](https://github.com/waruqi/tbox/wiki/)
	- [oschina](http://git.oschina.net/tboox/tbox/wikis/home)
- qq(group):    
	- 343118190

donate
------

####alipay
<img src="http://www.tboox.net/ruki/alipay.png" alt="alipay" width="128" height="128">

####paypal
<a href="http://tboox.net/%E6%8D%90%E5%8A%A9/">
<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif" alt="paypal">
</a>

build
-----

please install xmake first: [xmake](https://github.com/waruqi/xmake)


```bash
	// build for the host platform
    cd ./tbox
    xmake

	// build for the iphoneos platform
    cd ./tbox
    xmake f -p iphoneos 
    xmake
    
	// build for the android platform
    cd ./tbox
    xmake f -p android --ndk=xxxxx
    xmake
```

example
-----------
```c
    #include "tbox/tbox.h"

    int main(int argc, char** argv)
    {
        /* init tbox
         *
         * @param priv      the platform private data
         *                  pass JNIEnv* env for android
         *                  pass tb_null for other platform
         * @param data      the memory data for the memory pool, uses the native memory if be tb_null
         * @param size      the memory size for the memory pool, uses the native memory if be zero
         *
         * for android:     tb_init(jenv, tb_null, 0)
         * for memory pool: tb_init(tb_null, malloc(10 * 1024 * 1024), 10 * 1024 * 1024);
         */
        if (!tb_init(tb_null, tb_null, 0)) return 0;

        // print info with tag
        tb_trace_i("hello tbox");

        // print info only for debug
        tb_trace_d("hello tbox"); 

        // print error info
        tb_trace_e("hello tbox");

        // init stream
        tb_stream_ref_t stream = tb_stream_init_from_url("http://www.xxxx.com/index.html");
        if (stream)
        {
            // save stream data to file
            tb_transfer_done_to_url(stream, "/home/file/index.html", 0, tb_null, tb_null);

            // exit stream
            tb_stream_exit(stream);
        }

        // block: save http to file
        tb_transfer_done_url("http://www.xxxx.com/index.html", "/home/file/index.html", 0, tb_null, tb_null);

        // async: save http to file for windows path
        tb_transfer_pool_done(tb_transfer_pool(), "http://www.xxxx.com/index3.html", "c:/home/file/index4.html", 0, 0, tb_null, tb_null, tb_null);

        // async: save http to file for unix path
        tb_transfer_pool_done(tb_transfer_pool(), "http://www.xxxx.com/index0.html", "/home/file/index0.html", 0, 0, tb_null, tb_null, tb_null);
        tb_transfer_pool_done(tb_transfer_pool(), "http://www.xxxx.com/index1.html", "/home/file/index2.html", 0, 0, tb_null, tb_null, tb_null);
        tb_transfer_pool_done(tb_transfer_pool(), "http://www.xxxx.com/index2.html", "/home/file/index3.html", 0, 0, tb_null, tb_null, tb_null);

        // wait some time
        getchar();

        // exit tbox
        tb_exit();
        return 0;
    }
```


