#include "abb.h"
#include <stdio.h>
#include <string.h>

abb tablaSimbolos;

//función auxiliar para imprimir la tabla de símbolos
void imprimir(abb A) {
    tipoelem E;

	if(!es_vacio(A)){
	  imprimir(izq(A));
	  leer(A,&E);
          printf("%s, %d\n", E.lexema, E.componenteLexico);
	  imprimir(der(A));
	}
}

//función para iniciar la tabla con las palabras reservadas
void inicializarTabla(){

    //declaración de los arrays cn los valores y las palabras
    char nombres[][TAMCADENA] = {"package", "import", "func", "chan", "var", "for", "range", "go"};
    int definiciones[] = {PACKAGE, IMPORT, FUNC, CHAN, VAR, FOR, RANGE, GO};

    //Se crea el árbol binario
    crear(&tablaSimbolos);

    for (int i = 0; i < sizeof(nombres)/TAMCADENA; i++)
    {
        //printf("%s\n", nombres[i]);

        //crear un struct por que contenga lexema y componente léxico
        tipoelem elemento;
        strcpy(elemento.lexema, nombres[i]);
        elemento.componenteLexico = definiciones[i];

        //insertar el struct dentro del árbol
        insertar(&tablaSimbolos, elemento);

    }

    imprimir(tablaSimbolos);

}

void destruirTabla(){
    destruir(&tablaSimbolos);
}