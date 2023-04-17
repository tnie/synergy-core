#!/bin/bash

folder=$(cd "$(dirname "$0")";pwd)
echo $folder
#single
ps -ef | grep -v "grep" | grep "allSynergyRestart.sh"
if [ $? == 0 ]; then
  echo allSynergyRestart.sh is running.
  exit 1
fi
cd $folder
log=./allSynergyRestart.log
echo `date` run $0 ... | tee -a $log
./allSynergyRestart.sh | tee -a $log
echo -e `date` done $0 "\n" | tee -a $log
exit 0
