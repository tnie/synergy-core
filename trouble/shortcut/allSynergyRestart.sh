#!/usr/bin/expect

set timeout 20

# 键鼠共享客户端
spawn ssh root@192.168.3.29 "pkill synergyc ; /startSynergy.sh"
expect  {
  "yes/no"  { send "yes\r"; exp_continue }
  "ssword:" { send "passw0rd\r" }
}

spawn ssh root@192.168.3.30 "pkill synergyc ; /startSynergy.sh"
expect  {
  "yes/no"  { send "yes\r"; exp_continue }
  "ssword:" { send "passw0rd\r" }
}

spawn ssh root@192.168.3.31 "pkill synergyc ; /startSynergy.sh"
expect  {
  "yes/no"  { send "yes\r"; exp_continue }
  "ssword:" { send "passw0rd\r" }
}
# 键鼠共享服务器
#spawn ssh root@192.168.3.41 "pkill synergys ; /startSynergyS.sh"
spawn ssh root@192.168.3.41 "pkill synergys ; /startSynergy.sh"
expect  {
  "yes/no"  { send "yes\r"; exp_continue }
  "ssword:" { send "passw0rd\r" }
}
# 避免执行不完
sleep 2
