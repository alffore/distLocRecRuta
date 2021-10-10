
#ifndef __RECURSO_H__
#define __RECURSO_H__

struct Recurso {
    double x, y, z;
    long id_rec;
    long id_nodo;
    double dist_nodo;
    long index_nodo;
};

typedef struct Recurso *PRecurso;

#endif