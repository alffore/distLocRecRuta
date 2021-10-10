#ifndef __LOCALIDAD_H__
#define __LOCALIDAD_H__


struct Localidad {
    double x, y, z;
    long id_loc;
    long id_nodo;
    double dist_nodo;
    long index_nodo;
};

typedef struct Localidad *PLocalidad;



#endif