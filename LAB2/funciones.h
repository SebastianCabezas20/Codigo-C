/*LABORATORIO 2
Nombre: Sebastian cabezas
RUT: 20.453.460-8
Seccion: B-2 
*/

typedef struct nodo nodo;
typedef struct preferencia preferencia;
typedef struct colaPreferencia colaPreferencia;
typedef struct colaCancion colaCancion; 

//Cola cancion
colaCancion * crearColaCancion();
colaCancion * encolarCancion(colaCancion * colaAnt,nodo* cancion);
nodo * primeroColaCancion(colaCancion * Cola);
void desencolarCancion(colaCancion * Cola);

//Cola preferencia
preferencia * crearPreferencia(int numero);
colaPreferencia * crearColaPreferencia();
colaPreferencia * encolarPreferencia(colaPreferencia * colaAnt, preferencia* Preferencia);
preferencia * primeroColaPreferencia(colaPreferencia * Cola);
void desencolarPreferencia(colaPreferencia * cola);

//Funciones
colaPreferencia * obtenerTiempo(int *minutos,int *segundos);
nodo * buscadorCancion(nodo * primero , int codigo);
void playlist(nodo * canciones);
nodo *insertarOrdenado(nodo * primero, nodo * nuevo);
char * buscadorArtista(int codArtista);
char * buscadorGenero(int codGenero);
void liberar(nodo * primero);
nodo * crearNodo(char * nombre,char * nombreGenero,char * nombreArtista,int min,int seg,int puntaje,int codArtista,int codGenero);
nodo * obtenerCanciones(nodo * canciones);
nodo * insertar(nodo * primero,nodo * nuevo);
int valorLetra(char * nombreArtista);
nodo * ordenarNombre(nodo * primero);
nodo * ordenarTiempo(nodo * primero);
void agregarArchivo(nodo * canciones);