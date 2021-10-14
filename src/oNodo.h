
#ifndef __NODO_H__
#define __NODO_H__

struct Nodo {

    double lon, lat;

    double x, y, z;
    long id_nodo;

    //long aid_nodos[TAM_SUBN];
    long aindex_nodos[TAM_SUBN];
    double adist[TAM_SUBN];
    int nsn; //cantidad de subnodos

    long id_rec;
    double dist_rec;

    double delta;
};

typedef struct Nodo *PNodo;

#endif