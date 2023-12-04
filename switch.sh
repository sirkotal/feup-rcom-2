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
