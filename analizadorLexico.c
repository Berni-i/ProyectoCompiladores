#include "definiciones.h"
#include "sistemaDeEntrada.h"

tipoelem *siguienteElemento(){
    char caracter = siguienteCaracter();

    //saltar los espacios
    while(caracter == 32){
        caracter = siguienteCaracter();
        //posibles problemas al no adelantar el puntero inicio
    }

    if((caracter > 65 && caracter < 90) && (caracter > 65 && caracter < 90)){
        
    }

    
}