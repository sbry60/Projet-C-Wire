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

/*Fonction création arbre*/
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

int main() {
    /*Création du fichier */
    FILE *file = fopen("monfichier.csv", "w");

    /*Vérification de son exitence*/
    if (file == NULL){
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }
    fprintf(file,"Identifiant;Capicité;Consommation\n");

    Tree* ab=NULL;   /*Initialisation de l'arbre pour le calcul */
    Tree* node=NULL;/*Initialisation du noeud qui stocke l'adresse pour la fonction searchAVL*/
    int ret1=0;/*Variable pour la verification du scanf*/ 
    long v1,v2,v3,v4;/*Variable qui stocke respectivement l'identifiant de la station, l'identifiant du consommateur, capacité, consommation*/ 
    int h;/*Variable pour la fonction insertAVL*/
    long b;
  
    do{
        /*Récupération du filtrage du code C*/
        ret1=scanf("%ld;%ld;%ld;%ld\n",&v1,&v2,&v3,&v4);
        /*si toute les variables sont là et que le noeud représentant de la station n'est pas là on insère un nouveau noeud*/
        if(ret1==4 && searchAVL(ab,v1,&node)==0){
            ab=insertAVL(ab,v1,v3,v4,&h); 
        }
        /*si toute les variables sont là et que le noeud représentant de la station est là et que la capacité est différent de 0, ce qui signifie que c'est une ligne qui nous donne la capacité de la station, noeud->cap caut cette valeur */
        else if(ret1==4 && searchAVL(ab,v1,&node)==1 && v3!=0){
            node->cap=v3;
        }
        /*si toute les variables sont là et que le noeud représentant de la station est là et que la consommation est différent de 0, ce qui signifie que c'est les lignes des consommateurs, on rajoute cette valeur à noeud->load */
        else if(ret1==4 && searchAVL(ab,v1,&node)==1 && v4!=0){
            node->load+=v4;
        }    
    
    }while(ret1==4);
    /*On ajoute les données recueillies dans le fichier créé */
    infix(ab,file);
    /*si toute les variables sont là et que le noeud représentant de la station est là et que la capacité est différent de 0, ce qui signifie que c'est une ligne qui nous donne la capacité de la station, noeud->cap caut cette valeur */
    fclose(file);
    deleteTree(ab);
    return 0;
}
