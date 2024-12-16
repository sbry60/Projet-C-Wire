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

if [ "$#" -lt 3 ]; then
    echo "Erreur : Nombre d'arguments insuffisant."
    help_me
fi


if [[ "$*" == *"-h"* ]]; then
    help_me
fi

FILE=$1
TYPE_STATION=$2
TYPE_CONS=$3
ID_CENTRALE=${4:-"ALL"} 

max=

{
    read -r header
    while IFS=';' read -r col1 _; do
        if [ -n "$col1" ]; then
            if [ -z "$max" ]; then
                max=$col1
            elif [ "$col1" -gt "$max" ]; then
                max=$col1
            fi
        fi
    done
} < "$FILE"






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

if [[ "$ID_CENTRALE" -gt "$max"  ]]; then
    echo "Erreur : identifiant centrale incorrecte ($ID_CENTRALE)."
    help_me
fi

gcc -o projet projet.c
START_TIME=$(date +%s)

if [[ "$ID_CENTRALE" != "ALL" ]]; then
  
  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $2 != "-" && $4 == "-" && $7 == "-" ||$1==id && $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE | cut -d';' -f2,5,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv hvb_comp_$ID_CENTRALE.csv


  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $3 != "-" && $5 != "-" && $7 == "-" ||$1==id && $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,5,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv hva_comp_$ID_CENTRALE.csv
    


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $5 != "-" && $7 == "-" ||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,5,7,8 | tr '-' '0'| ./
    mv monfichier.csv lv_comp_$ID_CENTRALE.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $6 != "-" && $7 == "-"|| $1 == id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv lv_indiv_$ID_CENTRALE.csv

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $7 == "-"||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet
  mv monfichier.csv lv_all_$ID_CENTRALE.csv
  LV=lv_all_$ID_CENTRALE.csv

  else
  echo "Erreur"

  fi
else
  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE| cut -d';' -f2,5,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv hvb_comp.csv


  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$3 != "-" && $5 != "-" && $7 == "-" || $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,5,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv hva_comp.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$4 != "-" && $5 != "-" && $7 == "-" ||$3 != "-" && $4 != "-" && $8 == "-"' $FILE| cut -d';' -f4,5,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv lv_comp.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    awk -F';'  '$4 != "-" && $6 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet
    mv monfichier.csv lv_indiv.csv

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  awk -F';' '$4 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,6,7,8 | tr '-' '0'| ./projet
  mv monfichier.csv lv_all.csv
  LV=lv_all.csv

  else
  echo "Erreur"

  fi
fi

if [ -f "$LV" ]; then
  (tail -n +2 $LV | sort -t';'  -k2,2 $LV) > lv_all_triee.csv |gnuplot << EOF
  set terminal png
  set output "graph.png"
  set datafile separator ';'
  set title "Graphique Exemple"
  set xlabel "X-axis"
  set ylabel "Y-axis"
  set grid
  plot "lv_all_triee.csv" using 1:2 with lines title "Valeur1"
EOF

    
fi
END_TIME=$(date +%s)
DURATION=$((END_TIME - START_TIME))
echo "Traitement terminé en $DURATION secondes."
