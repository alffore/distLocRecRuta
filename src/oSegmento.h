#ifndef __SEGMENTO_H__
#define __SEGMENTO_H__



struct Segmento {
    long id_nodo0;
    long id_nodo1;
    double dist;
};

typedef struct Segmento* PSegmento;

#endif