#include "distlocrutac.h"

extern PNodo pNodo;
extern PLocalidad pLoc;
extern PRecurso pRec;

extern size_t tam_nodo;
extern size_t tam_rec;
extern size_t tam_loc;


void imprimeSalida(char *sarchivosal);
void imprimeSalidaNodo(char *sarchivo);

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


void imprimeSalidaNodo(char *sarchivo){
    FILE *fh;
    fh= fopen(sarchivo,"w");

    for(size_t i=0;i<tam_nodo;i++){
        PNodo p =pNodo+i;

        fprintf(fh,"%li,%lf,%lf,%li,%lf\n",p->id_nodo,p->lon,p->lat,p->id_rec,p->dist_rec);
    }


    fclose(fh);
}