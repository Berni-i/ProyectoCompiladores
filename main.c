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
    

    //COMENZAR BUCLE
    //llamar a la función del analizador sintáctico.



    //cerrar el fichero
    fclose(fuente);
    //destruir la tabla de símbolos
    destruirTabla();
    return 0;
}
