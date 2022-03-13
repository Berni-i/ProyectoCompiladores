//definiciones de las palabras clave
#define PACKAGE 500
#define IMPORT 501
#define FUNC 502
#define CHAN 503
#define VAR 504
#define FOR 505
#define RANGE 506
#define GO 507

#define TAMCADENA 32

typedef struct {
	char lexema[TAMCADENA];
	int componenteLexico;
} tipoelem; //definir tipoelem aquí para no modificar el .c