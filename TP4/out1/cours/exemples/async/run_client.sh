#!/bin/bash

for i in `seq 1 40`; do 
   ( sleep $[$RANDOM % 3] ; ./count_client 127.0.0.1 9998 1 &)
done
