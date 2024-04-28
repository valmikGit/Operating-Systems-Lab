# Determining and Modifying Program Priority: Find out the priority of your running program 
# and modify it using the nice command.

#!/bin/bash

# Find out the priority of the running program
echo "Priority of the running program:"
ps -o pid,ppid,ni,pri,cmd | grep "$(basename "$0")"

# Modify the priority using the nice command
echo "Modifying priority of the running program..."
nice -n -10 "$0"
