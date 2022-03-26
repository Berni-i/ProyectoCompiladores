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
    tipoelem *e;
    

    // leer caracter
    char caracter = siguienteCaracter();

    // saltar los espacios y los finales de línea
    while (caracter == 32 || caracter == '\n')
    {
        saltarCaracter();
        caracter = siguienteCaracter();
    }

    // si es el final de fichero devolver null
    if (caracter == EOF)
    {
        return NULL;
    }

    // detectar comentarios y omitirlos también
    if (caracter == '/')
    {
        caracter = siguienteCaracter();

        if (caracter == '/')
        {
            //saltar hasta el final de línea
            while (caracter != '\n')
            {
                caracter = siguienteCaracter();
                saltarCaracter();
            }
        }
        else if (caracter == '*')
        {
            while (caracter != EOF)
            {
                caracter = siguienteCaracter();
                saltarCaracter();

                //saltar hasta que encuentre un */
                if (caracter == '*')
                {
                    caracter = siguienteCaracter();
                    saltarCaracter();

                    if (caracter == '/')
                    {
                        caracter = siguienteCaracter();
                        saltarCaracter();
                        break;
                    }
                }
            }
        }
        else
        {
            //reservar memoria después de comprobar que no es un malloc
            e = malloc(sizeof(tipoelem));

            //devolver / si no se trata de un comentario
            caracter = '/';

            devolverCaracter();

            e->lexema = devolverPalabra();
            e->componenteLexico = caracter;
            saltarCaracter();

            return e;
        }
    }

    //reservar memoria después de comprobar que no es un malloc
    e = malloc(sizeof(tipoelem));

    //volver a saltar los espacios
    while (caracter == 32 || caracter == '\n')
    {
        saltarCaracter();
        caracter = siguienteCaracter();
    }


    // comprobar si se trata de una cadena alfanumérica
    // un caracter del alfabeto o una barra baja
    if (((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122)) || caracter == '_')
    {
        // autómata de cadenas alfanuméricas
        cadenaAlfanumerica(caracter, e);
    }
    else if (caracter == '.' || (caracter >= 48 && caracter <= 57))
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
    else
    { // lexemas que solo contengan un caracter como +, -, )...
        e->lexema = devolverPalabra();
        e->componenteLexico = caracter;
        saltarCaracter();
    }

    return e;
}

// función para leer cadenas alfanuméricas
void cadenaAlfanumerica(char caracter, tipoelem *e)
{
    
    char leido = siguienteCaracter();

    while ((leido >= 65 && leido <= 90) || (leido >= 97 && leido <= 122) || (leido >= 48 && leido <= 57) || leido == 95)
    {
        // leer siguiente caracter
        leido = siguienteCaracter();
    }

    // devolver el último caracter que se haya leido
    devolverCaracter();

    // actualizar elemento
    e->lexema = devolverPalabra();

    // preguntar a la tabla de símbolos de qué se trata
    e->componenteLexico = devolverComponente(e->lexema);
}

//función para leer números
void numeros(char caracter, tipoelem *e)
{

    char leido = siguienteCaracter();

    if (caracter == '.')
    {
        // PUNTO FLOTANTE EMPEZANDO POR PUNTO
        if ((leido >= 48 && leido <= 57) || leido == 'e' || leido == 'E')
        {
            puntoFlotante(leido, e);
        }
        else
        {
            //solo se trata de un punto
            devolverCaracter();
            e->lexema = devolverPalabra();
            e->componenteLexico = caracter;
        }

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
        else if ((caracter == '0') && (leido == 'x' || leido == 'X'))
        {
            // HEXADECIMAL
            leido = siguienteCaracter();

            while ((leido >= 48 && leido <= 57) || (leido >= 97 && leido <= 102) || (leido >= 65 && leido <= 70))
            {
                leido = siguienteCaracter();
            }

            devolverCaracter();

            // actualizar elemento
            e->lexema = devolverPalabra();
            e->componenteLexico = ENTERO;
        }
        else if (leido == 'i')
        {
            // IMAGINARIO
            e->lexema = devolverPalabra();
            e->componenteLexico = IMAGINARIOS;
        }
        else if (leido == 'e' || leido == 'E')
        {
            //NÚMERO CON EXPONENTE
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

            devolverCaracter();

            e->lexema = devolverPalabra();
            e->componenteLexico = FLOTANTES;
        }
        else
        {
            //ENTERO SIMPLE
            devolverCaracter();
            
            e->lexema = devolverPalabra();
            e->componenteLexico = ENTERO;
        }
    }
}

void operadoresVariosDigitos(char caracter, tipoelem *e)
{
    char leido;

    //:=
    if (caracter == ':')
    {
        leido = siguienteCaracter();

        if (leido == '=')
        {
            e->lexema = devolverPalabra();
            e->componenteLexico = DOSPUNTOSIGUAL;
        }
        else
        {
            devolverCaracter();

            e->lexema = devolverPalabra();
            e->componenteLexico = ':';
        }
    }

    //+=
    if (caracter == '+')
    {
        leido = siguienteCaracter();

        if (leido == '=')
        {
            e->lexema = devolverPalabra();
            e->componenteLexico = MASIGUAL;
        }
        else
        {
            devolverCaracter();

            e->lexema = devolverPalabra();
            e->componenteLexico = '+';
        }
    }

    //<-
    if (caracter == '<')
    {
        leido = siguienteCaracter();

        if (leido == '-')
        {
            e->lexema = devolverPalabra();
            e->componenteLexico = FLECHAIZQUIERDA;
        }
        else
        {
            devolverCaracter();

            e->lexema = devolverPalabra();
            e->componenteLexico = '<';
        }
    }
}

void puntoFlotante(char caracter, tipoelem *e)
{

    char leido = siguienteCaracter();

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
            //error porque no tendría exponente
        }
    }

    if (leido == 'i')
    {
        e->lexema = devolverPalabra();
        e->componenteLexico = IMAGINARIOS;
    }
    else
    {
        devolverCaracter();

        e->lexema = devolverPalabra();
        e->componenteLexico = FLOTANTES;
    }
}

void cadenas(tipoelem *e)
{
    char leido;

    do
    {
        //leer caracteres hasta que se encuentre otras comillas o EOF
        leido = siguienteCaracter();

        if (leido == '\\')
        {
            leido = siguienteCaracter();

            if (leido == '"')
            {
                continue;
            }
        }

        if (leido == '"')
            break;

    } while (leido != EOF);

    // actualizar elemento
    e->lexema = devolverPalabra();
    e->componenteLexico = CADENAS;
}
