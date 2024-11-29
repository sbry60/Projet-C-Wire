#!/bin/bash


chercher_motif_5_cwire() {
    local fichier="cwire.dat" 
    local motif="-"          

    
    if [[ ! -f "$fichier" ]]; then
        echo "Erreur : Le fichier $fichier n'existe pas."
        return 2
    fi

    while IFS= read -r ligne; do
        if [[ ${#ligne} -ge 5 ]]; then
            if [["${ligne:0:1}" == "1" && "${ligne:2:1}" != "$motif" ]]; then
                echo "$ligne"
            fi
        fi
    done < "$fichier"
}


chercher_motif_5_cwire
