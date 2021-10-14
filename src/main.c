
#include "distlocrutac.h"


PLocalidad pLoc;
PRecurso pRec;
PNodo pNodo;
PSegmento pSeg;


const size_t tam_loc = 292447;
const size_t tam_nodo = 1560802;
const size_t tam_rec = 1403;
const size_t tam_seg = 1756216;


extern void asociaLoc2Nodo(void);

extern void asociaRec2Nodo(void);

extern void generaRed(void);

extern void generaRecorridos(void);

extern int cargaArchivoLoc(char *snomarchivo, PLocalidad ploc);

extern int cargaArchivoNodo(char *snomarchivo, PNodo pnodo);

extern int cargaArchivoRec(char *snomarchivo, PRecurso prec);

extern int cargaArchivoSeg(char *snomarchivo, PSegmento pseg);

extern void imprimeSalida(char *sarchivosal);
extern void imprimeSalidaNodo(char *sarchivo);


/**
 *
 */
void alojaHostMemoria() {
    pLoc = (PLocalidad) malloc(sizeof(struct Localidad) * tam_loc);
    pNodo = (PNodo) malloc(sizeof(struct Nodo) * tam_nodo);
    pRec = (PRecurso) malloc(sizeof(struct Recurso) * tam_rec);
    pSeg = (PSegmento) malloc(sizeof(struct Segmento) * tam_seg);
}


/**
 *
 */
void liberaHostMemoria() {
    free(pLoc);
    free(pNodo);
    free(pRec);
    free(pSeg);
}

/**
 *
 */
void cargaRecursos() {

    char *sarchivo_loc = "/home/alfonso/distrecorrido/datos/localidad.csv";
    cargaArchivoLoc(sarchivo_loc, pLoc);
    /*for(size_t i = 0 ;i<tam_loc;i++){
        printf("%li %li (%lf,%lf,%lf)\n",i,(pLoc+i)->id_loc,(pLoc+i)->x,(pLoc+i)->y,(pLoc+i)->z);
    }*/

    char *sarchivo_nodo = "/home/alfonso/distrecorrido/datos/union_min.csv";
    cargaArchivoNodo(sarchivo_nodo, pNodo);

    char *sarchivo_rec = "/home/alfonso/distrecorrido/datos/museo.csv";
    cargaArchivoRec(sarchivo_rec, pRec);

    char *sarchivo_seg = "/home/alfonso/distrecorrido/datos/rutas.csv";
    cargaArchivoSeg(sarchivo_seg, pSeg);

}

/**
 *
 */
void calculos() {
    asociaLoc2Nodo();
    for(size_t i = 0 ;i<tam_loc;i++){
        printf("%li %li %li\n",i,(pLoc+i)->id_loc,(pLoc+i)->id_nodo);
    }


    asociaRec2Nodo();
    for(size_t i=0;i<tam_rec;i++){
        printf("%li %li %li\n",i,(pRec+i)->id_rec,(pRec+i)->index_nodo);
    }


    generaRed();
    for (size_t i = 0; i < tam_nodo; i++) {
        printf("%li %li %i\n", i, (pNodo + i)->id_nodo, (pNodo + i)->nsn);
    }

    generaRecorridos();
    for(size_t i=0; i<tam_nodo;i++){
        printf("%li %li %lf\n",(pNodo+i)->id_nodo,(pNodo+i)->id_rec,(pNodo+i)->dist_rec);
    }

}

/**
 *
 * @return
 */
int main(void) {

    alojaHostMemoria();

    cargaRecursos();

    calculos();

    imprimeSalida("salida_loc.csv");

    imprimeSalidaNodo("salida_nodos.csv");

    liberaHostMemoria();


    return 0;
}