#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"

FILE *fichero;

//declaración de los dos buffers con un espacio extra para EOF
char b1[TAMCADENA+1], b2[TAMCADENA+1];

//evitar que el retroceso de un caracter pueda suponer que se salte contenido
bool cargar = true;

//punteros de inicio y delantero
char *inicio = b1, *delantero = b1;


//cargar el buffer correspondiente
void cargarBuffer(char *buffer){

    /*TODO*/
    //tratamiento de errores en caso de perder el puntero de inicio
    if(cargar){ }
        fread(buffer,1,TAMCADENA,fichero);

        for (int i = 0; i < TAMCADENA; i++)
        {
            printf("%c", *(b1+i));
        }
    else{
        //habilitar la carga para la siguientne vez
        cargar = true;
    }
}

//iniciar buffer por primera vez y guardar la referencia al fichero
void iniciarBuffer(FILE *id_fichero){
    fichero = id_fichero;

    //incluir EOF
    *(b1 + TAMCADENA) = EOF;
    *(b2 + TAMCADENA) = EOF;

    cargarBuffer(b1);
}

//función que permite pasar cada caracter al analizador sintáctico
char siguienteCaracter(){
    char caracter = *delantero;

    //comprobar si se encuentra en uno de los fines de fichero
    if(caracter == EOF){
        if(delantero == (b1 + TAMCADENA)){
            cargarBuffer(b2);
            delantero = b2;
        }else if(delantero == (b2)){
            cargarBuffer(b1);
            delantero = b1;
        }else{
            return EOF;
        }
    }

    delantero += 1;
    return caracter;
}

//devolver la palabra en el momento en que el analizador léxico detecte que se ha llegado
//a un estado final
char* devolverPalabra(){
    char* palabra = "";

    while(inicio != delantero){
        if(inicio == (b1 + TAMCADENA)){
            inicio = b2;
        }else if(inicio == (b2)){
            inicio = b1;
        }

        palabra += *inicio;
        inicio += 1;
    }

    return palabra;
}

//función que permita ignorar caracteres cuando se trate de espacios o comentarios
void saltarCaracter(){
    //inicio += 1;
    inicio = delantero;
    //ya que delantero irá posición a posición y se pretende que se ignore un caracter
}

void devolverCaracter(){
    //función que servirá para devolver un caracter
    if(delantero == b1){
        delantero = (b2 + TAMCADENA);
        cargar = false;
    }else if(delantero == b2){
        delantero = (b1 + TAMCADENA);
        cargar = false;
    }else{
        delantero -= 1;
    }

}
