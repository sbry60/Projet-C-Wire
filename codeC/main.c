#include "tri.h"
int main() {
    /* File creation */
    FILE *file = fopen("test/monfichier.csv", "w");

    /* Check if the file was successfully created */
    if (file == NULL){
        printf("Error while creating the file.\n");
        return 1;
    }
    fprintf(file,"Identifier;Capacity;Load\n");

    Tree* tr = NULL;   /* Initialization of the tree for calculations */
    Tree* node = NULL; /* Initialization of the node to store the address for the searchAVL function */
    int ret1 = 0; /* Variable for scanf verification */ 
    long id1, cap1, loa1; /* Variables to store station ID, capacity, and consumption respectively */ 
    int h; /* Variable for the insertAVL function */

    do {
        /* Reading and filtering input from C code */
        ret1 = scanf("%ld;%ld;%ld\n", &id1, &cap1, &loa1);

        /* If all variables are present and the node representing the station does not exist, insert a new node */
        if (ret1 == 3 && searchAVL(tr, id1, &node) == 0){
            tr = insertAVL(tr, id1, cap1, loa1, &h); 
        }
        /* If all variables are present, the node representing the station exists, 
           and the capacity is not 0, it means this line gives the station's capacity.
           Update `node->cap` with this value */
        else if (ret1 == 3 && searchAVL(tr, id1, &node) == 1 && cap1 != 0){
            node->cap = cap1;
        }
        /* If all variables are present, the node representing the station exists, 
           and the consumption is not 0, it means this line provides consumption data.
           Add this value to `node->load` */
        else if (ret1 == 3 && searchAVL(tr, id1, &node) == 1 && loa1 != 0){
            node->load += loa1;
        }    

    } while (ret1 == 3);

    /* Add the collected data to the created file */
    infix(tr, file);

    /* Close the file and delete the tree */
    fclose(file);
    deleteTree(tr);
    return 0;
}
