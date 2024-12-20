#include "tri.h"

/* Function to create a tree */
Tree *createTree(long i, long c, long l){
  Tree *nv = malloc(sizeof(Tree));
  if (nv == NULL) {
    exit(2);
  }
  nv->id = i;
  nv->cap = c;
  nv->load = l;
  nv->sR = NULL;
  nv->sL = NULL;
  nv->height = 0;
  return nv;
}

/* Function to check if the node is empty */
int empty(Tree *a) { 
  return a == NULL; 
}

/* Function to get the height of a node */
int getHeight(Tree* a) {
    if (a == NULL)
        return 0;
    return a->height;
}

/* Function to check if the left child exists */
int existSL(Tree *a) {
  if (empty(a)) {
    exit(4);
  }
  return a->sL != NULL;
}

/* Function to check if the right child exists */
int existSR(Tree *a){
  if (empty(a)){
    exit(5);
  }
  return a->sR != NULL;
}

/* Function to add a left child */
int addSL(Tree *a, int i, int c, int l) {
  if (empty(a) || existSL(a)) {
    return 0;
  }
  a->sL = createTree(i, c, l);
  return 1;
}

/* Function to add a right child */
int addSR(Tree *a, long i, long c, long l) {
  if (empty(a) || existSR(a)) {
    return 0;
  }
  a->sR = createTree(i, c, l);
  return 1;
}

/* Function to get the minimum of two values */
int min2(int a, int b){
  return a < b ? a : b;
}

/* Function to get the maximum of two values */
int max2(int a, int b){
  return a > b ? a : b;
}

/* Function to get the minimum of three values */
int min3(int a, int b, int c){
  return min2(a, min2(b, c));
}

/* Function to get the maximum of three values */
int max3(int a, int b, int c){
  return max2(a, max2(b, c));
}

/* Function to perform a left rotation */
Tree* rotateLeft(Tree* root){
  if(root == NULL || root->sR == NULL){
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

/* Function to perform a right rotation */
Tree* rotateRight(Tree* root){
  if(root == NULL || root->sL == NULL){
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

/* Function to perform a double left rotation */
Tree* doubleRotateLeft(Tree* root){
  if(root == NULL || root->sR == NULL){
      exit(8);
  }
  root->sR = rotateRight(root->sR);
  return rotateLeft(root);
}

/* Function to perform a double right rotation */
Tree* doubleRotateRight(Tree* root){
  if(root == NULL || root->sL == NULL){
      exit(9);
  }
  root->sL = rotateLeft(root->sL);
  return rotateRight(root);
}

/* Function to balance an AVL tree */
Tree* balanceAVL(Tree* root){
  if(root == NULL){
      exit(10);
  }

  if(root->height >= 2){
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
