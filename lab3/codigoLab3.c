/*LABORATORIO 3
Nombre: Sebastian cabezas
RUT: 20.453.460-8
Seccion: B-2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodo nodo;
typedef struct grafo grafo;
typedef struct nodoVertice nodoVertice;
typedef struct nodoNumero nodoNumero;

//Representacion de nodo en el arreglo
struct nodoVertice
{
	char nombre[20];
	nodo * siguiente;
	int gasolineria;
};

//Representacion de nodo detro de lista adyacencia
struct nodo
{
	char nombrePlaneta[20];
	int costo;
	int costoGasolina;
	nodo * siguiente;
};

//Representacion del grafo
struct grafo
{
	int vertices;
	nodoVertice * adyacencia;
	int gasolina;
};

//Nodo lista camino minimo
struct nodoNumero
{
	int dato;
	nodoNumero * siguiente;
};

//O(1)
//Entrada: numero que contendra el nodo
//Salida: puntero a nodoNumero
//Descrip: Crea un nodo para la lista de camino minimo
nodoNumero * crearNodoNumero(int dato){
	nodoNumero * nuevo = (nodoNumero *)malloc(sizeof(nodoNumero));
	nuevo->dato = dato;
	nuevo->siguiente = NULL;
	return nuevo;
}

//O(1)
//Entrada: nombre del planeta, costo de distancia y costo de gasolina de la arista
//Salida: nodo con toda la informacion de entrada
//Descrip: Crea un nodo para la la lista de adyacencia del grafo
nodo * crearNodo(char * nombre, int costo, int costoGasolina){
	nodo * nuevoNodo = malloc(sizeof(nodo));
	strcpy(nuevoNodo->nombrePlaneta,nombre);
	nuevoNodo->costo = costo;
	nuevoNodo->costoGasolina = costoGasolina;
	nuevoNodo->siguiente = NULL;
	return nuevoNodo;
}
//O(n)
//Entrada: puntero a nodo al primero de la lista y nodo a insertar
//Salida: puntero a nodo que contendra la lista modificada
//Descrip: Inserta un nodo al final de la lista
nodo * insertar(nodo * primero,nodo * planeta){
	if(primero == NULL){//Caso que no haya nodo en el primero
		planeta->siguiente = NULL;
		return planeta;
	}
	if(primero->siguiente == NULL){ // Caso que hay un nodo
		primero->siguiente = planeta;
		planeta->siguiente = NULL;
		return primero;
	}
	nodo * auxAnt = primero;
	nodo * aux = primero->siguiente;
	while(aux != NULL){ // se recorre hasta el final
		auxAnt = aux;
		aux = aux->siguiente;
	}
	/// Y se agrega
	auxAnt->siguiente = planeta;
	planeta->siguiente = NULL;
	return primero;

}

////O(1)
//Entrada: puntero a nodo al primero de la lista y nodo a insertar
//Salida: puntero a nodo que contendra la lista modificada
//Descrip: Inserta un nodo al principio de la lista
nodoNumero * insertarPrincipio(nodoNumero * primero, nodoNumero * nuevo){
	if(primero == NULL){ //Caso que no hay nodos
		nuevo->siguiente = NULL;
		return nuevo;
	}
	else{ // se enlaza al primero y se apunta al nuevo primero
		nuevo->siguiente = primero;
		primero = nuevo;
		return primero;
	}
}

//19c + n(3c +n) + n(2c + 2n)
//19c + 5nc + 3n^2
//Entrada: nombre del archivo a leer
//Salida: puntero a grafo que contedra toda la informacion(N°vertices,lista de adyacencia,etc)
//Descrip: Crear grafo y completarlo mediante un archivo
grafo * crearGrafo(char * nombreArchivo){
	FILE * archivo;
	archivo = fopen(nombreArchivo,"r");//Abrimos archivo a leer

	grafo * grafoNuevo = (grafo *)malloc(sizeof(grafo));

	int numeroVertices,costo,costoGasolina;
	char nombreOrigen[20],nombrePlaneta[20],primerNombreOrigen[20];

	fscanf(archivo,"%d",&numeroVertices);
	grafoNuevo->vertices = numeroVertices;
	grafoNuevo->gasolina = 0;
	grafoNuevo->adyacencia = (nodoVertice *)malloc(sizeof(nodoVertice)*numeroVertices);

	if(numeroVertices > 0 && fscanf(archivo,"%s",primerNombreOrigen) !=EOF){
		
		int i = 0;
		strcpy(grafoNuevo->adyacencia[i].nombre,primerNombreOrigen);
		grafoNuevo->adyacencia[i].gasolineria = 0;
		fscanf(archivo," %s %d %d ",nombrePlaneta,&costo,&costoGasolina);

		grafoNuevo->adyacencia[i].siguiente = crearNodo(nombrePlaneta,costo,costoGasolina);
		while(i < numeroVertices && fscanf(archivo,"%s",nombreOrigen) !=EOF){
			if(strcmp(nombreOrigen,primerNombreOrigen) == 0){//Sigue con el mismo planeta de "origen"
				fscanf(archivo," %s %d %d ",nombrePlaneta,&costo,&costoGasolina); //Se agrega un nodo a la LISTA de adyacencia
				nodo * planetaNuevo = crearNodo(nombrePlaneta,costo,costoGasolina);
				grafoNuevo->adyacencia[i].siguiente = insertar(grafoNuevo->adyacencia[i].siguiente,planetaNuevo);//O(n)
			}
			else{
				//Se agrega un nuevo nodo al ARREGLO 
				i++;
				strcpy(primerNombreOrigen,nombreOrigen);
				strcpy(grafoNuevo->adyacencia[i].nombre,nombreOrigen);
				fscanf(archivo," %s %d %d ",nombrePlaneta,&costo,&costoGasolina);
				//Se agrega un nuevo nodo a la nueva lista de planetas
				grafoNuevo->adyacencia[i].siguiente = crearNodo(nombrePlaneta,costo,costoGasolina);
			}
		}
		for (int i = 0; i < numeroVertices; ++i)
		{
			printf("%s->",grafoNuevo->adyacencia[i].nombre);
			nodo * aux = grafoNuevo->adyacencia[i].siguiente;
			while(aux != NULL){
				printf("%s->", aux->nombrePlaneta );
				aux = aux->siguiente;
			}
			printf("\n");
		}
		fclose(archivo);
		return grafoNuevo;
	}

}
//6c + n(2nc)
//6c + 2n^2c
//Entrada: puntero a grafo creado y nombre del archivo a leer
//Salida: puntero a grafo, el cual sera grafo modificado
//Descrip: Identificar las gasolineras modificando el grafo
grafo * modificarGrafo(grafo * grafito, char * nombreArchivo){
	FILE * archivo;
	archivo = fopen(nombreArchivo,"r");//Abrir el archivo a leer
	if (archivo == NULL)
	{
		printf("NO SE A PODIDO ABRIR EL ARCHIVO\n");
		return grafito;
	}
	else{
		int gasolinaTotal;
		char nombreGasolina[20];
		fscanf(archivo,"%d",&gasolinaTotal);
		grafito->gasolina = gasolinaTotal; // Se asigna la gasolina inicial
		while(fscanf(archivo,"%s",nombreGasolina) != EOF){
			//Se busca el nombre del planeta 
			for (int i = 0; i < grafito->vertices; ++i)
			{
				if(strcmp(nombreGasolina,grafito->adyacencia[i].nombre) == 0){// Si es igual se marca el vertice
					grafito->adyacencia[i].gasolineria = 1;
				}
			}
		}

	}
	fclose(archivo);
	return grafito;
}

//O(n)
//Entrada: puntero a arreglo de visitados y la cantidad de vertices del grafo
//Salida: numero que verificara la accion 0 o 1
//Descrip: Verifica que todos los nodos esten visitados
int TodoVisitado(int * visitados, int vertices){
	for (int i = 0; i < vertices; ++i)
	{
		if(visitados[i] == 0){ // Si no a sido visitado se retorna un 0
			return 0;
		}
	}
	return 1;
}

//O(n)
//Entrada: arreglo de distancias, arreglo de visitados y cantidad de vertices del grafo
//Salida: index del vertice con menor distancia
//Descrip: Retorna el nodo con menor distancia y no haya sido visitado
int menorArreglo(int * distancia,int * visitados, int vertices){
	int menor = 0;
	int index = 0;
	int i = 0;
	int salida = 0;
	//Se busca el menor y que sea mayor a 0
	//Caso que no encuentre solo retornara el 0 por default
	while(salida == 0 && i < vertices){
		if(visitados[i] == 0 && distancia[i] > 0){
			menor = distancia[i];
			index = i;
			salida = 1;
		}
		i++;
	}
	//Buscara el menor desde lo encontrado anteriormente
	for (int k = i; k < vertices; ++k)
	{
		if(visitados[k] == 0 && menor > distancia[k] && distancia[k] > 0){
			menor = distancia[k];
			index = k;
		}
	}
	//Se busca dos veces debido a que siempre eligiria el 0 como menor y no funciona
	return index;
}

//O(n)
//Entrada: Lista de adyacencia, nombre buscado y numero de vetices
//Salida: index del nodo buscado
//Descrip: Busca el index de un cierto nodo con un nombre en especifico
int buscarIndex(nodoVertice * grafoAdyacente, char * nombre, int vertices){
	int i;
	for ( i = 0; i < vertices; ++i)
	{
		if(strcmp(grafoAdyacente[i].nombre,nombre) == 0){
			return i;
		}
	}
	return i;
}


//(n^2)
//Entrada: puntero a la lista de adyacencia, index del planeta origen y la cantidad de vertices
//Salida: Index de la gasolinera adyacente a un planeta
//Descrip: Buscar el index de la gasolinera adyacente a un planeta
int indexGasolina(nodoVertice * listaVertices, int indexOrigen, int vertices){
	nodo * listaPlanetas = listaVertices[indexOrigen].siguiente; //Obtenemos lista de planetas
	while(listaPlanetas != NULL){
		for (int i = 0; i < vertices; ++i)
		{
			//Se busca si en la lista de planetas coincide con alguna gasolinera en la lista de vertices(ARREGLO)
			if(strcmp(listaVertices[i].nombre,listaPlanetas->nombrePlaneta) == 0 && listaVertices[i].gasolineria == 1){

				return i;
			}
		}
		listaPlanetas = listaPlanetas->siguiente;
	}
	return 0;

}
//O(n)
//Entrada: puntero a lista de planetas de un vertice y nombre a buscar
//Salida: el costo de gasolina asociado a la arista 
//Descrip: Busca el costo de gasolina de una arista segun el nombre
int costo(nodo * listaPlanetas, char * nombreBuscar ){
	nodo * lista = listaPlanetas;
	while(lista != NULL){
		if(strcmp(lista->nombrePlaneta,nombreBuscar) == 0){//Si es el nodo buscado se retorna el costo
			return lista->costoGasolina;
		}
		lista = lista->siguiente;
	}
	return 0;
}
//O(n)
//Entrada: puntero a lista de planetas de un vertice y nombre a buscar
//Salida: el costo distancia asociado a la arista 
//Descrip: Busca el costo distancia de una arista segun el nombre
int costoSinGasolina(nodo * listaPlanetas, char * nombreBuscar ){
	nodo * lista = listaPlanetas;
	while(lista != NULL){
		if(strcmp(lista->nombrePlaneta,nombreBuscar) == 0){
			return lista->costo;
		}
		lista = lista->siguiente;
	}
	return 0;
}
//O(n)
//Entrada: puntero a arreglo de vertices, el index del planeta origen y nombre a buscar
//Salida: el costo de gasolina asociado a la arista
//Descrip: Busca el costo de gasolina de una arista segun el nombre y un index de origen
int costoGasolina(nodoVertice * lista, int index, int indexGasolina){
	nodo * listaPlanetas = lista[index].siguiente;
	while(listaPlanetas != NULL){
		if(strcmp(listaPlanetas->nombrePlaneta,lista[indexGasolina].nombre) == 0){
			return listaPlanetas->costoGasolina;
		}
		listaPlanetas = listaPlanetas->siguiente;
	}
	return 0;
}
//c + n(2c + n^2 + n +10c)
//c + 12nc + n^3 + n^2 
//Entrada: Puntero a un grafo armado, puntero a nodo con el camino minimo
//Salida: Camino minimo modificado si fue necesario
//Descrip: Busca y modifica si es necesario por la restriccion de gasolina
nodoNumero * verificarGasolina(grafo * grafito, nodoNumero * primero){
	nodoNumero * aux = primero;
	while(aux != NULL){//Recorremos el camino
		if(aux->siguiente != NULL){
			//Se obtiene el costo de gasolina
			int costoRecorrido = costo(grafito->adyacencia[aux->dato].siguiente,grafito->adyacencia[aux->siguiente->dato].nombre);
			if((grafito->gasolina - costoRecorrido) < 0){///Si el costo de la gasolina es negativo
				// Se calcula en costo gasolina
				int index = indexGasolina(grafito->adyacencia,aux->dato, grafito->vertices);
				costoRecorrido = costoGasolina(grafito->adyacencia,aux->dato,index);
				grafito->gasolina = grafito->gasolina - costoRecorrido; //Se resta gasolina
				//Se agrega la gasolinera y planeta nuevamente para volver al camino minimo
				nodoNumero * gasolineria = crearNodoNumero(index);
				gasolineria->siguiente = aux->siguiente;
				aux->siguiente = gasolineria;
				nodoNumero * planeta = crearNodoNumero(aux->dato);
				planeta->siguiente = aux->siguiente->siguiente;
				aux->siguiente->siguiente = planeta;
				//Se recargar la gasolina
				grafito->gasolina = 10;
			}
			else{
				grafito->gasolina = grafito->gasolina - costoRecorrido;
			}
			
		}
		aux = aux->siguiente;
	}
	return primero;
}
//4c + 2nc + nc + n(n +2c + n(4c +n)+ 2nc +4c) 
// 4c + 9nc + 7n^2 + n^3
//Entrada: puntero a grafo que contendra la lista de adyacencia y numero vertices
//Salida: lista enlazada con el camino minimo
//Descrip: Busca el camino minimo entre dos entre dos puntos
nodoNumero * caminoCorto(grafo * grafoAdy){

	//Arreglos que serviran como trazas de el algoritmo
	int * visitados = (int *)malloc(sizeof(int)*grafoAdy->vertices);
	int * distancia = (int *)malloc(sizeof(int)*grafoAdy->vertices);
	int * origen = (int *)malloc(sizeof(int)*grafoAdy->vertices);

	//Se rellenan los arreglos
	for (int i = 0; i < grafoAdy->vertices; ++i)
	{
		visitados[i] = 0;
		distancia[i] = 0;
	}
	for (int i = 0; i < grafoAdy->vertices; ++i)
	{
		origen[i] = -1;
	}

	while(TodoVisitado(visitados,grafoAdy->vertices) == 0){//verificar que todos esten visitados
		//Nodo a impeccionar
		int menor = menorArreglo(distancia,visitados,grafoAdy->vertices);//Que sea menor y no este visitado
		nodo * aux = grafoAdy->adyacencia[menor].siguiente; //Rescatamos la lista de planetas adyacentes
		visitados[menor] = 1;//Marcamos como visitado
		while(aux != NULL){
			//Revisamos cada planeta de la lista
			char nombreInter[20];
			strcpy(nombreInter,aux->nombrePlaneta);//Recuperamos nombre
			int nodoInter = buscarIndex(grafoAdy->adyacencia,nombreInter,grafoAdy->vertices);//Buscamos el index del nombre O(n)
			//Si el vertice no a sido visitado y la distancia es menor
			if(visitados[nodoInter] == 0 && distancia[nodoInter] == 0){
				origen[nodoInter] = menor; //Le damos el origen 
				distancia[nodoInter] = distancia[menor] + aux->costo;//Actualizamos costo
			}
			else if(visitados[nodoInter] == 0 && distancia[menor]+aux->costo < distancia[nodoInter]){//Ver que la distancia sea minima pero no 0
				origen[nodoInter] = menor; //Le damos el origen 
				distancia[nodoInter] = distancia[menor] + aux->costo;//Actualizamos costo
			}
			aux = aux->siguiente;
		}	
	}
	//Agregamos de forma ordenada a la lista
	//Desde el ultimo al primero siguiendo el camino en reversa
	nodoNumero * primero = NULL;
	int ultimoIndex = grafoAdy->vertices-1;
	while(origen[ultimoIndex] != -1 ){
		primero = insertarPrincipio(primero,crearNodoNumero(ultimoIndex));
		ultimoIndex = origen[ultimoIndex];
	}
	//Se inserta el ultimo
	primero = insertarPrincipio(primero,crearNodoNumero(ultimoIndex));
	free(origen);
	free(distancia);
	free(visitados);
	return primero;
}
//c + n(c + n) + n(2c)
//c + 3nc + n^2
//Entrada: puntero a grafo y la lista del camino minimo
//Descrip: Escribir en el archivo de salida
void agregarArchivo(grafo * grafoAdy, nodoNumero * primero){
	nodoNumero * aux = primero;
	int costoTotal = 0;
	//Calcular costo total del camino
	while(aux != NULL){
		if(aux->siguiente != NULL){
			costoTotal = costoTotal + costoSinGasolina(grafoAdy->adyacencia[aux->dato].siguiente,grafoAdy->adyacencia[aux->siguiente->dato].nombre);
		}
		aux = aux->siguiente;
	}
	FILE * archivo;
	archivo = fopen("ruta.out","w");//Abrir el archivo
	fprintf(archivo, "%d\n",costoTotal);//Escribir el costo
	aux = primero;
	while(aux->siguiente != NULL){
		fprintf(archivo, "%s->",grafoAdy->adyacencia[aux->dato].nombre);//escribir cada paso del camino
		aux = aux->siguiente;
	}
	fprintf(archivo, "%s\n",grafoAdy->adyacencia[aux->dato].nombre );//paso final
	fclose(archivo);
}

//FUNCION MAIN 
int main(int argc, char *argv[])
{
	
	grafo * grafoAdy;
	//Creamos con informacion
	grafoAdy = crearGrafo(argv[1]);
	//marcamos gasolineras
	grafoAdy = modificarGrafo(grafoAdy,argv[2]);
	nodoNumero * primero;
	//Obtener camino minimo
	primero = caminoCorto(grafoAdy);
	//intervenir camino minimo por restriccion
	primero = verificarGasolina(grafoAdy,primero);
	//Escribir en archivo final
	agregarArchivo(grafoAdy,primero);
	return 0;
}