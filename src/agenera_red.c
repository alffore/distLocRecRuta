#include "distlocrutac.h"

extern PNodo pNodo;
extern PSegmento pSeg;


extern size_t tam_nodo;
extern size_t tam_seg;


void generaRed(void);

void *generador(void *param);

void asignaNodos(long id_nodo, double dist, PNodo pn);


/**
 * 
 */
void *generador(void *param) {
    unsigned int *ihilo = (unsigned int *) param;

    for (unsigned int i = *ihilo; i < tam_nodo; i += NUM_HILOS) {
        PNodo pn = pNodo + i;

        for (unsigned int j = 0; j < tam_seg; j++) {
            PSegmento pseg = pSeg + j;
            if (pseg->id_nodo0 == pn->id_nodo) {
                asignaNodos(pseg->id_nodo1, pseg->dist, pn);
            } else if (pseg->id_nodo1 == pn->id_nodo) {
                asignaNodos(pseg->id_nodo0, pseg->dist, pn);
            }
        }
    }

    return NULL;
}


/**
 *
 * @param nodo_id
 * @param dist
 * @param pn
 */
void asignaNodos(long id_nodo, double dist, PNodo pn) {

    for (size_t i = 0; i < tam_nodo; i++) {
        PNodo paux = pNodo + i;
        if (paux->id_nodo == id_nodo) {
            pn->aindex_nodos[pn->nsn] = i;
            pn->adist[pn->nsn] = dist;
            pn->nsn++;
        }
    }
}

/**
 *
 */
void generaRed(void) {
    pthread_t thread[NUM_HILOS];
    int iret;
    unsigned int ihiloT[NUM_HILOS];

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        ihiloT[ihilos] = ihilos;
    }

    printf("Marca localidades con nodo mas cercano ...\n");
    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        iret = pthread_create(&thread[ihilos], NULL, generador, (void *) &ihiloT[ihilos]);

        if (iret) {
            fprintf(stderr, "Error al crear thread %d\n", ihilos);
        }
    }

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        pthread_join(thread[ihilos], NULL);
    }
}