#include <stdio.h>
#include <stdlib.h>
#include "tablaSimbolos.h"
#include "sistemaDeEntrada.h"

//declaración del fichero con el código fuente
FILE *fuente;

int main(int argc, char const *argv[])
{

    //INICIALIZAR ESTRUCTURAS DE DATOS

    //abrir fichero en modo lectura
    fuente = fopen("concurrentSum.go", "r");

    inicializarTabla();
    iniciarBuffer(fuente);
    

    fclose(fuente);
    return 0;
}
