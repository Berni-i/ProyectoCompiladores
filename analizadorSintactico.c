#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"


void comenzarLectura(){
    tipoelem *e;

    do
    {
        e = siguienteElemento();

        if(e != NULL) printf("<%s, %d>\n", e->lexema, e->componenteLexico);
    } while (e != NULL);

    
}