#!/bin/bash

# Exp 1
$ ifconfig eth0 up
$ ifconfig eth0 172.16.30.254/24

# Exp 3
ifconfig eth1 up
ifconfig eth1 172.16.31.253/24

sysctl net.ipv4.ip_forward=1
sysctl net.ipv4.icmp_echo_ignore_broadcasts=0

# Exp 4
route add default gw 172.16.31.254