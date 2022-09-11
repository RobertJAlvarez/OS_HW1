##!bin/bash
echo -----------------------------
echo "Number of active users"
who | wc -l
echo -----------------------------
echo "System has been runing sice"
last reboot | sed -n '1p'
echo -----------------------------
cat /proc/cpuinfo | grep -i "Model" | sed -n '1p'
echo ---------------------------
cat /proc/meminfo | grep -i "MemTotal"
echo -----------------------------
