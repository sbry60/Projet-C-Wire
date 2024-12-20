#include <stdio.h>
#include <stdlib.h>

/*Structure Arbre composée par ordre
de l'identifiant,capacité,consommation fils droit fils gauche et la hauteur*/
typedef struct _tree {
  long id;
  long cap;
  long load;
  struct _tree *sR;
  struct _tree *sL;
  int height;
} Tree;



Tree *createTree(long i,long c,long l);
int empty(Tree *a);
int getHeight(Tree* a);
int existSL(Tree *a);
int existSR(Tree *a);
int addSL(Tree *a, int i,int c,int l);
int addSR(Tree *a, long i,long c,long l);
int min2(int a, int b);
int max2(int a, int b);
int min3(int a, int b, int c);
int max3(int a, int b, int c);
Tree* rotateLeft(Tree* root);
Tree* rotateRight(Tree* root);
Tree* doubleRotateLeft(Tree* root);
Tree* balanceAVL(Tree* root);
int searchAVL(Tree* a, long v,Tree** b);
Tree* insertAVL(Tree* a,long i,long c,long l,int *h);
void infix(Tree* a,FILE *file);
Tree* removeMax(Tree* a, long* v );
Tree* removeAVL(Tree* a, long v);
void deleteTree(Tree* a);
int main(void);