#Les HVB
awk -F';' '$2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"{print $2, $7}' "cwire.dat"
#Les HVA
awk -F';' '$2 != "-" && $3 != "-" && $4 == "-" ' "cwire.dat"
#les postes LV
awk -F';' '$3 != "-" && $4 != "-" && $8 == "-"' "cwire.dat"
#les consommateurs des HVB
awk -F';' '$2 != "-" && $4 == "-" && $7 == "-"' "cwire.dat"
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
  awk -F';' '$2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | tr '-' '0'

  echo "consommateurs"
  # Les consommateurs des HVB
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-"' "cwire.dat" | tr '-' '0'

elif [[ "$1" == "hva" ]] && [[ "$2" == "comp" ]]; then

  echo "HVA COMP"
  # Les HVA
  awk -F';' '$2 != "-" && $3 != "-" && $4 == "-"' "cwire.dat" | tr '-' '0'

  echo "consommateurs"
  # Les consommateurs des HVA
  awk -F';' '$3 != "-" && $5 != "-" && $7 == "-"' "cwire.dat" | tr '-' '0'

elif [[ "$1" == "lv" ]] && [[ "$2" == "comp" ]]; then

  echo "LV COMP"
  # Les postes LV
  awk -F';' '$3 != "-" && $4 != "-" && $8 == "-"' "cwire.dat" | tr '-' '0'

  echo "consommateurs"
  # Les consommateurs entreprises des postes LV
  awk -F';' '$4 != "-" && $5 != "-" && $7 == "-"' "cwire.dat" | tr '-' '0'

elif [[ "$1" == "lv" ]] && [[ "$2" == "indiv" ]]; then

  echo "LV INDIV"
  # Les postes LV
  awk -F';' '$3 != "-" && $4 != "-" && $8 == "-"' "cwire.dat" | tr '-' '0'

  echo "consommateurs"
  # Les consommateurs individuels des postes LV
  awk -F';' '$4 != "-" && $6 != "-" && $7 == "-"' "cwire.dat" | tr '-' '0'

else
  echo "Erreur, veuillez entrer des arguments valides"
  exit 1
fi


