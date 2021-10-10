
#include "distlocrutac.h"

extern PNodo pNodo;
extern PRecurso pRec;

extern size_t tam_rec;
extern size_t tam_nodo;

void *asociaRec(void *param);
void asociaRec2Nodo(void);

/**
 *
 * @param param
 */
void *asociaRec(void *param) {
    unsigned int *ihilo = (unsigned int *) param;

    double distaux = MAX_DIST;
    double distmin = MAX_DIST;
    long jmin;

    for (size_t i = *ihilo; i < tam_rec; i += NUM_HILOS) {
        PRecurso prec = pRec + i;
        distmin = MAX_DIST;
        jmin = -1;

        for (size_t j = 0; j < tam_nodo; j++) {
            PNodo pn = pNodo + j;
            distaux = prec->x * pn->x + prec->y * pn->y + prec->z * pn->z;
            if (distaux > 1.00)distaux = 1.00;
            if (distaux < -1.00)distaux = -1.00;
            distaux = RT * acos(distaux);
            if (distmin > distaux) {
                distmin = distaux;
                jmin = j;
            }
        }

        prec->index_nodo = jmin;
        prec->id_nodo = (pNodo + jmin)->id_nodo;
        prec->dist_nodo = distmin;

        (pNodo + jmin)->dist_rec = distmin;
        (pNodo + jmin)->id_rec = prec->id_rec;
    }

    return NULL;
}


/**
 *
 */
void asociaRec2Nodo(void) {
    pthread_t thread[NUM_HILOS];
    int iret;
    unsigned int ihiloT[NUM_HILOS];

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        ihiloT[ihilos] = ihilos;
    }

    printf("Marca recursos con nodo mas cercano ...\n");
    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        iret = pthread_create(&thread[ihilos], NULL, asociaRec, (void *) &ihiloT[ihilos]);

        if (iret) {
            fprintf(stderr, "Error al crear thread %d\n", ihilos);
        }
    }

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        pthread_join(thread[ihilos], NULL);
    }
}