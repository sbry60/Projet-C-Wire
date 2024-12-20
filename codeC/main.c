#include "tri.h"
int main() {
    /*Création du fichier */
    FILE *file = fopen("test/monfichier.csv", "w");

    /*Vérification de son existence*/
    if (file == NULL){
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }
    fprintf(file,"Identifiant;Capacité;Consommation\n");

    Tree* ab=NULL;   /*Initialisation de l'arbre pour le calcul */
    Tree* node=NULL;/*Initialisation du noeud qui stocke l'adresse pour la fonction searchAVL*/
    int ret1=0;/*Variable pour la verification du scanf*/ 
    long v1,v2,v3;/*Variable qui stocke respectivement l'identifiant de la station, capacité, consommation*/ 
    int h;/*Variable pour la fonction insertAVL*/

    do{
        /*Récupération du filtrage du code C*/
        ret1=scanf("%ld;%ld;%ld\n",&v1,&v2,&v3);
        /*si toute les variables sont là et que le noeud représentant de la station n'est pas là on insère un nouveau noeud*/
        if(ret1==3 && searchAVL(ab,v1,&node)==0){
            ab=insertAVL(ab,v1,v2,v3,&h); 
        }
        /*si toute les variables sont là et que le noeud représentant de la station est là et que la capacité est différent de 0, ce qui signifie que c'est une ligne qui nous donne la capacité de la station, noeud->cap caut cette valeur */
        else if(ret1==3 && searchAVL(ab,v1,&node)==1 && v2!=0){
            node->cap=v2;
        }
        /*si toute les variables sont là et que le noeud représentant de la station est là et que la consommation est différent de 0, ce qui signifie que c'est les lignes des consommateurs, on rajoute cette valeur à noeud->load */
        else if(ret1==3 && searchAVL(ab,v1,&node)==1 && v3!=0){
            node->load+=v3;
        }    

    }while(ret1==3);
    /*On ajoute les données recueillies dans le fichier créé */
    infix(ab,file);
    /*si toute les variables sont là et que le noeud représentant de la station est là et que la capacité est différent de 0, ce qui signifie que c'est une ligne qui nous donne la capacité de la station, noeud->cap caut cette valeur */
    fclose(file);
    deleteTree(ab);
    return 0;
}
