#!bin/bash
echo -----------------------------
cat /proc/cpuinfo | grep -i "Model" | sed -n '1p'
echo ---------------------------
cat /proc/meminfo | grep -i "MemTotal"
echo -----------------------------
##echo "System has been runing since"
last reboot | sed -n '1p'
echo ----------------------------
echo "number of active users"
who | wc -l
