#!/bin/bash

/system reset-configuration

# Exp 4
/ip address add address=172.16.2.59/24 interface=ether1
/ip address add address=172.16.31.254/24 interface=ether2