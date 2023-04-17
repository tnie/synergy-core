#!/bin/bash

# 重新启动键鼠共享客户端
ps -ef | grep -v "grep" | grep "synergyc"
if [ $? == 0 ]; then
  pkill synergyc
  sleep 5
  ps -ef | grep -v "grep" | grep "synergyc"
  if [ $? == 0 ]; then
    echo -e "\033[31m kill synergyc failed. \033[0m"
    exit 1
  fi
  /startSynergy.sh &
  ps -ef | grep -v "grep" | grep "synergyc"
  if [ $? == 0 ]; then
    echo -e "\033[32m restart synergyc. \033[0m"
  else
    echo -e "\033[31m restart synergyc failed. \033[0m"
  fi
  exit 0
fi


# 重新启动键鼠共享服务端
ps -ef | grep -v "grep" | grep "synergys"
if [ $? == 0 ]; then
  pkill synergys
  sleep 5
  ps -ef | grep -v "grep" | grep "synergys"
  if [ $? == 0 ]; then
    echo -e "\033[31m kill synergys failed. \033[0m"
    exit 1
  fi
  /startSynergyS.sh &
  ps -ef | grep -v "grep" | grep "synergys"
  if [ $? == 0 ]; then
    echo -e "\033[32m restart synergys. \033[0m"
  else
    echo -e "\033[31m restart synergys failed. \033[0m"
  fi
  exit 0
fi

echo -e "\033[31m 没有找到键鼠共享程序. \033[0m"
exit 0

