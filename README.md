# xsmade

cd 3rdparty/wxWidgets
--git submodule update --init
--git submodule update --init --recursive

mkdir out && cd out
cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cmake --build .
