#include "tri.h"

/*Fonction création arbre*/
Tree *createTree(long i,long c,long l){
  Tree *nv = malloc(sizeof(Tree));
  if (nv == NULL) {
    exit(2);
  }
  nv->id = i;
  nv->cap = c;
  nv->load = l;
  nv->sR = NULL;
  nv->sL = NULL;
  nv->height= 0;
  return nv;
}
/*Fonction pour savoir si le noeud est vide*/
int empty(Tree *a) { 
  return a == NULL; 
}

/*Fonction pour avoir la hauteur d'un noeud*/
int getHeight(Tree* a) {
    if (a == NULL)
        return 0;
    return a->height;
}

/*Fonction pour savoir si le fils gauche existe*/
int existSL(Tree *a) {
  if (empty(a)) {
    exit(4);
  }
  return a->sL != NULL;
}

/*Fonction pour savoir si le fils droit existe*/
int existSR(Tree *a){
  if (empty(a)){
    exit(5);
  }
  return a->sR != NULL;
}

/*Fonction pour ajouter un fils gauche */
int addSL(Tree *a, int i,int c,int l) {
  if (empty(a) || existSL(a)) {
    return 0;
  }
  a->sL = createTree(i,c,l);
  return 1;
}

/*Fonction pour ajouter un fils droit */
int addSR(Tree *a, long i,long c,long l) {
  if (empty(a) || existSR(a)) {
    return 0;
  }
  a->sR = createTree(i,c,l);
  return 1;
}

/*Fonction pour obtenir le minimum entre deux valeurs */
int min2(int a, int b){
  return a < b ? a : b;
}
/*Fonction pour obtenir le maximum entre deux valeurs */
int max2(int a, int b){
  return a > b ? a : b;
}
/*Fonction pour obtenir le minimum entre troix valeurs */
int min3(int a, int b, int c){
  return min2(a, min2(b, c));
}
/*Fonction pour obtenir le maximum entre troix valeurs */
int max3(int a, int b, int c){
  return max2(a, max2(b, c));
}

/*Fonction pour faire une rotation gauche */
Tree* rotateLeft(Tree* root){
  if(root==NULL || root->sR == NULL){
         exit(7);
    }
  Tree* pivot  = root->sR;
  root->sR = pivot->sL;
  pivot->sL = root;
  int eqa = root->height;        
  int eqp = pivot->height;        
  root->height  = eqa - max2(eqp, 0) - 1;
  pivot->height = min3(eqa-2, eqa+eqp-2, eqp-1);
  root = pivot;
  return root;
}

/*Fonction pour faire une rotation droite */
Tree* rotateRight(Tree* root){
  if(root==NULL || root->sL == NULL){
      exit(7);
  }
  Tree* pivot  = root->sL;
  root->sL = pivot->sR;
  pivot->sR = root;
  int eqa = root->height;        
  int eqp = pivot->height;        
  root->height  = eqa - min2(eqp, 0) + 1;
  pivot->height = max3(eqa+2, eqa+eqp+2, eqp+1);
  root = pivot;
  return root;
}

/*Fonction pour faire une double rotation gauche */
Tree* doubleRotateLeft(Tree* root){
  if(root==NULL || root->sR == NULL){
      exit(8);
  }
  root->sR = rotateRight(root->sR);
  return rotateLeft(root);
}

/*Fonction pour faire une double rotation droite */
Tree* doubleRotateRight(Tree* root){
  if(root==NULL || root->sL == NULL){
      exit(9);
  }
  root->sL= rotateLeft(root->sL);
  return rotateRight(root);
}

/*Fonction pour réquilibrer un arbre */
Tree* balanceAVL(Tree* root){
  if(root == NULL){
      exit(10);
  }

  if(root->height>= 2){
      if(root->sR == NULL){
          exit(11);
      }
      if(root->sR->height >= 0){
          root = rotateLeft(root);
      }        
      else{
          root = doubleRotateLeft(root);
      }        
  }
  else if(root->height <= -2){
      if(root->sL == NULL){
          exit(12);
      }
      if(root->sL->height <= 0){
          root = rotateRight(root);
      }        
      else{
          root = doubleRotateRight(root);                        
      }
  }
  return root;
}



