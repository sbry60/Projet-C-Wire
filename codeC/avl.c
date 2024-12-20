#include "tri.h"
/* Function to search for a node and store its address if found */
int searchAVL(Tree* a, long v, Tree** b){
  if(a == NULL){
      return 0;
  }
  else if(a->id == v){
      *b = a;
      return 1;
  }
  else if(v > a->id){
      return searchAVL(a->sR, v, b);
  }
  else{
      return searchAVL(a->sL, v, b);
  }
}

/* Function to insert a node into an AVL tree */
Tree* insertAVL(Tree* a, long i, long c, long l, int *h){
    /* h is used to update the heights */
    /* Insert the node and set h to 1 */
    if (a == NULL){
        *h = 1;
        return createTree(i, c, l);
    }
    else if (i < a->id){ 
        a->sL = insertAVL(a->sL, i, c, l, h);
        *h = -*h; /* Change the sign of h when inserting on the left */
    }
    else if (i > a->id){
        a->sR = insertAVL(a->sR, i, c, l, h);
    }
    /* If the identifier is already present, return the node and set h to 0 so the next condition does not apply */
    else{ 
        *h = 0;
        return a;
    }
    /* This condition means if there is an insertion, we add h to the height and balance the tree */
    if (*h != 0){
        a->height += *h;
        a = balanceAVL(a);
        *h = (a->height == 0) ? 0 : 1; 
    }

    return a;
}

/* Infix traversal to write AVL data to a file */
void infix(Tree* a, FILE *file){
  if(a != NULL){
      infix(a->sL, file);
      fprintf(file, "%ld;%ld;%ld\n", a->id, a->cap, a->load);
      infix(a->sR, file);
  }
}

/* Function to remove the maximum node from the tree */
Tree* removeMax(Tree* a, long* v){
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

/* Function to remove a node from the tree */
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
              a->sL = removeMax(a->sL, &(a->id));
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

/* Function to delete the entire tree */
void deleteTree(Tree* a) {
    if (a == NULL) {
        return;
    }
    deleteTree(a->sL);
    deleteTree(a->sR);
    free(a);
}
