//definiciones de las palabras clave
#define PACKAGE 500
#define IMPORT 501
#define FUNC 502
#define CHAN 503
#define VAR 504
#define FOR 505
#define RANGE 506
#define GO 507

//definiciones de operadores
#define DOSPUNTOSIGUAL 508
#define MASIGUAL 509
#define FLECHAIZQUIERDA 510
#define CADENAS 511

//definición de literales
#define ENTERO 512
#define FLOTANTES 513

//definición del tamaño máximo de la cadena
#define TAMCADENA 32

//definición de las estrcuturas con las que trabajará el árbol de la tabla de símbolos
typedef struct {
	char lexema[TAMCADENA];
	int componenteLexico;
} tipoelem; //definir tipoelem aquí para no modificar el .c
