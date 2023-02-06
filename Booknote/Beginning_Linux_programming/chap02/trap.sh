#! /bin/bash

trap 'rm -f /tmp/my_trap_file_$$' INT
echo cteating file /tmp/my_trap_file_$$
date > /tmp/my_trap_file_$$

echo 'press interrupt (CTRL-C) to interrupt ...'
while [ -f /tmp/my_trap_file_$$ ]; do
        echo File exists
        sleep 1
done    
echo The file no longer exists

Trap INT
echo cerating file /tmp/my_trap_file_$$
date > /tmp/my_trap_file_$$

echo "press interrupt (control-c) to interrupt ..."
while [ -f /tmp/my_trap_file_$$ ]; do
        echo File exists
        sleep 1
done    

echo we never get here
return
