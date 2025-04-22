# xsmade
# ssh -L 0.0.0.0:9223:localhost:9222 localhost -N


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



mouseEvent dispatch……
/snapshot/chromeV/node_modules/puppeteer-core/lib/cjs/puppeteer/cdp/IsolatedWorld.js:73
        const error = new Error('Execution context was destroyed');
                      ^

Error: Execution context was destroyed
    at #waitForExecutionContext (/snapshot/chromeV/node_modules/puppeteer-core/lib/cjs/puppeteer/cdp/IsolatedWorld.js:73:23)
    at IsolatedWorld.evaluate (/snapshot/chromeV/node_modules/puppeteer-core/lib/cjs/puppeteer/cdp/IsolatedWorld.js:98:58)
    at CdpFrame.title (/snapshot/chromeV/node_modules/puppeteer-core/lib/cjs/puppeteer/api/Frame.js:888:47)
    at CdpFrame.<anonymous> (/snapshot/chromeV/node_modules/puppeteer-core/lib/cjs/puppeteer/util/decorators.js:109:27)
    at CdpPage.title (/snapshot/chromeV/node_modules/puppeteer-core/lib/cjs/puppeteer/api/Page.js:1092:43)
    at TabManager.getAllPagesInfoByBrowserId (/snapshot/chromeV/testCore.js)
    at async CloudManager.handleUpdateTabs (/snapshot/chromeV/testCore.js)

