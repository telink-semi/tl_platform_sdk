程序打包命令：pyinstaller --onefile --name bin_pack bin_pack.py

一、add_head
(1)参数说明
第一参数：模式add_head
第二参数：输入bin路径
第三参数：输出bin路径
第四参数：16进制4byte数
第五参数：16进制4byte数
...
...
第n参数：16进制4byte数

(2)特殊字符识别
从第四参数开始，如果存在'auto_len'则会在对应头位置添加输入bin的大小（16进制4byte数）


二、combine_bin
第一参数：模式combine_bin
第二参数：输出bin路径
第三参数：输入bin1路径
第四参数：输入bin1偏移地址
第五参数：输入bin2路径
第六参数：输入bin2偏移地址
