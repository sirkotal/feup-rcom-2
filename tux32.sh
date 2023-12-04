#!/bin/bash

# Exp 2
$ ifconfig eth0 up
$ ifconfig eth0 172.16.31.1/24

# Exp 3
route add -net  172.16.30.0/24 gw 172.16.31.253