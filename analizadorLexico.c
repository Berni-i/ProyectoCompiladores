#include "definiciones.h"
#include "sistemaDeEntrada.h"
#include <string.h>
#include <stdlib.h>

void cadenaAlfanumerica(char caracter, tipoelem *e);

void numeros(char caracter, tipoelem *e);

void operadoresVariosDigitos(char caracter, tipoelem *e);

void puntoFlotante(char caracter, tipoelem *e);

tipoelem *siguienteElemento()
{
    // leer caracter
    char caracter = siguienteCaracter();

    tipoelem *e;
    e = malloc(sizeof(tipoelem));

    if (caracter == EOF)
    {
        free(e);
        return NULL;
    }

    // saltar los espacios
    while (caracter == 32 || caracter == '\n')
    {
        saltarCaracter(); // mandar inicio a la posición de delantero
        caracter = siguienteCaracter();
    }

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
    else
    { // lexemas que solo contengan un caracter como +, -, )...
        strcpy(e->lexema, (char *)&caracter);
        e->componenteLexico = caracter;
    }

    printf("%s\n", e->lexema);

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
    strcpy(e->lexema, devolverPalabra());

    // preguntar a la tabla de símbolos de qué se trata
    // TODO
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

            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = ENTERO;
        }
        else if (leido == 'i')
        {
            // IMAGINARIO
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = IMAGINARIOS;
        }
        else
        {
            // actualizar elemento
            strcpy(e->lexema, devolverPalabra());
            e->componenteLexico = ENTERO;
        }
    }
}

void operadoresVariosDigitos(char caracter, tipoelem *e)
{
    // función para leer cadenas alfanuméricas
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

        if (leido == '+' || leido == '-')
        {
            leido = siguienteCaracter();
        }

        if (leido >= 48 && leido <= 57)
        {
            while (leido >= 48 && leido <= 57)
            {
                leido = siguienteCaracter();
            }
        }
        else
        {
            // Error, número sin exponente
        }
    }

    if (leido == 'i')
    {
        strcpy(e->lexema, devolverPalabra());
        e->componenteLexico = IMAGINARIOS;
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
