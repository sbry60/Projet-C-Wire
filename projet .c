#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
  long id;
  long cap;
  long load;
  struct _tree *sR;
  struct _tree *sL;
  int height;
} Tree;


Tree *createTree(long i,long c,long l) {
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
int empty(Tree *a) { 
  return a == NULL; 
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
int addSL(Tree *a, int i,int c,int l) {
  if (empty(a) || existSL(a)) {
    return 0;
  }
  a->sL = createTree(i,c,l);
  return 1;
}
int getHeight(Tree* a) {
    if (a == NULL)
        return 0;
    return a->height;
}

int addSR(Tree *a, long i,long c,long l) {
  if (empty(a) || existSR(a)) {
    return 0;
  }
  a->sR = createTree(i,c,l);
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

Tree* insertAVL(Tree* a,  long i,long c,long l, int *h)
{
    if (a == NULL){
        *h = 1;
        return createTree(i,c,l);

    }
    else if (i < a->id){ 
        a->sL = insertAVL(a->sL,i,c,l,h);
        *h = -*h; 

    }
    else if (i > a->id){
        a->sR = insertAVL(a->sR, i,c,l, h);
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


void infix(Tree* a,FILE *file){
  if(a!=NULL){
      infix(a->sL,file);
      fprintf(file,"%ld;%ld;%ld\n",a->id,a->cap,a->load);
      infix(a->sR,file);
  }
}

void prefix(Tree* a){
  if(a!=NULL){
      printf("[%02ld(%2d)]", a->id, a->height);
      prefix(a->sL);
      prefix(a->sR);
  }
}

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


int main() {
    FILE *file = fopen("monfichier.csv", "w");

    if (file == NULL){
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }
    fprintf(file,"Identifiant;Capicité;Consommation\n");

    Tree* ab=NULL;
    Tree* noeud=NULL;
    int ret1=0;
    long v1,v2,v3,v4;
    long b;
    int h;
    do{
        ret1=scanf("%ld;%ld;%ld;%ld\n",&v1,&v2,&v3,&v4);
        if(ret1==4 && searchAVL(ab,v1,&noeud)==0){
            ab=insertAVL(ab,v1,v3,v4,&h); 
        }
        else if(ret1==4 && searchAVL(ab,v1,&noeud)==1 && v3!=0){
            noeud->cap=v3;
        }
        else if(ret1==4 && searchAVL(ab,v1,&noeud)==1 && v4!=0){
            noeud->load+=v4;
        }    
    
    }while(ret1==4);
    infix(ab,file);
    fclose(file);
    return 0;
}
