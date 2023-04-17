#!/bin/bash

date
ifconfig
synergyc --version
cat /startSynergy.sh
synergys --version
cat /startSynergyS.sh
# 使用前请确认实际环境中 ip 地址是否与脚本中一致，请按需修改：
# 修改脚本 ip 地址时，可能需要同时修改 ./check5Synergy.sh
ping -c 4 192.168.3.29
ping -c 4 192.168.3.30
ping -c 4 192.168.3.31
ping -c 4 192.168.3.41
tac /var/log/messages | grep -iwm1000 'synergy\|Time'

