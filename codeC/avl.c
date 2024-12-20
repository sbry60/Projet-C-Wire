#include "tri.h"
/*Fonction recherche d'un noeud et qui stocke l'adresse du noeud s'il le trouve */
int searchAVL(Tree* a, long v,Tree** b){
  if(a == NULL){
      return 0;
  }
  else if(a->id == v){
      *b=a;
      return 1;
  }
  else if(v > a->id){
      return searchAVL(a->sR,v,b);
  }
  else{
      return searchAVL(a->sL,v,b);
  }
}

/*Fonction insertion dans un arbre de type AVL */

Tree* insertAVL(Tree* a,long i,long c,long l,int *h){
    /*h est utilise pour la mise à jour des hauteurs */
    /*Insertion du noeud et la valeur de h est de 1*/
    if (a == NULL){
        *h = 1;
        return createTree(i,c,l);

    }
    else if (i < a->id){ 
        a->sL = insertAVL(a->sL,i,c,l,h);
        *h = -*h; /*on change le signe de h quand on insere a gauche */

    }
    else if (i > a->id){
        a->sR = insertAVL(a->sR,i,c,l,h);
    }
    /*si l'dentifiant est déja présent, on retourne le noeud et on met h à 0 pour que la prochaine condition n'aie pas lieu */
    else{ 
        *h = 0;
        return a;
    }
    /* cette condition signifie s'il y a une insertion, on rajoute h à la hauteur et on equilibre */
    if (*h != 0){
        a->height += *h;
        a = balanceAVL(a);
        *h = (a->height == 0) ? 0 : 1; 
    }

    return a;
}

/*aprcours infix qui permet d'écrire les données de l'AVL dans un fichier */
void infix(Tree* a,FILE *file){
  if(a!=NULL){
      infix(a->sL,file);
      fprintf(file,"%ld;%ld;%ld\n",a->id,a->cap,a->load);
      infix(a->sR,file);
  }
}

/*Fonction suppression du maximum de l'arbre */
Tree* removeMax(Tree* a, long* v ){
  if(a == NULL || a == NULL){
      exit(14);
  }
  if(a->sR != NULL){
      a->sR = removeMax(a->sR, v);
  }
  else{
      Tree* pop = a;
      *v = a->id;
      a = a->sL;
      free(pop);
  }
  return a;
}
/*Fonction suppression d'un noeud de l'arbre */
Tree* removeAVL(Tree* a, long v){
  if(a != NULL){
      if(v < a->id){
          a->sL = removeAVL(a->sL, v);
      }
      else if(v > a->id){
          a->sR = removeAVL(a->sR, v);
      }
      else{
          if(a->sL != NULL && a->sR != NULL){
              a->sL = removeMax(a->sL, &(a->id) );
          }
          else{
              Tree* child = a->sL;
              if(child == NULL){
                  child = a->sR;
              }
              free(a);
              a = child;
          }
      }    
  }
  return a;
}
void deleteTree(Tree* a) {
    if (a == NULL) {
        return;
    }
    deleteTree(a->sL);
    deleteTree(a->sR);
    free(a);
}