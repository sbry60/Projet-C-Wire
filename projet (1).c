#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
  int value;
  struct _tree *sR;
  struct _tree *sL;
  int height;
} Tree;

typedef struct _type {
  int id;
  int capacity;
  int load;
} Component;

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
int sumTree(Tree* a) {
    if (a == NULL) {
        return 0;
    }
    return a->value + sumTree(a->sL) + sumTree(a->sR);
}
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

Tree* insertAVL(Tree* a, int v, int *h)
{
    if (a == NULL){
        *h = 1;
        return createTree(v);
        
    }
    else if (v < a->value){ 
        a->sL = insertAVL(a->sL, v, h);
        *h = -*h; 
        
    }
    else if (v > a->value){
        a->sR = insertAVL(a->sR, v, h);
    }
    else{ 
        *h = 0;
        return a;
    }
    
    if (*h != 0){
        a->height += *h;
        a = balanceAVL(a);
        *h = (a->height == 0) ? 0 : 1; 
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


int main() {
    FILE *file = fopen("monfichier.txt", "w");

    if (file == NULL) {
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }
    fprintf(file,"Identifiant;Capicité;Consommation\n");

    
    
    Tree* ab=NULL;
    int ret=0;
    int v1,v2,v3;
    int a;
    int b;
    ret=scanf("%d;%d;%d\n",&v1,&v2,&v3);
    a=v1;
    if(ret==3){
        ab=createTree(v3);
    }
    do{
        ret=scanf("%d;%d;%d\n",&v1,&v2,&v3);
        if(ret==3 && a==v1 ){
            ab=insertAVL(ab,v3,&b); 
        }
        else{
            fprintf(file,"%d;-;%d\n",v1,sumTree(ab));
            ab=NULL;
            a=v1;
        }
    }while(ret==3);
    fprintf(file,"%d;-;%d\n",v1,sumTree(ab));
    fclose(file);
    return 0;
}
