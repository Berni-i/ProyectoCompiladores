#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"


void comenzarLectura(){
    tipoelem *e;

    do
    {
        e = siguienteElemento();

        printf("<%s, %d>", e->lexema, e->componenteLexico);
    } while (e != NULL);
    
}