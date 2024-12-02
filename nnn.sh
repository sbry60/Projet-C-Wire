#Les HVB
awk -F';' '$2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat"
#les consommateurs des HVB
awk -F';' '$2 != "-" && $4 == "-" && $7 == "-"' "cwire.dat"
#les postes LV
awk -F';' '$3 != "-" && $4 != "-" && $8 == "-"' "cwire.dat"
#Les consommateurs des HVA
awk -F';' '$3 != "-" && $5 != "-" && $7 == "-"' "cwire.dat"
#Les consommateurs indiviuels des postes LV
awk -F';' '$4 != "-" && $6 != "-" && $7 == "-"' "cwire.dat"
#Les consommateurs entreprises des postes LV
awk -F';' '$4 != "-" && $5 != "-" && $7 == "-"' "cwire.dat"




#!/bin/bash

if [[ "$1" == "hvb" ]] && [[ "$2" == "comp" ]]; then 
  echo "HVB COMP"

  # Les HVB
  awk -F';' '$2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" |  sed 's/;-//g; s/-;//g'


  echo "comssommmateurs"
  # Les consommateurs des HVB
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-"' "cwire.dat"
fi

