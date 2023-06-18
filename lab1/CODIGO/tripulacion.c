/*LABORATORIO 1 
Nombre: Sebastian cabezas
RUT: 20.453.460-8
Seccion: B-2 
*/

//importacion de librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"


typedef struct tripulante tripulante;
//Se define como se representara el tripulante
struct tripulante
{
	char *nombre;
	int peso;
	int calificacion;
};

tripulante *tripulantes;
int canSoluciones = 0;//cantidad de soluciones totales 

/////////Funciones

//Entrada: direccion de memoria de cantidad de tripulantes y peso
//Funcion: obtener los dos primeros datos del archivo
//T(n) = 3c   O(c)
void obtenerDatos(int *cantidadTripulantes,int *peso){
	FILE * archivo;
	archivo = fopen("tripulantes.in","r");//abrimos archivo en modo lectura
	if(archivo == NULL){
		printf("ERROR NO SE A PODIDO ABRIR EL ARCHIVO\n");
		return;
	}
	else{
	fscanf(archivo,"%d",cantidadTripulantes);//obtener los 2 primeros datos
	fscanf(archivo,"%d",peso);

	fflush(archivo);
	fclose(archivo);//cerramos archivo
}
}

//Entrada: arreglo de estructuras tripulante y cantidad de tripulantes.
//Funcion: obtener informacion de archivo "tripulantes.in"tal como 
//nombre, peso y calificacion de cada tripulante y agregarlos a la estructura.
//T(n) = 5c+n(7c)+2c   O(n)
void obtenerNombre(tripulante * tripulante, int cantidadTripulantes){
	FILE * archivo;
	archivo = fopen("tripulantes.in","r");//abrimos archivo en modo lectura
	if(archivo == NULL){
		printf("ERROR NO SE A PODIDO ABRIR EL ARCHIVO\n");
		return;
	}
	else{
	int peso,calificacion;
	char caracter[20];
	fscanf(archivo,"%d",&peso);
	fscanf(archivo,"%d",&calificacion);

	for (int i = 0; i < cantidadTripulantes; ++i)
	{
		fscanf(archivo,"%s %d %d ",caracter,&peso,&calificacion);//se obtienen los datos
		strcpy(tripulantes[i].nombre,caracter);//se copian los strings
		tripulantes[i].peso = peso;
		tripulantes[i].calificacion= calificacion;
	}
	fflush(archivo);
	fclose(archivo);
}
}

//////////////////////////////////////////////
//Entrada: arreglo solucion de enteros y cantidad de tripulantes.
//Salida: entero con la suma de los numeros
//Funcion: suma los numeros del arreglo.
//T(n) = 2c+n(3c)   O(n)
int sumaArreglo(int *arreglo, int cantidad){
	int suma = 0;	
	for (int i = 0; i < cantidad; ++i)
	{
		suma = suma + arreglo[i];
	}
	return suma;

}


//Entrada: arreglo de estructuras tripulante ,cantidad de tripulantes y arreglo solucion
//Funcion: agrega a un archivo ("tripulantesIntermedio.in") el arreglo solucion con su determinado peso total y calificacion total
//T(n) = 2c+n(3c)+n(c)+2c   O(n)
void agregarSolucion(tripulante *tripulantes,int cantidad,int *solucion){
	int calificacionTotal = 0,pesoTotal = 0;

	for (int i = 0; i < cantidad; ++i)
	{
		if(solucion[i] > 0){//sumamos el peso total y calificacion total SI el tripulante este estipulado en la solucion
			calificacionTotal = calificacionTotal + tripulantes[i].calificacion;//si calificacion es distinto de 0 sumamos a total
			pesoTotal = pesoTotal + tripulantes[i].peso;
		}
	}
	if(calificacionTotal > 0){//si existe al menos un tripulante
		FILE *archivo;
		archivo = fopen("tripulanteIntermedio.in","a");//abrimos archivo en modo agregar
		if(archivo == NULL){
			printf("ERROR AL ABRIR EL ARCHIVO\n");
			return;
		}
		else{
		for (int i = 0; i < cantidad; ++i)
		{
			fprintf(archivo, "%d ",solucion[i] );//agregamos lo que esta en el arreglo
		}
		fprintf(archivo, "%d %d \n", pesoTotal,calificacionTotal);//agregamos datos restantes
		
		fflush(archivo);
		fclose(archivo);//cerramos archivo
		canSoluciones++;//sumamos una solucion a la variable global
	}
	}
}


//Entrada: arreglo de estructuras tripulante, arreglo auxiliar, posicion, cantidad de tripulantes y peso maximo.
//Funcion: realiza todas las combinaciones de pesos de tripulantes.
//T(n) = n si n = 0
//      cn +T(n-1) C.O    O(n^2)
void filtroPeso(tripulante *tripulantes,int *arreglo,int j,int cantidad,int peso){
	for (int i = 0; i < 2; ++i)
		{
				
			if(i == 0){
				arreglo[j] = tripulantes[j].peso;//agregamos peso al arreglo
			}
			else{
				arreglo[j] = 0;//caso que ese tripulante no vaya
			}
			
			if(j == cantidad-1){//llego al ultimo tripulante
				if(sumaArreglo(arreglo,cantidad) <= peso){
				agregarSolucion(tripulantes,cantidad,arreglo);
						
				}
			} 
			else{
				filtroPeso(tripulantes,arreglo,j+1,cantidad,peso);
			}
		}	
}


//Funcion: borra el contenido del archivo.
// O(c)
void borrarContenidoIntermedio(){
	FILE *archivo;
	archivo = fopen("tripulanteIntermedio.in","w");
	if(archivo == NULL){
		printf("ERROR NO SE A PODIDO ABRIR EL ARCHIVO\n");
		return;
	}
	fclose(archivo);	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Entrada: arreglo bidimensional de soluciones, cantidad de tripulantes, cantidad de soluciones y arreglo auxiliar.
//Funcion: ordena las soluciones por calificacion con el algoritmo de seleccion.
//T(n) = 2c+n(2c + n(3c))+n(2c)+n(2c)+n(2c) = 2c + 3n^2 + 4nc   O(n^2)
void ordenamiento(int**soluciones,int cantidad,int canSoluciones,int *aux){
	int mayor,posicionMayor;
	for (int i = 0; i < canSoluciones; ++i)
	{
		mayor = soluciones[i][cantidad+1];//cantidad mas 1 porque ahi se encuentra la calificacion total
		posicionMayor = i;
		
		for (int j = i+1; j < canSoluciones; ++j)
		{
			if(mayor < soluciones[j][cantidad+1]){//se busca el mayor en el arreglo
				mayor = soluciones[j][cantidad+1];// se guarda el mayor
				posicionMayor = j;//se guarda la posicion del mayor
			}
		}
		
		
		
		for (int k = 0; k < cantidad+2; ++k)
		{
			aux[k] = soluciones[i][k];//copiamos en aux
		}
		for (int k = 0; k < cantidad+2; ++k)
		{
			soluciones[i][k] = soluciones[posicionMayor][k]; //reemplazamos las soluciones
		}
		for (int k = 0; k < cantidad+2; ++k)
		{
			soluciones[posicionMayor][k] = aux[k];//agregamos el aux a la solucion que se reemplazo
		}	
	}
}


//Entrada: arreglo bidimensional de soluciones, cantidad de soluciones y cantidad de tripulantes.
//Funcion: copia las soluciones de un archivo("tripulantesIntermedios.in") a un arreglo bidimensional.
////T(n) = n(n(2c))   O(n^2)
void copiarSoluciones(int **soluciones,int canSoluciones, int canTripulantes){
	if(canSoluciones > 0){
		FILE *archivo;
		archivo = fopen("tripulanteIntermedio.in","r");
		if(archivo == NULL){
		printf("ERROR NO SE A PODIDO ABRIR EL ARCHIVO\n");
		return;
		}
		else{
		for (int i = 0; i < canSoluciones; ++i)
		{
			
			for (int j = 0; j < canTripulantes+2; ++j)
			{
				fscanf(archivo,"%d",&soluciones[i][j]);//se obtiene el numero y se agrega a una posicion del arreglo
			}
		}
		fflush(archivo);
		fclose(archivo);//cerramos el archivo
	}
	}
}
//////////////////////////////////////////////////////////////////////

//Entrada: arreglo de estructuras tripulante,arreglo bidimensional de soluciones , cantidad de tripulantes y cantidad de soluciones.
//Funcion: agrega las soluciones al archivo "tripulantes.out"
//T(n) = n(n(2c)2c)+c   O(n^2)
void agregarOut(tripulante *tripulantes,int **soluciones, int cantidad,int canSoluciones){
	FILE *archivo;
	archivo = fopen("tripulantes.out","w");//abrimos el archivo en modo escritura
	if(archivo == NULL){
		printf("ERROR EL ARCHIVO NO SE A PODIDO ABRIR\n");
	}
	else{
	for (int i = 0; i < canSoluciones; ++i)
	{
		for (int j = 0; j < cantidad; ++j)
		{
			if(soluciones[i][j] > 0){//si el tripulante esta estipulado se coloca el nombre de este
				fprintf(archivo, "%s ",tripulantes[j].nombre);
			}
		}
		fprintf(archivo, "%d ",soluciones[i][cantidad]);//se agrega el peso total de esa solucion
		fprintf(archivo, "%d \n",soluciones[i][cantidad+1]);//se agrega el calificacion total de esa solucion
	}
	fflush(archivo);
	fclose(archivo);//cerramos el archivo
}
}

/////FUNCION PRINCIPAL

int main(int argc, char const *argv[])
{	

	//reservamos memoria para variables
	int *pesoMax =(int *)malloc(sizeof(int));
	int *cantidadTripulantes = (int *)malloc(sizeof(int));
	
	//obtenemos los primeros datos
	obtenerDatos(cantidadTripulantes,pesoMax);
	printf("%d %d \n",*cantidadTripulantes,*pesoMax );

	//reservamos memoria para el arreglo de tripulantes 
	tripulantes = (tripulante *)malloc(sizeof(tripulante)*(*cantidadTripulantes));
	for (int i = 0; i < *cantidadTripulantes; ++i)
	{
		tripulantes[i].nombre = (char *)malloc(sizeof(char)*20);//reservamos para nombre
	}
	
	obtenerNombre(tripulantes, *cantidadTripulantes);//obtenemos nombre,peso y calificacion de tripulantes


	for (int i = 0; i < *cantidadTripulantes; ++i)
	{
		printf("%s %d %d \n",tripulantes[i].nombre,tripulantes[i].peso,tripulantes[i].calificacion );
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////

	int *arregloSuma =(int *)malloc(sizeof(int)*(*cantidadTripulantes));//reservamos memoria para arreglo auxiliar
	borrarContenidoIntermedio();//borramos contenido del archivo
	
	filtroPeso(tripulantes,arregloSuma,0,*cantidadTripulantes,*pesoMax);//realiza el filtro por el peso maximo
	free(arregloSuma);//se libera memoria del aux.
	/////////////////////////////////////////////////////////////////////////////////////////////////
    
    //Reservamos memoria para el arreglo de soluciones
	int ** soluciones = (int **)malloc(sizeof(int*)*canSoluciones);
	for (int i = 0; i < canSoluciones; ++i)
	{
		soluciones[i] = (int *)malloc(sizeof(int)*(*cantidadTripulantes)+2);//+2 para el peso total y calificacion total
	}

	copiarSoluciones(soluciones,canSoluciones,*cantidadTripulantes);//copiamos soluciones de archivo
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	int *aux = (int*)malloc(sizeof(int)*(*cantidadTripulantes)+2);//reservamos memoria para arreglo auxiliar
	ordenamiento(soluciones,*cantidadTripulantes,canSoluciones,aux);//ordenamos soluciones
	free(aux);//liberamos memoria

	//////////////////////////////////////////////////////////////////////////////////////////
	agregarOut(tripulantes,soluciones,*cantidadTripulantes,canSoluciones);//copiamos soluciones finales a archivo

	printf("¡ACCION REALIZADA CON EXITO!\n");

    //Se realizan los free correspondientes
	free(pesoMax);
	free(cantidadTripulantes);
	for (int i = 0; i < *cantidadTripulantes; ++i)
	{
		free(tripulantes[i].nombre);
	}
	free(tripulantes);
	for (int i = 0; i < canSoluciones; ++i)
	{
		free(soluciones[i]);
	}
	free(soluciones);

	

	return 0;
}