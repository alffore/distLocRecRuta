#include "distlocrutac.h"

extern PNodo pNodo;

extern size_t tam_nodo;


void *recorrido(void *param);

void generaTR(void);

void generaRecorridos(void);

/**
 *
 * @param param
 * @return
 */
void *recorrido(void *param) {
    unsigned int *ihilo = (unsigned int *) param;


    for (size_t i = *ihilo; i < tam_nodo; i += NUM_HILOS) {
        PNodo pn = pNodo + i;
        if (pn->id_rec > 0 && pn->nsn > 0) {
            for (int j = 0; j < pn->nsn; j++) {
                size_t index = pn->aindex_nodos[j];
                if (i != index) {
                    double nueva_dist = pn->adist[j] + pn->dist_rec;
                    if ((pNodo + index)->id_rec < 0 ||
                        ((pNodo + index)->id_rec > 0 && (pNodo + index)->dist_rec > nueva_dist)) {
                        (pNodo + index)->delta += nueva_dist - (pNodo + index)->dist_rec;
                        (pNodo + index)->dist_rec = nueva_dist;
                        (pNodo + index)->id_rec = pn->id_rec;
                    }
                }
            }
        }
    }

    return NULL;
}

/**
 *
 */
void generaTR(void) {
    pthread_t thread[NUM_HILOS];
    int iret;
    unsigned int ihiloT[NUM_HILOS];

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        ihiloT[ihilos] = ihilos;
    }

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        iret = pthread_create(&thread[ihilos], NULL, recorrido, (void *) &ihiloT[ihilos]);

        if (iret) {
            fprintf(stderr, "Error al crear thread %d\n", ihilos);
        }
    }

    for (unsigned int ihilos = 0; ihilos < NUM_HILOS; ihilos++) {
        pthread_join(thread[ihilos], NULL);
    }
}


/**
 *
 */
void generaRecorridos(void) {

    double delta0 = 0.0;
    double delta1 = 0.0;

    long tam = 1;

    printf("Genera los recorridos ...\n");

    do {
        delta1 = delta0;

        generaTR();

        delta0 = 0.0;
        for (size_t i = 0; i < tam_nodo; i++) {
            delta0 += (pNodo + i)->delta;
        }

        printf("Ciclo: %li Marca recursos con nodo mas cercano: %lf\n", tam, delta1 - delta0);
        tam++;
    } while (delta1 != delta0 && tam <= ITER_REC);

}