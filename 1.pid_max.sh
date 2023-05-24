#!/bin/bash

max_pid=$(cat /proc/sys/kernel/pid_max)

echo "Maximum PID value : $max_pid"
