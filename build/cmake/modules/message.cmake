# @https://blog.csdn.net/u013250861/article/details/139332241
#[[
\033[1;31;40m    <!--1-高亮显示 31-前景色红色  40-背景色黑色-->
\033[0m          <!--采用终端默认设置，即取消颜色设置-->
显示方式
0                终端默认设置
1                高亮显示
4                使用下划线
5                闪烁
7                反白显示
8                不可见

前景色            背景色           颜色
---------------------------------------
30                40              黑色
31                41              红色
32                42              绿色
33                43              黃色
34                44              蓝色
35                45              紫红色
36                46              青蓝色
37                47              白色
]]

string(ASCII 27 Esc)
# Esc[0;31m
set(MSG_COLOR_RED "${Esc}[1;31m") # 红色
set(MSG_COLOR_GREEN "${Esc}[1;32m") # 绿色
set(MSG_COLOR_YELLOW "${Esc}[1;33m") # 黃色
# Esc[0m
set(MSC_COLOR_END "${Esc}[m") # 结束颜色设置
set(MSG_COLOR_BLUE "${Esc}[1;34m") # 蓝色高亮
#set(RB "${Esc}[1;31;40m") # 红色字体黑色背景
#message("${R}红色内容${E} 默认颜色")
#message("${B}蓝色内容${E} 默认颜色")
#message("${RB}红色字体黑色背景${E} 默认颜色")
macro(GFN_MESSAGE_INFO INPUT_TEXT)
message(STATUS "${MSG_COLOR_GREEN}${INPUT_TEXT}${MSC_COLOR_END}")
endmacro(GFN_MESSAGE_INFO)

macro(GFN_MESSAGE_WARN INPUT_TEXT)
message(STATUS "${MSG_COLOR_YELLOW}${INPUT_TEXT}${MSC_COLOR_END}")
endmacro(GFN_MESSAGE_WARN)

macro(GFN_MESSAGE_ERROR INPUT_TEXT)
message(STATUS "${MSG_COLOR_RED}${INPUT_TEXT}${MSC_COLOR_END}")
endmacro(GFN_MESSAGE_ERROR)

