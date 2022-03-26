#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"
#include "string.h"


void comenzarLectura(){
    tipoelem *e;

    e = siguienteElemento();

    while(e != NULL){
        
        printf("<%s, %d>\n", e->lexema, e->componenteLexico);

        free(e->lexema);
        free(e);

        e = siguienteElemento();
    }

}
