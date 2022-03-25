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
    int leidos;

    /*TODO*/
    // tratamiento de errores en caso de perder el puntero de inicio
    if (cargar && !feof(fichero))
    {
        leidos = fread(buffer, 1, TAMCADENA, fichero);

        //introducir el caracter EOF porque fread no lo introduce por defecto
        if(leidos < TAMCADENA){
            *(buffer + leidos) = EOF;
        }

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

    //printf("sig caracter delantero = %c inicio = %c\n", *delantero, *inicio);

    // comprobar si se encuentra en uno de los fines de fichero
    if (caracter == EOF)
    {

        //printf("delantero = %c inicio = %c\n", *delantero, *inicio);

        if (delantero == (b1 + TAMCADENA))
        {
            cargarBuffer(b2);
            delantero = b2;
            caracter = *b2;
            delantero += 1;
            //printf("después de la carga delantero = %c inicioeee = %c\n", *delantero, *inicio);
        }
        else if (delantero == (b2 + TAMCADENA))
        {
            cargarBuffer(b1);
            delantero = b1;
            caracter = *b1;
            delantero += 1;
            //delantero+=1;

            //printf("delantero = %c inicioaa = %c\n", *delantero, *inicio);
        }
        else
        {
            printf("Caracter final leido\n");
            return EOF;
        }
    }else{
        //printf("avanza 1\n");
        delantero += 1;
    }

    //if(*inicio == EOF) inicio = delantero;

    //printf("caracter %c\n",caracter);

    return caracter;
}

// devolver la palabra en el momento en que el analizador léxico detecte que se ha llegado
// a un estado final
char *devolverPalabra()
{
    int i = 0, tam = 8;
    char *palabra = malloc(tam+1);

    //si se retrasa una posición en el momento de cambiar de buffer estarán en la misma posición
    //los dos punteros
    if(inicio == delantero){
        *palabra = *delantero;
        *(palabra + 1) = '\0';

       inicio++;
       delantero++;
    }

    while (inicio != delantero)
    {
        if (*inicio == EOF)
        {
            if(inicio == (b1 + TAMCADENA))
            {
                inicio = b2;
                //printf("dos\n");
            }
            else if (inicio == (b2 + TAMCADENA))
            {
                inicio = b1;
                //printf("dossss\n");
            }
        }

        if(i == tam){
            tam += 8;
            palabra = realloc(palabra, tam+1);
        }

        *(palabra + i) = *inicio;
        *(palabra + i + 1) = '\0';

        //sino nunca se llega a la primera posicion
        if(inicio == delantero) break;

        inicio += 1;
        i++;
    }




    //sino se queda en eof si acaba el buffer justo
    if (*inicio == EOF)
    {
        if(inicio == (b1 + TAMCADENA))
        {
            inicio = b2;
            //printf("dos\n");
        }
        else if (inicio == (b2 + TAMCADENA))
        {
            inicio = b1;
            //printf("tres\n");
        }
    }

    //printf("palabra devuelta %s\n", palabra);
    //printf("posicion de delantero= %c e inicio %c\n", *delantero, *inicio);
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

    delantero -= 1;
    //printf("chao\n");

    // función que servirá para devolver un caracter
    if (delantero == b1)
    {
        delantero = (b2 + TAMCADENA);
        cargar = 0;
        //printf("holaaaa\n");
    }
    else if (delantero == b2)
    {
        delantero = (b1 + TAMCADENA);
        cargar = 0;
        //printf("adios\n");
    }
}
