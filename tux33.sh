#!/bin/bash

# Exp 1
$ ifconfig eth0 up
$ ifconfig eth0 172.16.30.1/24

# Exp 3
route add -net  172.16.31.0/24 gw 172.16.30.254 

# Exp 4
route add default gw 172.16.30.254 