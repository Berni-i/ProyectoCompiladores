#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"

FILE *fichero;

// declaración de los dos buffers con un espacio extra para EOF
char b1[TAMCADENA + 1], b2[TAMCADENA + 1];

// evitar que el retroceso de un caracter pueda suponer que se salte contenido
int cargar = 1;

// punteros de inicio y delantero
char *inicio = b1, *delantero = b1;

// cargar el buffer correspondiente
void cargarBuffer(char *buffer)
{

    /*TODO*/
    // tratamiento de errores en caso de perder el puntero de inicio
    if (cargar)
    {
        fread(buffer, 1, TAMCADENA, fichero);

        printf("\nimpresión del buffer\n");
        for (int i = 0; i < TAMCADENA; i++)
        {
            printf("%c", *(buffer + i));
        }
        printf("\n\n");
    }
    else
    {
        // habilitar la carga para la siguientne vez
        cargar = 1;
    }
}

// iniciar buffer por primera vez y guardar la referencia al fichero
void iniciarBuffer(FILE *id_fichero)
{
    fichero = id_fichero;

    // incluir EOF
    *(b1 + TAMCADENA) = EOF;
    *(b2 + TAMCADENA) = EOF;

    cargarBuffer(b1);
}

// función que permite pasar cada caracter al analizador sintáctico
char siguienteCaracter()
{
    char caracter = *delantero;

    printf("delantero = %c inicio = %c\n", *delantero, *inicio);

    // comprobar si se encuentra en uno de los fines de fichero
    if (caracter == EOF)
    {

         printf("delantero = %c inicio = %c\n", *delantero, *inicio);
        if (delantero == (b1 + TAMCADENA))
        {
            cargarBuffer(b2);
            delantero = b2;
            caracter = *b2;
            printf("delantero = %c inicio = %c\n", *delantero, *inicio);
        }
        else if (delantero == (b2 + TAMCADENA))
        {
            cargarBuffer(b1);
            delantero = b1;
            caracter = *b1;
        }
        else
        {
            return EOF;
        }
    }else{
        delantero += 1;
    }


    return caracter;
}

// devolver la palabra en el momento en que el analizador léxico detecte que se ha llegado
// a un estado final
char *devolverPalabra()
{
    int i = 0, tam = 8;
    char *palabra = malloc(tam);
    

    while (inicio != delantero)
    {
        if (*inicio == EOF)
        {
            if (inicio == (b1 + TAMCADENA))
            {
                inicio = b2;
            }
            else if (inicio == (b2 + TAMCADENA))
            {
                inicio = b1;
            }
        }

        if(i == tam){
            tam += 8;
            palabra = realloc(palabra, tam);
        }

        *(palabra + i) += *inicio;
        inicio += 1;
        i++;
    }

    printf("palabra devuelta %s\n", palabra);
    return palabra;
}

// función que permita ignorar caracteres cuando se trate de espacios o comentarios
void saltarCaracter()
{
    // inicio += 1;
    inicio = delantero;
    // ya que delantero irá posición a posición y se pretende que se ignore un caracter
}

void devolverCaracter()
{
    // función que servirá para devolver un caracter
    if (delantero == b1)
    {
        delantero = (b2 + TAMCADENA);
        cargar = 0;
    }
    else if (delantero == b2)
    {
        delantero = (b1 + TAMCADENA);
        cargar = 0;
    }
    else
    {
        delantero -= 1;
    }
}
