
#include "distlocrutac.h"

extern PNodo pNodo;
extern PLocalidad pLoc;

extern size_t tam_loc;
extern size_t tam_nodo;

void *asociaLoc(void *param);
void asociaLoc2Nodo(void);

/**
 *
 * @param param
 */
void *asociaLoc(void *param) {
   unsigned int *ihilo = (unsigned int *) param;

    double distaux = MAX_DIST;
    double distmin = MAX_DIST;
    long jmin;

    for (unsigned int i = *ihilo; i < tam_loc; i += NUM_HILOS) {
        PLocalidad pl = pLoc + i;
        distmin = MAX_DIST;
        jmin = -1;
        for (unsigned int j = 0; j < tam_nodo; j++) {
            PNodo pn = pNodo + j;
                distaux = pl->x * pn->x + pl->y * pn->y + pl->z * pn->z;
                if (distaux > 1.00)distaux = 1.00;
                if (distaux < -1.00)distaux = -1.00;
                distaux = RT * acos(distaux);
                if (distmin > distaux) {
                    distmin = distaux;
                    jmin = j;
                }            
        }
        if(jmin>0){
            pl->index_nodo = jmin;
            pl->id_nodo = (pNodo + jmin)->id_nodo;
            pl->dist_nodo = distmin;  
        }      
    }

    return NULL;
}

/**
 *
 */
void asociaLoc2Nodo(void) {
    pthread_t thread[NUM_HILOS];
    int iret;
    unsigned int ihiloT[NUM_HILOS];

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        ihiloT[ihilos] = ihilos;
    }

    printf("Marca localidades con nodo mas cercano ...\n");
    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        iret = pthread_create(&thread[ihilos], NULL, asociaLoc, (void *) &ihiloT[ihilos]);

        if (iret) {
            fprintf(stderr, "Error al crear thread %d\n", ihilos);
        }
    }

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        pthread_join(thread[ihilos], NULL);
    }
}