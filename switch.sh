#!/bin/bash

/system reset-configuration

# Exp 2
/interface bridge add name=bridge30
/interface bridge add name=bridge31

/interface bridge port remove [find interface=ether1] 
/interface bridge port remove [find interface=ether2] 
/interface bridge port remove [find interface=ether3] 

/interface bridge port add bridge=bridge30 interface=ether1
/interface bridge port add bridge=bridge30 interface=ether2 
/interface bridge port add bridge=bridge31 interface=ether3

# Exp 3
/interface bridge port remove [find interface=ether4]
/interface bridge port add bridge=bridge31 interface=ether4

# Exp 4 -> connect the Router's eth1 to LANscape (P3.1) and eth2 to the Switch's eth5
/interface bridge port remove [find interface=ether5]
/interface bridge port add bridge=bridge31 interface=ether5   # switch the cable connected to the Switch's console to the Router's MTIK
