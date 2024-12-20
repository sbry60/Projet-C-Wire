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

if [[ "$ID_CENTRALE" -gt "$max"  ]]; then
    echo "Erreur : identifiant centrale incorrecte ($ID_CENTRALE)."
    help_me
fi
make -C codeC
if [ ! -f ./codeC/exec ]; then
    echo "L'exécutable n'existe pas."
    exit 1
fi
if [ ! -r ./codeC/exec ]; then
    echo "L'exécutable ne peut pas être lu."
   exit 1
fi

if [ ! -x ./codeC/exec ]; then
   echo "L'exécutable ne peut pas être exécuté."
    exit 1
fi

START_TIME=$(date +%s)
if [ -d "tmp" ]; then
    rm -rf "tmp"
fi
if [ -d "graphs" ]; then
    rm -rf "graphs"
fi
if [ -d "test" ]; then
    rm -rf "test"
fi

mkdir tmp graphs test
if [[ "$ID_CENTRALE" != "ALL" ]]; then

  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $2 != "-" && $4 == "-" && $7 == "-" ||$1==id && $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE | cut -d';' -f2,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/hvb_comp_$ID_CENTRALE.csv
    sort -t';' -k2,2n test/hvb_comp_$ID_CENTRALE.csv -o test/hvb_comp_$ID_CENTRALE.csv


  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $3 != "-" && $5 != "-" && $7 == "-" ||$1==id && $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/hva_comp_$ID_CENTRALE.csv
    sort -t';' -k2,2n test/hva_comp_$ID_CENTRALE.csv -o test/hva_comp_$ID_CENTRALE.csv



  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $5 != "-" && $7 == "-" ||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/lv_comp_$ID_CENTRALE.csv
    sort -t';' -k2,2n test/lv_indiv_$ID_CENTRALE.csv -o test/lv_indiv_$ID_CENTRALE.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $6 != "-" && $7 == "-"|| $1 == id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| make -C ./codeC/exec
    mv test/monfichier.csv test/lv_indiv_$ID_CENTRALE.csv
    sort -t';' -k2,2n test/lv_indiv_$ID_CENTRALE.csv -o test/lv_indiv_$ID_CENTRALE.csv

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $7 == "-"||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
  mv test/monfichier.csv test/lv_all_$ID_CENTRALE.csv
  sort -t';' -k2,2n test/lv_all_$ID_CENTRALE.csv -o test/lv_all_$ID_CENTRALE.csv
  LV=test/lv_all_$ID_CENTRALE.csv

  else
  echo "Erreur"

  fi
else
  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE| cut -d';' -f2,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/hvb_comp.csv
    sort -t';' -k2,2n test/hvb_comp.csv -o test/hvb_comp.csv


  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$3 != "-" && $5 != "-" && $7 == "-" || $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/hva_comp.csv
    sort -t';' -k2,2n test/hva_comp.csv -o test/hva_comp.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    awk -F';' '$4 != "-" && $5 != "-" && $7 == "-" ||$3 != "-" && $4 != "-" && $8 == "-"' $FILE| cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/lv_comp.csv
    sort -t';' -k2,2n test/lv_comp.csv -o test/lv_comp.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    awk -F';'  '$4 != "-" && $6 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/lv_indiv.csv
    sort -t';' -k2,2n test/lv_indiv.csv -o test/lv_indiv.csv

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  awk -F';' '$4 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
  mv test/monfichier.csv test/lv_all.csv
  sort -t';' -k2,2n test/lv_all.csv -o test/lv_all.csv
  LV=test/lv_all.csv

  else
  echo "Erreur"

  fi
fi
if [ -f "$LV" ]; then
  a=$(wc -l < $LV)
  if [[ "$a" -lt 20 ]]; then
  echo "Nombre de postes LV insuffisants pour pouvoir effectué le minmax"
  fi
  if [[ "$a" -gt 20 ]]; then
    tail -n +2 "$LV" | awk -F';' '{
    if ($2-$3 > 0) {
        print $1 ";"0";" ($2 - $3)
    } else {
        print $1";"($2 - $3)";"0
    }
}' "$LV" | sort -t';' -k2,2n -k3,3n > test/lv_all_minmax.csv
  (head -n 10 test/lv_all_minmax.csv && tail -n 10 test/lv_all_minmax.csv) > test/temp.csv
  mv test/temp.csv test/lv_all_minmax.csv
  gnuplot << EOF
  set terminal pngcairo size 1400,600 enhanced font 'Verdana,12'
  set output 'graphs/bar_chart.png'
  set title "Graphique en Barres"
  set xlabel "Stations LV"
  set ylabel "Énergie (kWh)"
  set datafile separator ';'
  set style data histograms
  set boxwidth  0.4
  set xtics rotate by -45
  set style fill solid 1.0 border -1
  plot "test/lv_all_minmax.csv" using 3:xtic(1) with boxes lc rgb "green" title "Station les + chargés", \
    "test/lv_all_minmax.csv" using 2:xtic(1) with boxes lc rgb "red" title "Station les - chargés"
EOF
 fi
fi
END_TIME=$(date +%s)
DURATION=$((END_TIME - START_TIME))
echo "Traitement terminé en $DURATION secondes."
