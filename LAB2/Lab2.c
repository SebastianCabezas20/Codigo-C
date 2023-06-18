/*LABORATORIO 2
Nombre: Sebastian cabezas
RUT: 20.453.460-8
Seccion: B-2 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

typedef struct nodo nodo;
typedef struct preferencia preferencia;
typedef struct colaPreferencia colaPreferencia;
typedef struct colaCancion colaCancion; 


//estructura de una cancion
struct nodo
{
	char nombreCancion[30];
	char nombreArtista[30];
	char nombreGenero[30];
	int minutos;//minutos de duracion
	int segundos;//segundos de duracion
	int puntaje;//puntaje que tiene la cancion
	int artista;//codigo de artista
	int genero;//codigo de genero
	nodo * siguiente;//puntero al siguiente nodo
	nodo * anterior;//puntero al nodo anterior
};


///////COLA CANCION
//Estreuctura de una cola cancion
struct colaCancion
{
	nodo * primero;
	nodo * ultimo;
};


//Salida: Cola de canciones nula
//Descrip: Crea una cola de canciones nula
// O(1)
colaCancion * crearColaCancion(){
	colaCancion * colaNueva =(colaCancion *)malloc(sizeof(colaCancion));//se reserva memoria para cola
	colaNueva->primero = NULL;//debido a que es nueva se apunta a NULL
	colaNueva->ultimo = NULL;
	return colaNueva;
}

//Entrada: Puntero a cola cancion, puntero a nodo cancion
//Salida: Cola de canciones modificada
//Descrip: Encola una cancion a la cola
// O(1)
colaCancion * encolarCancion(colaCancion * colaAnt,nodo* cancion){
	if(colaAnt->primero == NULL){//caso de que el primero sea nulo
		colaAnt->primero = cancion;
		colaAnt->ultimo = cancion;
		colaAnt->ultimo->siguiente = NULL;
		return colaAnt;
	}
	else{//caso general
		colaAnt->ultimo->siguiente = cancion;
		colaAnt->ultimo = cancion;
		colaAnt->ultimo->siguiente = NULL;
		return colaAnt;
	}
}

//Entrada: Puntero a cola cancion
//Salida: Puntero a cancion
//Descrip: Retorna la primera cancion de la cola.
// O(1)
nodo * primeroColaCancion(colaCancion * Cola){
	if(Cola->primero != NULL){//mientras el primero sea distinto de nulo se retornara
		return Cola->primero;
	}
	else{
		return NULL;
	}
}		

//Entrada: Puntero a cola cancion
//Descrip: desencola una cancion de la cola sin eliminar
// O(1)
void desencolarCancion(colaCancion * Cola){
	if(Cola->primero != NULL){
		Cola->primero = Cola->primero->siguiente;//se avanza
		if(Cola->primero == NULL){//caso que despues de encolar no existan mas nodos
			Cola->ultimo = NULL;
		}
	}
}


////////////////////////////////////////////////////////////

//estructura de un nodo preferencia
struct preferencia
{
	int numero;
	preferencia * siguiente;
};

//Entrada: Numero entero.
//Salida: Puntero a una preferencia
//Descrip: Crea una preferencia dado un numero.
preferencia * crearPreferencia(int numero){
	preferencia * nuevaPreferencia =(preferencia *)malloc(sizeof(preferencia));//se reserva memoria
	nuevaPreferencia->numero = numero;
	nuevaPreferencia->siguiente = NULL;
	return nuevaPreferencia;
};


///COLA PREFERENCIAS

//estructura de una cola de preferencias
struct colaPreferencia
{
	preferencia * primero;
	preferencia * ultimo;
};


//Salida: Puntero a cola de preferencias
//Descrip: Crea una cola de preferencias vacia.
// O(1)
colaPreferencia * crearColaPreferencia(){
	colaPreferencia * colaNueva =(colaPreferencia *)malloc(sizeof(colaPreferencia));//reservar memoria
	colaNueva->primero = NULL;//se anula los punteros
	colaNueva->ultimo = NULL;
	return colaNueva;	
}

//Entrada: Puntero a cola de preferencias y puntero a una preferencia.
//Salida: Puntero a cola de preferencias
//Descrip: Encolar preferencia en una cierta cola.
// O(1)
colaPreferencia * encolarPreferencia(colaPreferencia * colaAnt, preferencia* Preferencia){
	if(colaAnt->primero == NULL){//caso primero nulo
		colaAnt->primero = Preferencia;//como es el primero los dos apuntan al primero
		colaAnt->ultimo = Preferencia;
		colaAnt->ultimo->siguiente = NULL;
		return colaAnt;
	}
	else{//caso general
		colaAnt->ultimo->siguiente = Preferencia;//se encola al final
		colaAnt->ultimo = Preferencia;
		colaAnt->ultimo->siguiente = NULL;
		return colaAnt;
	}
}

//Entrada: Puntero a cola preferencias
//Salida: Puntero a preferencia
//Descrip: Retorna la primera preferencia de la cola.
// O(1)
preferencia * primeroColaPreferencia(colaPreferencia * Cola){
	if(Cola->primero != NULL){
		return Cola->primero;//se retorna el primero
	}
	else{
		return NULL;
	}
}

//Entrada: Puntero a cola preferencia
//Descrip: Desencola la primera preferencia de la lista.
// O(1)
void desencolarPreferencia(colaPreferencia * cola){
	if(cola->primero != NULL){
		cola->primero = cola->primero->siguiente;//se avanza al siguiente
		if(cola->primero == NULL){//caso que el primero quede nulo.
			cola->ultimo = NULL;//ultimo queda nulo.
		}
	}
}

//////////////////////////////////////////////////////////////////////


//Entrada: Direccion de memoria de minutos y segundos
//Salida: Puntero a cola de preferencias
//Descrip: se obtiene el tiempo limite y la cola de preferencias de archivo "preferencias.in".
// T(n) = 7c + 2n  o(n)
colaPreferencia * obtenerTiempo(int *minutos,int *segundos){
	FILE * archivo = fopen("preferencias.in","r");//abrimos el archivo
	if (archivo == NULL)
	{
		printf("ERROR AL ABRIR EL ARCHIVO\n");
	}
	char p;
	int numero;
	fscanf(archivo,"%d %c %d ",minutos,&p,segundos);//se lee el tiempo limite dado
	colaPreferencia * cola = crearColaPreferencia();//se crea cola
	while(fscanf(archivo,"%d",&numero) != EOF){//Se continuara siempre que lo leido no sea el final del archivo

		preferencia * nodo = crearPreferencia(numero);//se crea preferencia
		cola = encolarPreferencia(cola,nodo);//se encola preferencia
	}
	fclose(archivo);
	return cola;
};

//Entrada: Puntero a nodo cancion, que corresponde a una lista y un numero que pertenecera al codigo
//Salida: Puntero a cancion
//Descrip: Busca una cancion en una lista en base a un codigo de genero.
// T(n) = 2c + n   O(n)
nodo * buscadorCancion(nodo * primero , int codigo){
	nodo * aux = primero; //se crea un auxiliar para recorrer la lista
	while(aux != NULL){
		if(aux->genero == codigo){//caso que se encontro una cancion con ese genero
			return aux; 
		}
		aux = aux->siguiente; //se avanza
	}
	return aux;// caso que no se encontro y se retorna nulo
}


//Entrada: Puntero a nodo de canciones, que corresponde a una lista
//Descrip: Crea la playlist que se imprimira en el archivo "playlist.out"
// T(n) = 14c + 4n + n(16c + n )= 14c + 20nc + n^2   O(n^2)
void playlist(nodo * canciones){
	int minutosMax,segundosMax,totalParcial = 0; 
	colaPreferencia * preferencias = obtenerTiempo(&minutosMax,&segundosMax);//obtener preferencias y tiempo max O(n)
	//////////////////////////////////////////////////////////////////////

	int tiempoMaximo = (minutosMax*60) + segundosMax,tiempoRelativo = 0; //Se calcula tiempo maximo
	colaCancion * colaCanciones= crearColaCancion();//Se crea cola de canciones

	if(tiempoMaximo > 0 && canciones != NULL){
		nodo * cancion = canciones;// puntero auxiliar de lista 

		FILE * archivo = fopen("playlist.out","w");//se abre el archivo a escribir
		if(archivo == NULL){
			printf("ERROR AL ABRIR EL ARCHIVO\n");
			return;
		}

		while(cancion != NULL && tiempoMaximo >= tiempoRelativo){

			preferencia * PrimeraPreferencia = primeroColaPreferencia(preferencias);//se obtiene el primer elemento de la cola
			desencolarPreferencia(preferencias);//desencolamos la primera preferencia
			int codigo = PrimeraPreferencia->numero;
			preferencias = encolarPreferencia(preferencias,PrimeraPreferencia);//volvemos a encolar la preferencia
			cancion = buscadorCancion(canciones,codigo);//buscar cancion y sacar de la lista O(n)
			if(cancion != NULL){
				///////////////////////////////////////
				nodo * ant = cancion->anterior;
				nodo * des = cancion->siguiente;
				if(ant == NULL && des == NULL){//caso que sea solo un nodo
					canciones = NULL;
				}
				else if(ant == NULL){//caso que sea el primero nodo de la lista
					des->anterior = NULL;
					canciones = canciones->siguiente;
				}
				else if(des == NULL){//caso ultimo nodo de la lista
					ant->siguiente = NULL;
				}
				else{//caso general
					ant->siguiente = des;
					des->anterior = ant;
				}
				cancion->siguiente = NULL;
				cancion->anterior = NULL;
				//se comienza a escribir en el archivo la cancion encontrada
				fprintf(archivo,"%d;%s;%d:%d;%s;%s\n",cancion->puntaje,cancion->nombreCancion,cancion->minutos,cancion->segundos,cancion->nombreArtista,cancion->nombreGenero);
				///////////////////////////////////////////
				tiempoRelativo = tiempoRelativo + (cancion->minutos*60)+cancion->segundos;//Se actualiza el tiempo relativo
				colaCanciones = encolarCancion(colaCanciones,cancion);//encolamos cancion 
			}
		}

		if(tiempoMaximo > tiempoRelativo){ //Verificamos si salio del while por no encontrar mas canciones o se alcanzo el tiempo limite
			while(tiempoMaximo >= tiempoRelativo){
				cancion = primeroColaCancion(colaCanciones); //obtenemos la primera cancion de la cola
				tiempoRelativo = tiempoRelativo + (cancion->minutos*60)+cancion->segundos; //actualizamos tiempo
				//se escribe la cancion en el archivo
				fprintf(archivo,"%d;%s;%d:%d;%s;%s\n",cancion->puntaje,cancion->nombreCancion,cancion->minutos,cancion->segundos,cancion->nombreArtista,cancion->nombreGenero);
				desencolarCancion(colaCanciones);//desencolamos cancion
				colaCanciones = encolarCancion(colaCanciones,cancion);//encolamos cancion para utilizala denuevo
			}
		}
		int restante = tiempoRelativo - tiempoMaximo; //se calcula el tiempo restante y se escribe en archivo
		fprintf(archivo, "%d:%d \n",restante/60,restante%60 );
		fclose(archivo);
	}
	/// Se liberan las cola usadas
	while(preferencias->primero != NULL){
			preferencia * primero = primeroColaPreferencia(preferencias);
			desencolarPreferencia(preferencias);
			free(primero);
	}
	while(colaCanciones->primero != NULL){
		nodo * eliminar = primeroColaCancion(colaCanciones);
		desencolarCancion(colaCanciones);
		free(eliminar);
	}
}


////////////PRIMERA PARTE

//Entrada: Puntero a cancion que correspondera a la lista de canciones
//Salida: Puntero a cancion que correspondera a la lista de canciones modificada
//Descrip: Inserta una cancion en la lista de forma ordenada, mediante puntaje
// T(n) = 6c + 4nc   O(n)
nodo *insertarOrdenado(nodo * primero, nodo * nuevo){
	if(primero == NULL){//caso que este la lista vacia
		nuevo->siguiente = primero; // se enlista
		nuevo->anterior = NULL;
		primero = nuevo;
		return primero;

	}else if(primero->puntaje <= nuevo->puntaje){ //se corroborra el primer elemento
		nuevo->siguiente = primero; //se agrega a la primera posicion de la lista
		nuevo->anterior = NULL;
		primero->anterior = nuevo;
		primero = nuevo;
		return primero;
	}else{
		nodo * aux = primero->siguiente;
		nodo * auxAnt = primero;
		while(aux != NULL){
			if(aux->puntaje <= nuevo->puntaje ){ //se busca el puntaje que sea menor o igual
				nuevo->siguiente = aux;
				nuevo->anterior = auxAnt;
				auxAnt->siguiente = nuevo;
				aux->anterior = nuevo;
				return primero;
			}
			else{
				auxAnt = aux;
				aux = aux->siguiente; //se avanzan auxiliares
			}
		}
		// caso que llega al final de la lista
		nuevo->siguiente = aux; 
		auxAnt->siguiente = nuevo;
		nuevo->anterior = auxAnt;
		return primero;
	}

}

//Entrada: numero entero que corresponde al codigo del artista
//Salida: String o cadena de caracteres que correspondera al nombre del artista
//Descrip: Busca el nombre del artista en el archivo "artistas.in" mediante el codigo
// T(n) = 4c + n(6c)   O(n)
char * buscadorArtista(int codArtista){
	FILE * archivo = fopen("artistas.in","r"); //se abre el archivo para leer
	if(archivo == NULL)
		printf("ERROR DE ARCHIVO\n");
	else{

		int cantidadArtistas,codigo;
		char * nombreArtista = malloc(sizeof(char)*30);//se reserva memoria para la cadena de caracteres

		fscanf(archivo,"%d",&cantidadArtistas); //se leer la cantidad de artistas
		for (int i = 0; i < cantidadArtistas; ++i)
		{
			fscanf(archivo,"%d",&codigo);
			if(codArtista == codigo){//si el codigo de artista es igual al codigo se retorna
				fscanf(archivo,"%s",nombreArtista);
				fclose(archivo);
				return nombreArtista;
			}
			fscanf(archivo,"%s",nombreArtista);// se avanza en el archivo
		}
	}
	fclose(archivo);
}

//Entrada: numero entero que corresponde al codigo del genero
//Salida: String o cadena de caracteres que correspondera al nombre del genero
//Descrip: Busca el nombre del genero en el archivo "genero.in" mediante el codigo de este
// T(n) = 4c + n(6c)   O(n)
char * buscadorGenero(int codGenero){
	FILE * archivo = fopen("generos.in","r");// se abre el archivo en modo lectura


		int cantidadGeneros,codigo;
		char * nombreGenero = malloc(sizeof(char)*30); //Se reserva memoria para la cadena de caracteres

		fscanf(archivo,"%d",&cantidadGeneros);// se lee la cantidad de generos
		for (int i = 0; i < cantidadGeneros; ++i)
		{
			fscanf(archivo,"%d",&codigo);
			if(codGenero == codigo){// si el codigo es igual al codigo del archivo se lee y retorna el nombre
				fscanf(archivo,"%s",nombreGenero);
				fclose(archivo);
				return nombreGenero;
			}
			fscanf(archivo,"%s",nombreGenero);// se avanza en el archivo
	}
	
	fclose(archivo);
}

//Entrada:puntero a nodo cancion que corresponde a la lista
//Descrip: Libera la lista de entrada
// T(n) =  6nc   O(n)
void liberar(nodo * primero){
	while(primero != NULL){
		nodo *aux = primero;
		free(primero->nombreArtista);
		free(primero->nombreCancion);
		free(primero->nombreGenero);
		primero = primero->siguiente;
		free(aux);
	}
}

//Entrada: cadena de caracteres que corresponde al nombre de la cancion,nombre del genero,nombre del artista
//entero minutos, segundos, puntaje, codigo de artista y codigo de genero
//Salida: Puntero a nodo cancion, que correspondera a una nueva cancion
//Descrip: Crea cancion mediante argumentos dados
// O(1)
nodo * crearNodo(char * nombre,char * nombreGenero,char * nombreArtista,int min,int seg,int puntaje,int codArtista,int codGenero){
	nodo * nuevoNodo = (nodo *)malloc(sizeof(nodo));// se reserva memoria para crear nodo
	strcpy(nuevoNodo->nombreCancion,nombre);// Se copia las cadenas de caracteres
	strcpy(nuevoNodo->nombreArtista,nombreArtista);
	strcpy(nuevoNodo->nombreGenero,nombreGenero);
	nuevoNodo->minutos = min; // se agregan los minutos
	nuevoNodo->segundos = seg; // Se agregan los segundos
	nuevoNodo->puntaje = puntaje; //Se agrega el puntaje
	nuevoNodo->artista = codArtista; //Se agrega el codigo de artista
	nuevoNodo->genero = codGenero; // se agrega codigo de genero
	return nuevoNodo; 
}

//Entrada:puntero a nodo cancion que corresponde a la lista
//Salida: Puntero a nodo cancion que corresponde a lista
//Descrip: Se obtienen las canciones mediante el archivo "canciones.in" y se agregan a una lista de forma ordenada
// T(n) = 5c + n(3c + 2n)=  5c + 3nc + 2n^2   O(n^2)
nodo * obtenerCanciones(nodo * canciones){
	FILE *archivo = fopen("canciones.in","r");//se abre el archivo en modo lectura
	if (archivo == NULL)
		printf("ERROR DE ARCHIVO\n");
	else{

		int cantidadCanciones,min,seg,puntaje,codArtista,codGenero;
		char *nombreCancion = malloc(sizeof(char)*30),*nombreArtista,*nombreGenero,dosPuntos;

		fscanf(archivo,"%d",&cantidadCanciones);//se lee la cantidad de canciones
		for (int i = 0; i < cantidadCanciones; ++i)
		{
			fscanf(archivo,"%s %d %c %d %d %d %d",nombreCancion,&min,&dosPuntos,&seg,&codArtista,&codGenero,&puntaje);// se lee una linea del archivo
			nombreArtista = buscadorArtista(codArtista);// Se busca el nombre del artista en base al codigo
			nombreGenero = buscadorGenero(codGenero); //Se busca el nombre del genero en base al codigo
			nodo * cancion = crearNodo(nombreCancion,nombreGenero,nombreArtista,min,seg,puntaje,codArtista,codGenero); //se crea nodo cancion
			canciones = insertarOrdenado(canciones,cancion);// se inserta en lista de forma ordenada
		}	
	
	}
	fclose(archivo);
	return canciones;	
}


//Entrada:puntero a nodo cancion que corresponde a la lista y puntero a nodo cancion
//Salida: Puntero a nodo cancion que corresponde a lista
//Descrip: inserta una cancion en la cabeza de una lista
// O(1)
nodo * insertar(nodo * primero,nodo * nuevo){
	if(primero == NULL){//caso que la lista sea vacia
		nuevo->siguiente = NULL;
		nuevo->anterior = NULL;
		primero = nuevo;
		return primero;
	}//caso general
	nuevo->siguiente = primero;//se enlista
	nuevo->anterior = NULL;
	primero->anterior = nuevo;
	primero = nuevo;
	return primero;
}

//Entrada: Cadena de caracteres
//Salida: Valor, un numero entero
//Descrip: Se le da un valor a la primera letra del nombre
// T(n) = c + 26c   O(1)
int valorLetra(char * nombreArtista){
	char abecedario[] = "abcdefghijkmnlopqrstuwxyz"; //La lista base de letras
	for (int i = 0; i < 25; ++i)
	{
		if(abecedario[i] == nombreArtista[0]){ //si se encuentra se la letra en la lista se retorna su valor mas un 1
			return i+1;
		}
	}
}


//Entrada:puntero a nodo cancion que corresponde a la lista
//Salida: Puntero a nodo cancion que corresponde a lista
//Descrip: Ordena una lista en base a su nombre
// T(n) = 3c + n(8c + n(4c))= 3c + 8nc + 4n^2    O(n^2)
nodo * ordenarNombre(nodo * primero){
	nodo * cancionesNuevas = NULL; //nueva lista donde se traspasaran los nodos
	if(primero == NULL){ //caso que no existan nodos
		return primero;
	}
	nodo * menor,*aux;
	while(primero != NULL){ //O(n)
		menor = primero; // Cancion a comparar
		aux = primero->siguiente; //auxiliar que recorrera la lista
		while(aux != NULL){ // O(n)
			// Si el puntaje es igual si compara el valor de cada letra y si cumple se apunta al nuevo menor
			if(menor->puntaje == aux->puntaje && valorLetra(menor->nombreArtista) <= valorLetra(aux->nombreArtista)){ //O(n)
				menor = aux;
			}
			aux = aux->siguiente;
		}
		///desenlistar la cancion a insertar en la nueva lista
		nodo * ant = menor->anterior;
		nodo * des = menor->siguiente;
		if(ant == NULL && des == NULL){
			primero = NULL;
		}
		else if(ant == NULL){
			des->anterior = NULL;
			primero = primero->siguiente;
		}
		else if(des == NULL){
			ant->siguiente = NULL;
		}
		else{
			ant->siguiente = des;
			des->anterior = ant;
		} 
		// fin de desenlistar
		menor->siguiente = NULL;
		menor->anterior = NULL; 
		cancionesNuevas = insertar(cancionesNuevas,menor); //se inserta la cancion en la nueva lista
	}
	return cancionesNuevas; // se retorna la nueva lista
}

//Entrada:puntero a nodo cancion que corresponde a la lista
//Salida: Puntero a nodo cancion que corresponde a lista
//Descrip: Ordena una lista en base a su duracion
// T(n) = 3c + n(8c + n(4c))= 3c + 8nc + 4n^2    O(n^2)
nodo * ordenarTiempo(nodo * primero){
	if(primero == NULL){ //caso que sea vacia la lista
		return primero;
	}
	nodo * canciones = NULL; //Nueva lista 

	while(primero != NULL){
		nodo * mayor = primero; // Se apunta la cabeza de la lista, la cual sera comparada
		nodo * aux = primero->siguiente; //auxiliar que recorrera la lista
		while(aux != NULL){
			//se comprueba si el puntaje y el nombre es igual, si es asi si comparan las duraciones y se apunta al mayor
			if(mayor->puntaje == aux->puntaje && valorLetra(mayor->nombreArtista) == valorLetra(aux->nombreArtista) && ((mayor->minutos*60)+mayor->segundos) < ((aux->minutos*60)+aux->segundos)){
				mayor = aux;
			}
			aux = aux->siguiente;//se avanza el aux
		}
		//desenlistar la cancion a enlistar en la nueva lista
		nodo * ant = mayor->anterior;
		nodo * des = mayor->siguiente;
		if(ant == NULL && des == NULL){ 
			primero = NULL;
		}
		else if(ant == NULL){
			des->anterior = NULL;
			primero = primero->siguiente;
		}
		else if(des == NULL){
			ant->siguiente = NULL;
		}
		else{
			ant->siguiente = des;
			des->anterior = ant;
		}
		//
		mayor->siguiente = NULL;
		mayor->anterior = NULL;
		canciones = insertar(canciones,mayor); //Se inserta en la nueva lista
	}
	return canciones;

}

//Entrada:puntero a nodo cancion que corresponde a la lista
//Descrip: Agrega las canciones a archivo de salida "salida.out"
// T(n) = 3c + 2nc    O(n)
void agregarArchivo(nodo * canciones){
	if(canciones != NULL){
		FILE * archivo = fopen("salida.out","w"); //se abre el archivo en modo escritura
		if(archivo == NULL){
			printf("ERROR AL ABRIR EL ARCHIVO\n");
		}
		else{
			nodo * aux = canciones; //aux que recorrera la lista
			while(aux != NULL){
				fprintf(archivo,"%d;%s;%d:%d;%s;%s\n",aux->puntaje,aux->nombreCancion,aux->minutos,aux->segundos,aux->nombreArtista,aux->nombreGenero); //se escribira una linea
				aux = aux->siguiente; // se avanzara a la siguiente cancion
			}
			fclose(archivo);
		}
	}
}


int main(int argc, char const *argv[])
{
	

	nodo * canciones = NULL; //Lista de canciones
	canciones = obtenerCanciones(canciones); //Se obtienen las canciones y se insertan de forma ordenada por puntaje
	canciones = ordenarNombre(canciones); // Se ordenan por nombre
	canciones = ordenarTiempo(canciones); // se ordenan por tiempo de duracion
	agregarArchivo(canciones); //Se agrega a archivo de salida
	//insertar
	playlist(canciones); // Se crea la playlist
	liberar(canciones); // Se libera la lista 
	printf("ACCION REALIZADA CON EXITO\n");

	return 0;
}