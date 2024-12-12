#!/bin/bash


function help_me {
    echo "Utilisation : <chemin_du_fichier_csv> <type_station> <type_consommateur> [id_centrale] [-h]"
    echo "Options :"
    echo "  <chemin_du_fichier_csv>   : Chemin obligatoire vers le fichier CSV."
    echo "  <type_station>            : Type de station à analyser (hvb, hva, lv)."
    echo "  <type_consommateur>       : Type de consommateur (comp, indiv, all)."
    echo "  [id_centrale]             : (Optionnel) Filtre pour une centrale spécifique."
    echo "  -h                        : Affiche cette aide."
    exit 0
}
gcc -o projet projet.c
FILE=$1
TYPE_STATION=$2
TYPE_CONS=$3
ID_CENTRALE=${4:-"ALL"} 



START_TIME=$(date +%s)




if [ ! -f "$FILE" ]; then
    echo "Erreur : Le fichier $FILE n'existe pas."
    help_me
    exit 1
fi
if [[ "$TYPE_STATION" != "hvb" && "$TYPE_STATION" != "hva" && "$TYPE_STATION" != "lv" ]]; then
    echo "Erreur : Type de station incorrecte ($TYPE_STATION)."
    help_me
fi

if [[ "$TYPE_CONS" != "comp" && "$TYPE_CONS" != "indiv" && "$TYPE_CONS" != "all" ]]; then
    echo "Erreur : Type de consommateur invalide ($TYPE_CONSUMER)."
    help_me
fi




if [[ "$ID_CENTRALE" != "ALL" ]]; then
  
  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $2 != "-" && $4 == "-" && $7 == "-" ||$1==id && $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE | cut -d';' -f2,5,7,8 | tr '-' '0'| ./projet


  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $3 != "-" && $5 != "-" && $7 == "-" ||$1==id && $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,5,7,8 | tr '-' '0'| ./projet


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $5 != "-" && $7 == "-" ||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,5,7,8 | tr '-' '0'| ./projet


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $6 != "-" && $7 == "-"|| $1 == id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $7 == "-"||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet

  else
  echo "Erreur"

  fi
else
  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE| cut -d';' -f2,5,7,8 | tr '-' '0'| ./projet


  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$3 != "-" && $5 != "-" && $7 == "-" || $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,5,7,8 | tr '-' '0'| ./projet


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$4 != "-" && $5 != "-" && $7 == "-" ||$3 != "-" && $4 != "-" && $8 == "-"' $FILE| cut -d';' -f4,5,7,8 | tr '-' '0'| ./projet


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    awk -F';'  '$4 != "-" && $6 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  awk -F';' '$4 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet

  else
  echo "Erreur"

  fi
fi

END_TIME=$(date +%s)
DURATION=$((END_TIME - START_TIME))
echo "Traitement terminé en $DURATION secondes."
