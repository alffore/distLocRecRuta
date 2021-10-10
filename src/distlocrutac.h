
#ifndef __DISTLOCRUTAC_H__
#define __DISTLOCRUTAC_H__


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>


#define RT 6371008.8
#define NUM_HILOS 8
#define MAX_DIST 20015114.44
#define SEP ","
#define MAX_LONG 512
#define TAM_SUBN 11
#define ITER_REC 600


#include "oLocalidad.h"
#include "oRecurso.h"
#include "oSegmento.h"
#include "oNodo.h"

#endif