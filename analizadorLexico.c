#include "definiciones.h"
#include "sistemaDeEntrada.h"
#include "tablaSimbolos.h"
#include <string.h>
#include <stdlib.h>

void cadenaAlfanumerica(char caracter, tipoelem *e);

void numeros(char caracter, tipoelem *e);

void operadoresVariosDigitos(char caracter, tipoelem *e);

void puntoFlotante(char caracter, tipoelem *e);

void cadenas(tipoelem *e);

tipoelem *siguienteElemento()
{
    // leer caracter
    char caracter = siguienteCaracter();

    //sleep(1);

    tipoelem *e;


    // saltar los espacios
    while (caracter == 32 || caracter == '\n')
    {
        saltarCaracter(); // mandar inicio a la posición de delantero
        caracter = siguienteCaracter();
        //printf("leido espacio o barra n\n");
    }

    if (caracter == EOF)
    {
        printf("Final analizador léxico\n");
        return NULL;
    }

    e = malloc(sizeof(tipoelem));

    // comprobar si se trata de una cadena alfanumérica
    // un caracter del alfabeto o una barra baja
    if (((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122)) || caracter == 95)
    {
        // autómata de cadenas alfanuméricas
        cadenaAlfanumerica(caracter, e);
    }
    else if (caracter == 46 || (caracter >= 48 && caracter <= 57))
    { // números empiezan por punto, 1 o 0x
        // autómata de números
        numeros(caracter, e);
    }
    else if (caracter == 58 || caracter == 60 || caracter == 43)
    { // considerar para el código :=, <-, +=,
        // autómata para operadores de varios símbolos
        operadoresVariosDigitos(caracter, e);
    }
    else if (caracter == '"')
    {
        cadenas(e);
    }
    else if(caracter == '/'){
        caracter = siguienteCaracter();

        if(caracter == '/'){
            while(caracter != '\n'){
                caracter = siguienteCaracter();
            }
        }else if(caracter == '*'){
            while(caracter != EOF){
                caracter = siguienteCaracter();

                if(caracter == '*'){
                    caracter = siguienteCaracter();

                    if(caracter == '/') break;
                }
            }
        }
        else{
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = caracter;
            saltarCaracter();
        }
    }
    else
    { // lexemas que solo contengan un caracter como +, -, )...
        strcpy(e->lexema, devolverPalabra());
        e->componenteLexico = caracter;
        saltarCaracter();
    }

    //printf("%s\n", e->lexema);

    return e;
}

void cadenaAlfanumerica(char caracter, tipoelem *e)
{
    // función para leer cadenas alfanuméricas
    char leido = siguienteCaracter();

    while ((leido >= 65 && leido <= 90) || (leido >= 97 && leido <= 122) || (leido >= 48 && leido <= 57) || leido == 95)
    {
        // leer siguiente caracter
        leido = siguienteCaracter();
    }

    // devolver el último caracter que se haya leido
    devolverCaracter();

    // actualizar elemento
    strcpy(e->lexema, devolverPalabra()); //mirar strcpy

    // preguntar a la tabla de símbolos de qué se trata
    e->componenteLexico = devolverComponente(e->lexema);
}


void numeros(char caracter, tipoelem *e)
{
    // función para leer cadenas alfanuméricas
    // componentes léxicos para cada cada tipo de numero
    char leido = siguienteCaracter();

    if (caracter == 36)
    {
        // PUNTO FLOTANTE EMPEZANDO POR PUNTO
        puntoFlotante(leido, e);
    }
    else if (caracter >= 48 && caracter <= 57)
    {
        // EMPEZANDO POR DÍGITOS
        while (leido >= 48 && leido <= 57)
        {
            leido = siguienteCaracter();
        }

        if (leido == '.')
        {
            // PUNTO FLOTANTE
            puntoFlotante(leido, e);
        }
        else if ((caracter == 0) && (leido == 'x' || leido == 'X'))
        {
            // HEXADECIMAL
            while ((leido >= 48 && leido <= 57) || (leido >= 97 && leido <= 102) || (leido >= 65 && leido <= 70))
            {
                leido = siguienteCaracter();
            }

            devolverCaracter();

            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = ENTERO;
        }
        else if (leido == 'i')
        {
            // IMAGINARIO
            //printf("holaaa");
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = IMAGINARIOS;
        }
        else
        {

            devolverCaracter();

            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = ENTERO;
        }
    }

}

void operadoresVariosDigitos(char caracter, tipoelem *e)
{
    char leido;

    //:=
    if(caracter == ':'){
        leido = siguienteCaracter();

        if(leido == '='){
            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = DOSPUNTOSIGUAL;
        }else{
            devolverCaracter();

            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = ':';
        }
    }

    //+=
    if(caracter == '+'){
        leido = siguienteCaracter();

        if(leido == '='){
            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = MASIGUAL;
        }else{
            devolverCaracter();

            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = '+';
        }
    }


    //<-
    if(caracter == '<'){
        leido = siguienteCaracter();

        if(leido == '-'){
            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = FLECHAIZQUIERDA;
        }else{
            devolverCaracter();

            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = '<';
        }
    }
}

void puntoFlotante(char caracter, tipoelem *e)
{

    char leido = siguienteCaracter();

    // leer números
    while (leido >= 48 && leido <= 57)
    {
        leido = siguienteCaracter();
    }

    if (leido == 'E' || leido == 'e')
    {
        leido = siguienteCaracter();
        //printf("holeeee\n");

        if (leido == '+' || leido == '-')
        {
            leido = siguienteCaracter();
        }

        if (leido >= 48 && leido <= 57)
        {
            while (leido >= 48 && leido <= 57)
            {
                leido = siguienteCaracter();
                //printf("holiiiii\n");
            }
        }
        else
        {
            //printf("ooooooº\n");
        }
    }

    //printf("holiixxxiii %c\n", leido);

    if (leido == 'i')
    {
        //printf("holaa\n");
        strcpy(e->lexema, devolverPalabra());
        e->componenteLexico = IMAGINARIOS;
        //printf("holaa\n");
    }
    else
    {
        // devolver el último caracter que se haya leido
        devolverCaracter();

        // actualizar elemento
        strcpy(e->lexema, devolverPalabra());
        e->componenteLexico = FLOTANTES;
    }

}

void cadenas(tipoelem *e)
{
    char leido;

    do
    {
        leido = siguienteCaracter();

        if(leido == '/'){
            leido = siguienteCaracter();

            if(leido == '"'){
                leido = siguienteCaracter();
                continue;
            }
        }

    } while (leido != '"');

    // actualizar elemento
    strcpy(e->lexema, devolverPalabra());
    e->componenteLexico = CADENAS;
}
