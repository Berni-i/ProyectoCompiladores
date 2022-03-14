#include "definiciones.h"
#include "sistemaDeEntrada.h"
#include <string.h>
#include <stdlib.h>



void cadenaAlfanumerica(char caracter, tipoelem *e);

void numeros(char caracter, tipoelem *e);

void operadoresVariosDigitos(char caracter, tipoelem *e);



tipoelem *siguienteElemento(){
    //leer caracter
    char caracter = siguienteCaracter();

    tipoelem *e;
    e = malloc(sizeof(tipoelem));

    //saltar los espacios
    while(caracter == 32){
        caracter = siguienteCaracter();
        saltarCaracter(); //mandar inicio a la posición de delantero
    }

    //comprobar si se trata de una cadena alfanumérica
    if(((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122)) || caracter == 95){
        //autómata de cadenas alfanuméricas
        cadenaAlfanumerica(caracter, e);

    }else if(caracter == 46 || (caracter >= 48 && caracter <= 57)){ //números empiezan por punto, 1 o 0x
        //autómata de números
        numeros(caracter, e);

    }else if(caracter == 58 || caracter == 60 || caracter == 43){ //considerar para el código :=, <-, +=,
        //autómata para operadores de varios símbolos
        operadoresVariosDigitos(caracter, e);

    }else{ //lexemas que solo contengan un caracter como +, -, )...
        strcpy(e->lexema, (char*) &caracter);
        e->componenteLexico = caracter;
    }

    printf("%s\n", e->lexema);

    return e;

}



void cadenaAlfanumerica(char caracter, tipoelem *e){
    //función para leer cadenas alfanuméricas
    char leido  =  siguienteCaracter();

    while((leido >= 65 && leido <= 90) || (leido >= 97 && leido <= 122) || (leido >= 48 && leido <= 57) || leido == 95){
        //leer siguiente caracter
        leido = siguienteCaracter();
    }

    //devolver el último caracter que se haya leido
    devolverCaracter();

    //actualizar elemento
    strcpy(e->lexema, devolverPalabra());

    //preguntar a la tabla de símbolos de qué se trata

}

void numeros(char caracter, tipoelem *e){
    //función para leer cadenas alfanuméricas
    //componentes léxicos para cada cada tipo de numero
    char leido = siguienteCaracter();

    if(leido == 36){ //decimal
        leido = siguienteCaracter();

        while((caracter >= 48 && caracter <= 57)){

        }
    }else if(leido == 'x'){ //

    }


}

void operadoresVariosDigitos(char caracter, tipoelem *e){
    //función para leer cadenas alfanuméricas

}
