#!/bin/bash

# Exp 2
$ ifconfig eth0 up
$ ifconfig eth0 172.16.31.1/24

# Exp 3
route add -net  172.16.30.0/24 gw 172.16.31.253

# Exp 4
route add default gw 172.16.31.254
# check step 2.3 #
sysctl net.ipv4.conf.eth0.accept_redirects=0
sysctl net.ipv4.conf.all.accept_redirects=0 

route del -net 172.16.30.0/24 gw 172.16.31.253

route add -net 172.16.30.0/24 gw 172.16.31.253 
sysctl net.ipv4.conf.eth0.accept_redirects=1
sysctl net.ipv4.conf.all.accept_redirects=1