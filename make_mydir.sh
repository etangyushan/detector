#!/bin/sh
mkdir -p /root/detector
mkdir -p /root/detector/log
mkdir -p /root/detector/before_transform
mkdir -p /root/detector/after_transform
mkdir -p /root/detector/match
mkdir -p /root/detector/policy
touch /root/detector/log/filematch.log 
touch /root/detector/log/filenomatch.log 
touch /root/detector/log/client.log 
touch /root/detector/log/computerstate.log 
touch /root/detector/policy/keyword.plc
