#!/bin/bash

gcc -o projet projet.c 
if [[ "$1" == "hvb" ]] && [[ "$2" == "comp" ]]; then 
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" {print $2,$5,$8}' "cwire.dat"
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "comp" ]]; then 
  awk -F';' '$3 != "-" && $5 != "-" && $7 == "-" {print $3,$5,$8}' "cwire.dat"
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "comp" ]]; then 
  awk -F';' '$4 != "-" && $5 != "-" && $7 == "-" {print $4,$5,$8}' "cwire.dat"
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "indiv" ]]; then 
  awk -F';' '$4 != "-" && $6 != "-" && $7 == "-"' "cwire.dat" | cut -d';' -f4,6,8 | ./projet
  
fi
