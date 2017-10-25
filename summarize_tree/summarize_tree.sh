#!/bin/sh

cd $1       #go to the current address

file=$(find . -type f|wc -l)  #get the number of regular files
dir=$(find  . -type d|wc -l)  #get the number of directories

#print out
echo "There were $dir directories."
echo "There were $file regular files."
