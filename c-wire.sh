#!/bin/bash

# Function to display help and usage information
function help_me {
    echo "Usage: <path_to_csv_file> <station_type> <consumer_type> [central_id] [-h]"
    echo "Options:"
    echo "  <path_to_csv_file>   : Mandatory path to the CSV file."
    echo "  <station_type>       : Type of station to analyze (hvb, hva, lv)."
    echo "  <consumer_type>      : Type of consumer (comp, indiv, all)."
    echo "  [central_id]         : (Optional) Filter for a specific central."
    echo "  -h                   : Displays this help."
    exit 0
}
# Ensure the minimum number of arguments is provided
if [ "$#" -lt 3 ]; then
    echo "Error: Insufficient number of arguments."
    help_me
fi
# Display help if the -h option is used
if [[ "$*" == *"-h"* ]]; then
    help_me
fi
# Retrieve arguments
FILE=$1
TYPE_STATION=$2
TYPE_CONS=$3
ID_CENTRALE=${4:-"ALL"} 

# Check if the file exists
if [ ! -f "$FILE" ]; then
    echo "Error: File $FILE does not exist."
    help_me
    exit 1
fi

# Validate station type and consumer type
if [[ "$TYPE_STATION" != "hvb" && "$TYPE_STATION" != "hva" && "$TYPE_STATION" != "lv" ]]; then
    echo "Error: Invalid station type ($TYPE_STATION)."
    help_me
fi

if [[ "$TYPE_CONS" != "comp" && "$TYPE_CONS" != "indiv" && "$TYPE_CONS" != "all" ]]; then
    echo "Error: Invalid consumer type ($TYPE_CONS)."
    help_me
fi

# Clean the C code
make clean -C codeC
# Compile the C code
make -C codeC


if [ ! -f ./codeC/exec ]; then
    echo "The executable does not exist."
    exit 1
fi
if [ ! -r ./codeC/exec ]; then
    echo "The executable cannot be read."
    exit 1
fi

if [ ! -x ./codeC/exec ]; then
    echo "The executable cannot be executed."
    exit 1
fi
# Initiating the start time for the timer
START_TIME=$(date +%s)

# Cleanup and create temporary directories
if [ -d "tmp" ]; then
    chmod 777 tmp
    rm -rf tmp
fi
if [ -d "graphs" ]; then
    chmod 777 graphs
    rm -rf graphs
fi
if [ ! -d "test" ]; then
    mkdir test
fi
mkdir tmp graphs


# Data processing based on the provided arguments
# Block specific to a given central
if [[ "$ID_CENTRALE" != "ALL" ]]; then
  # For hvb comp
    if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
   # I filter to get the lines where there is the central identifier, the HVB identifier, and a load, or the central identifier, the HVB identifier, and a capacity
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $2 != "-" && $4 == "-" && $7 == "-" ||$1==id && $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE | cut -d';' -f2,7,8 | tr '-' '0'| ./codeC/exec
    #I Rename 
    mv test/monfichier.csv test/hvb_comp_$ID_CENTRALE.csv
    # I sort by capacity
    sort -t';' -k2,2n test/hvb_comp_$ID_CENTRALE.csv -o test/hvb_comp_$ID_CENTRALE.csv
  
  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
    # I filter to get the lines where there is the central identifier, the HVA identifier, and a load, or the central identifier, the HVA identifier, and a capacity
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $3 != "-" && $5 != "-" && $7 == "-" ||$1==id && $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/hva_comp_$ID_CENTRALE.csv
    sort -t';' -k2,2n test/hva_comp_$ID_CENTRALE.csv -o test/hva_comp_$ID_CENTRALE.csv

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then
   # I filter to get the lines where there is the  central identifier, the LV identifier,the LV company identifier  and a load, or the central identifier, the LV identifier, and a capacity
    awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $5 != "-" && $7 == "-" ||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/lv_comp_$ID_CENTRALE.csv
    sort -t';' -k2,2n test/lv_indiv_$ID_CENTRALE.csv -o test/lv_indiv_$ID_CENTRALE.csv
 
  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then 
    #I filter to get the lines where there is the central identifier, the LV identifier,the LV individual identifier  and a load, or the central identifier, the LV identifier, and a capacity
      awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $6 != "-" && $7 == "-"|| $1 == id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| make -C ./codeC/exec
      mv test/monfichier.csv test/lv_indiv_$ID_CENTRALE.csv
      sort -t';' -k2,2n test/lv_indiv_$ID_CENTRALE.csv -o test/lv_indiv_$ID_CENTRALE.csv
 
  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then
      # I filter to get the lines where there is the central identifier, the LV identifier and a load, or the central dentifier, the LV identifier, and a capacity
      awk -F';' -v id="$ID_CENTRALE" '$1==id && $4 != "-" && $7 == "-"||$1==id && $3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
      mv test/monfichier.csv test/lv_all_$ID_CENTRALE.csv
      # For LV all, I sort by load, it's more simple for the treatment of lv minmax
      sort -t';' -k3,3n test/lv_all_$ID_CENTRALE.csv -o test/lv_all_$ID_CENTRALE.csv
      # LV is to verirfie the existence of the file later in the script
  LV=test/lv_all_$ID_CENTRALE.csv

  else
      echo "Error"
  fi
else

  if [[ "$TYPE_STATION" == "hvb" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
  # I filter to get the lines where there is  the HVB identifier, and a load, or the HVB identifier, and a capacity
      awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' $FILE| cut -d';' -f2,7,8 | tr '-' '0'| ./codeC/exec
      mv test/monfichier.csv test/hvb_comp.csv
      sort -t';' -k2,2n test/hvb_comp.csv -o test/hvb_comp.csv
      

  elif [[ "$TYPE_STATION" == "hva" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
  # I filter to get the lines where there is  the HVA identifier, and a load, or the HVA identifier, and a capacity
      awk -F';' '$3 != "-" && $5 != "-" && $7 == "-" || $2 != "-" && $3 != "-" && $4 == "-" ' $FILE | cut -d';' -f3,7,8 | tr '-' '0'| ./codeC/exec
      mv test/monfichier.csv test/hva_comp.csv
      sort -t';' -k2,2n test/hva_comp.csv -o test/hva_comp.csv

  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "comp" ]]; then 
   # I filter to get the lines where there is the LV identifier,the LV company identifier  and a load, or the LV identifier, and a capacity
    awk -F';' '$4 != "-" && $5 != "-" && $7 == "-" ||$3 != "-" && $4 != "-" && $8 == "-"' $FILE| cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
    mv test/monfichier.csv test/lv_comp.csv
    sort -t';' -k2,2n test/lv_comp.csv -o test/lv_comp.csv
    


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "indiv" ]]; then
  # I filter to get the lines where there is the LV identifier,the LV individual identifier  and a load, or the LV identifier, and a capacity
      awk -F';' '$4 != "-" && $6 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
      mv test/monfichier.csv test/lv_indiv.csv
      sort -t';' -k2,2n test/lv_indiv.csv -o test/lv_indiv.csv
      LV=test/lv_all.csv


  elif [[ "$TYPE_STATION" == "lv" ]] && [[ "$TYPE_CONS" == "all" ]]; then 
  # I filter to get the lines where there is the LV identifier,the LV identifier  and a load, or the LV identifier, and a capacity
      awk -F';' '$4 != "-" && $7 == "-"||$3 != "-" && $4 != "-" && $8 == "-"' $FILE | cut -d';' -f4,7,8 | tr '-' '0'| ./codeC/exec
      mv test/monfichier.csv test/lv_all.csv
      # For LV all, I sort by load, it's more simple for the treatment of lv minmax
      sort -t';' -k3,3n test/lv_all.csv -o test/lv_all.csv
      # LV is to verirfie the existence of the file later in the script
      LV=test/lv_all.csv

  else
      echo "Error"
  fi
fi
# LV station analysis for minmax
if [ -f "$LV" ]; then
    a=$(wc -l < $LV)
# the code must have 20 LV stations to do the minmax
    if [[ "$a" -lt 20 ]]; then
        echo "Insufficient number of LV stations to perform the minmax analysis."
    fi
    if [[ "$a" -ge 20 ]]; then
        #I take the first 10 and the last 10 for the min-max.
        (tail -n +2 $LV | head -n 10 && tail -n 10 $LV) > test/lv_all_minmax.csv
        #I put the stations that are under-consumed in column 3 and those that are over-consumed in column 2 in temp.csv
        awk -F';' '{
        if ($2-$3 > 0) {
        print $1 ";"0";" ($2 - $3)
        } else {
        print $1";"($3 - $2)";"0
         }
        }' "test/lv_all_minmax.csv" > tmp/temp.csv
        #I sort
        sort -t';' -k2,2 -k3,3n tmp/temp.csv -o tmp/temp.csv
        # I call gnuplot for graphics
        gnuplot << EOF
        set terminal pngcairo size 1400,600 enhanced font 'Verdana,12'
        set output 'graphs/bar_chart.png'
        set title "Bar Chart"
        set xlabel "LV Stations"
        set ylabel "Energy (kWh)"
        set datafile separator ';'
        set style data histograms
        set boxwidth  0.4
        set xtics rotate by -45
        set style fill solid 1.0 border -1
        plot "tmp/temp.csv" using 3:xtic(1) with boxes lc rgb "green" title "Most Loaded Stations", \
            "tmp/temp.csv" using 2:xtic(1) with boxes lc rgb "red" title "Least Loaded Stations"
EOF
    fi
fi

END_TIME=$(date +%s)
DURATION=$((END_TIME - START_TIME))
echo "Processing completed in $DURATION seconds."
