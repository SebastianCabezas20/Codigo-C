
/*LABORATORIO 1 
Nombre: Sebastian cabezas
RUT: 20.453.460-8
Seccion: B-2 
*/
typedef struct tripulante tripulante;

//definicion cabeceras de funciones
void obtenerDatos(int *cantidadTripulantes,int *peso);
void obtenerNombre(tripulante * tripulante, int cantidadTripulantes);
int sumaArreglo(int *arreglo, int cantidad);
void agregarSolucion(tripulante *tripulantes,int cantidad,int *solucion);
void filtroPeso(tripulante *tripulantes,int *arreglo,int j,int cantidad,int peso);
void borrarContenidoIntermedio();
void ordenamiento(int**soluciones,int cantidad,int canSoluciones,int *aux);
void copiarSoluciones(int **soluciones,int canSoluciones, int canTripulantes);
void agregarOut(tripulante *tripulantes,int **soluciones, int cantidad,int canSoluciones);