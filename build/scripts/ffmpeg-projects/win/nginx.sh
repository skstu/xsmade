./configure --prefix=./installed/nginx \
            --add-module=./modules/nginx-http-flv-module-1.2.11 \
			--add-module=./modules/nginx-rtmp-module \
            --with-openssl=./deps/openssl-3.4.0 \
			--with-zlib=./deps/zlib \
			--with-pcre=./deps/pcre2
            
            
            #--without-http_rewrite_module