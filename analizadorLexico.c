#include "definiciones.h"
#include "sistemaDeEntrada.h"


tipoelem *siguienteElemento(){
    //leer caracter
    char caracter = siguienteCaracter();

    tipoelem e;

    //saltar los espacios
    while(caracter == 32){
        caracter = siguienteCaracter();
        saltarCaracter();
        //si por cada espacio leído se adelanta una posición, if innecesarios
        //posibles problemas al no adelantar el puntero inicio
    }

    //comprobar si se trata de una cadena alfanumérica
    if((caracter > 65 && caracter < 90) && (caracter > 65 && caracter < 90)){
        //autómata de cadenas alfanuméricas
        e = *cadenaAlfanumerica(caracter);
    }else if(caracter == 46 || caracter >= 48 && caracter <= 57){ //números empiezan por punto, 1 o 0x
        e = *numeros(caracter);

    }else if(caracter == 58 || caracter == 60 || caracter == 43){ //considerar para el código :=, <-, +=,

    }else{ //lexemas que solo contengan un caracter como +, -, )...
        switch (caracter) {
            case 43: //para todos los símbolos ascii
                e.lexema = (char*)caracter;
                e.componenteLexico = caracter;
                return caracter;
        }
    }

    return e;

}

/*

tipoelem *cadenaAlfanumerica(char caracter){
    //función para leer cadenas alfanuméricas
    char leido;

    while(leido )

}

tipoelem *numeros(char caracter){
    //función para leer cadenas alfanuméricas

}

tipoelem *operadoresVariosDigitos(char caracter){
    //función para leer cadenas alfanuméricas

}*/
