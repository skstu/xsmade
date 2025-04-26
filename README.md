# xsmade
cp /home/ponyo/Desktop/projects/xsmade/bin/browser.zip /home/docker/browserRpc/fpbrowser/
cp /home/ponyo/Desktop/projects/xsmade/bin/components/libbrwsvr.so /home/docker/browserRpc/fpbrowser/components/libbrwsvr.so

docker run --memory="8g" --cpus="4" --shm-size="1g" --mem_limit="4g" -p 9218:9218 -p 8888:8888 -it dev1

# ssh -L 0.0.0.0:9223:localhost:9222 localhost -N
docker run --memory="2g" --cpus="2" -p 9218:9218 -p 7778:7778 -it dev1 /bin/bash
docker run -d --name chromium-container --memory="2g" --cpus="2" your-chromium-image
zip -r /home/ponyo/Desktop/projects/xsmade/bin/brw[25421-1].zip /home/ponyo/Desktop/projects/xsmade/bin/ -x "/path/to/directory/exclude_this_folder/*"

../build/scripts/linux/install-chrome.sh
scp ../bin/brw[25418-3].zip panda@10.100.4.15:/home/panda/cppdev
scp ../bin/brw[25418-3].zip panda@10.100.4.15:/home/panda/goprojects/wul-svc/cppdev

cd 3rdparty/wxWidgets
--git submodule update --init
--git submodule update --init --recursive

mkdir out && cd out
cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cmake --build .


/home/ponyo/Desktop/projects/chromium_dev/130.0.6723.116/src/third_party/llvm-build/Release+Asserts


无头浏览器启动命令
```
docker exec -it browser /bin/bash

./fpbrowser/browser/chromium/130.0.6723.116/chrome --no-sandbox --remote-debugging-port=9222 --disable-gpu --headless=new --log-file=./chromium_log.log 

./fpbrowser/browser/chromium/130.0.6723.116/chrome --no-sandbox --remote-debugging-port=9222 --disable-gpu --headless=new --log-file=./chromium_log.log --remote-debugging-address=0.0.0.0

```

ppt应用去移动
```
./cloud-manager-linux.app --port=9292 --url=ws://127.0.0.1:9222/devtools/browser/069492a9-35be-4e13-9ba6-1b5b66babc7c
```

端口转发指令
```
ssh -L 0.0.0.0:9223:localhost:9222 localhost -N
```


安装工具
```
# ssh转发支持
apt install ssh

# netstat指令支持
apt install net-tools

# killall支持
apt install psmisc
```

排查命令
```
docker exec -it browser /bin/bash

curl http://127.0.0.1:9222/json
curl http://127.0.0.1:9222/json/version

# 9222端口是否支持0.0.0.0
netstat -tuln | grep 9222

#
cat /app/logs/cloud-manager.log








gin" "--no-tags"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/wasm_tts_engine/src failed; will retry after a short nap...
177>WARNING: subprocess '"git" "-c" "core.deltaBaseCacheLimit=512m" "fetch" "origin" "--no-tags"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/vulkan-tools/src failed; will retry after a short nap...
180>WARNING: subprocess '"git" "-c" "core.deltaBaseCacheLimit=512m" "fetch" "origin" "--no-tags"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/vulkan_memory_allocator failed; will retry after a short nap...
183>WARNING: subprocess '"git" "-c" "core.deltaBaseCacheLimit=512m" "fetch" "origin" "--no-tags"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/wayland-protocols/kde failed; will retry after a short nap...
189>WARNING: subprocess '"git" "-c" "core.deltaBaseCacheLimit=512m" "clone" "--no-checkout" "--progress" "https://chromium.googlesource.com/webpagereplay.git" "/home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/_gclient_webpagereplay_u_rcunu9"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165 failed; will retry after a short nap...
191>WARNING: subprocess '"git" "-c" "core.deltaBaseCacheLimit=512m" "fetch" "origin" "--no-tags"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/weston/src failed; will retry after a short nap...
193>WARNING: subprocess '"git" "-c" "core.deltaBaseCacheLimit=512m" "fetch" "origin" "--no-tags"' in /home/ponyo/Desktop/projects/chromium/134.0.6998.165/src/third_party/xdg-utils failed; will retry after a short nap...

