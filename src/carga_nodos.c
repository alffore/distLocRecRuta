//
// Created by alfonso on 14/09/21.
//
#include "distlocrutac.h"


int cargaArchivoNodo(char *snomarchivo, PNodo pnodo);

void parseaLineaNodo(char *slinea, PNodo pnodo);

void convierteCoordNodo(PNodo,double,double);

/**
 *
 * @param snomarchivo
 * @param pnodo
 * @return
 */
int cargaArchivoNodo(char *snomarchivo, PNodo pnodo) {

    printf("Carga nodos ...\n");

    FILE *fp = fopen(snomarchivo, "r");
    unsigned int pos = 0;

    if (fp != NULL) {
        char buffer[MAX_LONG];

        while (fgets(buffer, MAX_LONG, fp)) {
            parseaLineaNodo(buffer, pnodo + pos);
            pos++;
        }
    }

    fclose(fp);
    return 0;
}

/**
 *
 * @param slinea
 * @param pnodo
 */
void parseaLineaNodo(char *slinea, PNodo pnodo) {
    char *result = NULL;
    double lon,lat;

    result = strtok(slinea, SEP);

    lon = atof(result);
    result = strtok(NULL, SEP);

    pnodo->lon=lon;

    lat = atof(result);
    result = strtok(NULL, SEP);

    pnodo->lat=lat;

    pnodo->id_nodo = atoi(result);


    pnodo->id_rec = -1;

    for (int i = 0; i < TAM_SUBN; i++) {
        pnodo->adist[i] = -1.0;
        pnodo->aindex_nodos[i] = -1;
    }

    pnodo->nsn = 0;

    pnodo->dist_rec=0.0;
    pnodo->delta=0.0;

    convierteCoordNodo(pnodo,lon,lat);
}

/**
 *
 * @param p
 */
void convierteCoordNodo(PNodo p,double lon,double lat) {

    double r;

    lat = lat * M_PI / 180.0;
    lon = lon * M_PI / 180.0;

    p->x = sin(lon) * cos(lat);
    p->y = cos(lon) * cos(lat);
    p->z = sin(lat);

    r = pow(p->x, 2.0) + pow(p->y, 2.0) + pow(p->z, 2.0);
    r = sqrt(r);

    p->x /= r;
    p->y /= r;
    p->z /= r;
}
