#include "distlocrutac.h"

extern PNodo pNodo;
extern PLocalidad pLoc;
extern PRecurso pRec;

extern size_t tam_nodo;
extern size_t tam_rec;
extern size_t tam_loc;


void imprimeSalida(char *sarchivosal);

/**
 *
 * @param sarchivosal
 */
void imprimeSalida(char *sarchivosal){

    FILE *fh;
    fh =fopen(sarchivosal,"w");
    for(size_t il=0;il<tam_loc;il++){
        PLocalidad pl = pLoc+il;

        PNodo  pn = pNodo+pl->index_nodo;

        fprintf(fh,"Loc: %li,%li,%lf\n",pl->id_loc,pn->id_rec,pn->dist_rec);

    }

    fclose(fh);
}