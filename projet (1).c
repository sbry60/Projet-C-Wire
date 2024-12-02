#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
  int value;
  struct _tree *sR;
  struct _tree *sL;
  int height;
} Tree;

typedef struct _type {
  int id_centrale;
  int id_hvb;
  int id_hva;
  int id_lv;
  int id_comp;
  int id_indiv;
  int id_capacity;
  int id_load;
} Type;

Tree *createTree(int v) {
  Tree *nv = malloc(sizeof(Tree));
  if (nv == NULL) {
    exit(2);
  }
  nv->value = v;
  nv->sR = NULL;
  nv->sL = NULL;
  nv->height= 0;
  return nv;
}
int empty(Tree *a) { 
  return a == NULL; 
}
int element(Tree *a) {
  if (empty(a)) {
    exit(3);
  }
  return a->value;
}

int existSL(Tree *a) {
  if (empty(a)) {
    exit(4);
  }
  return a->sL != NULL;
}
int existSR(Tree *a){
  if (empty(a)){
    exit(5);
  }
  return a->sR != NULL;
}
int addSL(Tree *a, int e) {
  if (empty(a) || existSL(a)) {
    return 0;
  }
  a->sL = createTree(e);
  return 1;
}
int getHeight(Tree* a) {
    if (a == NULL)
        return 0;
    return a->height;
}

int addSR(Tree *a, int e) {
  if (empty(a) || existSR(a)) {
    return 0;
  }
  a->sR = createTree(e);
  return 1;
}
int min2(int a, int b){
  return a < b ? a : b;
}
int max2(int a, int b){
  return a > b ? a : b;
}
int min3(int a, int b, int c){
  return min2(a, min2(b, c));
}
int max3(int a, int b, int c){
  return max2(a, max2(b, c));
}



int hauteur(Tree* pTree) {
    if (pTree == NULL) {
        return -1; // Convention : un nœud vide a une hauteur de -1
    }
    return 1 + max2(hauteur(pTree->sL), hauteur(pTree->sR));



Tree* rotateLeft(Tree* root){
  if(root==NULL || root->sR == NULL){
      exit(6);
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
Tree* rotateRight(Tree* root){
  if(root==NULL || root->sL == NULL){
      exit(7);
  }
  Tree* pivot  = root->sL;
  root->sL = pivot->sL;
  pivot->sR = root;
  int eqa = root->height;        
  int eqp = pivot->height;        
  root->height  = eqa - min2(eqp, 0) + 1;
  pivot->height = max3(eqa+2, eqa+eqp+2, eqp+1);
  root = pivot;
  return root;
}

Tree* doubleRotateLeft(Tree* root){
  if(root==NULL || root->sR == NULL){
      exit(8);
  }
  root->sR = rotateRight(root->sR);
  return rotateLeft(root);
}
Tree* doubleRotateRight(Tree* root){
  if(root==NULL || root->sL == NULL){
      exit(9);
  }
  root->sL= rotateLeft(root->sL);
  return rotateRight(root);
}
Tree* HeightAVL(Tree* root){
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
          root = rotateLeft(root);
      }        
      else{
          root = doubleRotateRight(root);                        
      }
  }
  return root;
}

int searchAVL(Tree* a, int v){
  if(a == NULL){
      return 0;
  }
  else if(a->value == v){
      return 1;
  }
  else if(v > a->value){
      return searchAVL(a->sR, v);
  }
  else{
      return searchAVL(a->sL, v);
  }
}

Tree* insertAVL(Tree* a, int v){
  if(a == NULL){
      // insert
      a = createTree(v);
      if(a == NULL){
          exit(13);
      }
  }    
  else if(v < a->value){
      a->sL = insertAVL(a->sL, v);
  }
  else if(v > a->value){
      a->sR = insertAVL(a->sR, v);
  }
  else{
      
  }
  return a;
}

void infix(Tree* a){
  if(a!=NULL){
      infix(a->sL);
      printf("[%02d(%2d)]", a->value, a->height);
      infix(a->sR);
  }
}

void prefix(Tree* a){
  if(a!=NULL){
      printf("[%02d(%2d)]", a->value, a->height);
      prefix(a->sL);
      prefix(a->sR);
  }
}

Tree* removeMax(Tree* a, int* v ){
  if(a == NULL || a == NULL){
      exit(14);
  }
  if(a->sR != NULL){
      a->sR = removeMax(a->sR, v);
  }
  else{
      Tree* pop = a;
      *v = a->value;
      a = a->sL;
      free(pop);
  }
  return a;
}

Tree* removeAVL(Tree* a, int v){
  if(a != NULL){
      if(v < a->value){
          a->sL = removeAVL(a->sL, v);
      }
      else if(v > a->value){
          a->sR = removeAVL(a->sR, v);
      }
      else{
          if(a->sL != NULL && a->sR != NULL){
              a->sL = removeMax(a->sL, &(a->value) );
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

/*// Équilibrer un arbre AVL
Arbre* equilibrerAVL(Arbre* pRacine) {
    if (pRacine->equilibre >= 2) {
        if (pRacine->pDroit->equilibre >= 0) {
            return rotationGauche(pRacine); // Rotation gauche simple
        } else {
            pRacine->pDroit = rotationDroite(pRacine->pDroit);
            return rotationGauche(pRacine); // Double rotation gauche
        }
    } else if (pRacine->equilibre <= -2) {
        if (pRacine->pGauche->equilibre <= 0) {
            return rotationDroite(pRacine); // Rotation droite simple
        } else {
            pRacine->pGauche = rotationGauche(pRacine->pGauche);
            return rotationDroite(pRacine); // Double rotation droite
        }
    }
    return pRacine;
}*/
void whatistype(Type* type){
  if(type->id_comp!= 0){
    printf("Company");
  }
  if(type->id_indiv!= 0 ){
    printf("Individual");
  }
  if(type->id_hva!= 0 && type->id_indiv== 0 && type->id_comp== 0 ){
    printf("Station HV-A");
  }
  if(type->id_hvb!= 0 && type->id_indiv== 0 && type->id_comp== 0 ){
    printf("Station HV-B");
  }
}
int main() {
  // Write C code here
  printf("Try programiz.pro");

  return 0;
}
