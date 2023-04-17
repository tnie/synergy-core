#!/bin/bash

# 检测当前设备的键鼠共享程序，检测完毕后将 debugSynergy*.log 文件提交
# 如果需要检测多个设备上的键鼠共享程序，方法有二：
# 1）在每个设备上分别执行当前脚本；
# 2）或者使用 ./check5Synergy.sh （可能需要修改）

log=debugSynergy_$(date +%y%m%d%H%M%S).log
bash ./checkSynergy.sh  | tee -a $log
