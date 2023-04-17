#!/bin/bash

# 检测多个设备的键鼠共享程序，检测完毕后将 debugSynergy*.log 文件提交
# 如果只需要检测当前设备上的键鼠共享程序，更建议使用：
# 1）使用 ./check1Synergy.sh

# 使用前请确认实际环境中 ip 地址是否与脚本中一致，请按需修改：
# 修改脚本 ip 地址时，需要同时修改 ./checkSynergy.sh

log=debugSynergy_$(date +%y%m%d%H%M%S).log
echo $log
# 键鼠共享客户端，一般为综合显控等
ssh root@192.168.3.29 < ./checkSynergy.sh  | tee -a $log

ssh root@192.168.3.30 < ./checkSynergy.sh | tee -a $log

ssh root@192.168.3.31 < ./checkSynergy.sh | tee -a $log

# 键鼠共享服务器，一般为 zht
ssh root@192.168.3.41 < ./checkSynergy.sh | tee -a $log

