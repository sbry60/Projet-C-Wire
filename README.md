# Projet C-WIRE


## Table des Matières
1. [Description](#description)
2. [Installation](#installation)
3. [Utilisation](#utilisation)
4. [Auteurs](#auteurs)

## Description

Le projet consiste à développer un programme permettant de synthétiser les données relatives au système de distribution d’électricité en France. L'objectif est d'analyser et de structurer les informations contenues dans un fichier .csv pour fournir des résultats exploitables, tels que la capacité, la consommation.

## Installation

### Prérequis


- Système d'exploitation compatible avec la compilation C et shell(Linux, macOS, Windows avec Cygwin ou MinGW).
- Assurez-vous que Gnuplot est installé sur votre système.
- gcc doit être installé sur votre machine.
- Pensez à installer la commande chmod+x pour compiler le fichier c-wire.sh

### Étapes d'installation

1. Clonez le dépôt :
    ```bash
    https://github.com/sbry60/Projet-C-Wire
   
    ```
    
2. Compilez le projet :
    ```bash
    make
    ```
    
## Utilisation

Pour exécuter l'application :
    ```
    ./nom_du_fichier.sh input/fichier option id_central help
    ```

## Options:
hva comp,
hvb comp,
lv all,
lv comp,
lv indiv,
lv all.

Si vous souhaitez voir les résultats pour le fichier c-wire_v00.dat voici le lien :
https://drive.google.com/drive/folders/1kL1EGP7LOTQJIdzCApEjS0AYCue9n3js?usp=drive_link
    
## Auteurs

- **Iyed SOUISSI** - (https://github.com/IS277)
- **Yasser SABAR** - (https://github.com/sbry60)
- **Zakaria DIHAJ** - (https://github.com/zikodihaj)
