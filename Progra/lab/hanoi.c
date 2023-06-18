#include <stdio.h>
#include <stdlib.h>

// TORRES DE HANOI con BEE//
//Sebastian cabezas 
//seccion : L-3

//estado inicial A = [4,3,2,1]   estado final A = [0,0,0,0]
//               B = [0,0,0,0]                B = [4,3,2,1]
//               C = [0,0,0,0]                C = [0,0,0,0]

typedef struct shanoi{
int *A; // ejemplo: A= [3,2,1,0,0], n_A=3, size=5
int *B;
int *C;
int size; // tamaño maximo de los arreglos
int n_A,n_B,n_C; // cantidad de elementos en A,B, y C

int idEstado;    // numeracion de este estado
int estadoAnterior; // numeracion del estado de donde proviene
char * transicion; 
} hanoi;

int correlativo;


// Funciones de listas
hanoi crearEstado(int *A, int *B, int *C, int size, int anterior, char * t); 
hanoi * agregarEstado(hanoi * lista, int * elementos, hanoi estado);
hanoi * sacarElemento(hanoi * lista, int * elementos);
int estaEstado(hanoi * lista, int elementos, hanoi estado);
void mostrarSolucion(hanoi * lista, int ultimo);

// funciones chequear transicion 
int verificarAB(hanoi estado);
int verificarAC(hanoi estado);
int verificarBA(hanoi estado);
int verificarBC(hanoi estado);
int verificarCA(hanoi estado);
int verificarCB(hanoi estado);

// funciones de transicion
hanoi moverAB(hanoi estado);
hanoi moverAC(hanoi estado);
hanoi moverBA(hanoi estado);
hanoi moverBC(hanoi estado);
hanoi moverCA(hanoi estado);
hanoi moverCB(hanoi estado);
// funciones generales
int esFinal(hanoi b);
void imprimirEstado(hanoi b);

// implementaciones


///////////LISTAS//////////////////
hanoi crearEstado(int *A, int *B, int *C, int nA, int nB, int nC, int size,int anterior, char * t){
	hanoi nuevoEstado;
	nuevoEstado.A = A;
	nuevoEstado.B = B;
	nuevoEstado.C = C;
	nuevoEstado.n_A =nA;
	nuevoEstado.n_B =nB;
	nuevoEstado.n_C =nC;
	nuevoEstado.size = size;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

hanoi * agregarEstado(hanoi * lista, int * elementos, hanoi estado){  
	hanoi * nuevaLista = (hanoi *)malloc(sizeof(hanoi)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

hanoi * sacarElemento(hanoi * lista, int * elementos){
	hanoi * nuevaLista = (hanoi *)malloc(sizeof(hanoi)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

int estaEstado(hanoi * lista, int elementos, hanoi b){
	for (int i = 0; i < elementos; ++i)
	{
		for (int j = 0; j < b.nA ; ++j)
		{
			if(lista[i].A[j] != b.A[j]){
				return 0;
			}                                   //si es distinto == no esta me retornara un cero.
		}
	}
	for (int i = 0; i < elementos; ++i)
	{
		for (int j = 0; j < b.nB ; ++j)
		{
			if(lista[i].B[j] != b.B[j]){
				return 0;
			}                                   //si es distinto == no esta me retornara un cero.
		}
	}
	for (int i = 0; i < elementos; ++i)
	{
		for (int j = 0; j < b.nC ; ++j)
		{
			if(lista[i].A[j] != b.A[j]){
				return 0;
			}                                   //si es distinto == no esta me retornara un cero.
		}
	}

	return 1;
}
//////////CHEQUEAR TRANSICIONES///////////////////
int verificarAB(hanoi estado){

	if(estado.A[estado.nA-1] < estado.B[estado.nB-1] && estado.nA > 0){ // que en la torre b haya un numero mayor que a y hayan elementos en a
		return 1;
	}
	return 0;
}
int verificarAC(hanoi estado){

	if(estado.A[estado.nA-1] < estado.C[estado.nC-1] && estado.nA > 0){ // que en la torre c haya un numero mayor que a y hayan elementos en a
		return 1;
	}
	return 0;
}
int verificarBA(hanoi estado){

	if(estado.B[estado.nB-1] < estado.A[estado.nA-1] && estado.nB > 0){ 
		return 1;
	}
	return 0;
}
int verificarBC(hanoi estado){

	if(estado.B[estado.nB-1] < estado.C[estado.nC-1] && estado.nB > 0){ 
	}
	return 0;
}
int verificarCB(hanoi estado){

	if(estado.C[estado.nC-1] < estado.B[estado.nB-1] && estado.nC > 0){ 
		return 1;
	}
	return 0;
}
int verificarCA(hanoi estado){

	if(estado.C[estado.nC-1] < estado.A[estado.nA-1] && estado.nC > 0){ 
		return 1;
	}
	return 0;
}

///////////TRANSICIONES//////////////////
hanoi moverAB(hanoi estado){
	return crearEstado(nuevoA, nuevoB , estado.C, estado.idEstado, "AB");
}


//////////FUNCIONES GENERALES///////////////////
int esFinal(hanoi b){
	if()  ///si es estado final
		return 1;
	return 0;
}

void imprimirEstado(hanoi b){
	printf("Id:%d; A5:%d, A3:%d; T:%s, IdAnt:%d\n", );
}


void mostrarSolucion(hanoi * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].estadoAnterior;
	}
}


///////////PRINCIPAL//////////////////
int main(){
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	hanoi bActual, bSiguiente;
	hanoi * abiertos = (hanoi *)malloc(sizeof(hanoi)*canAbiertos);
	hanoi * cerrados = (hanoi *)malloc(sizeof(hanoi)*canCerrados);
	hanoi inicial = crearEstado(... colocar elementos iniciales);
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	while(canAbiertos > 0){
		bActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, bActual);
		if(esFinal(bActual) == 1){ // Aqui se encontro la solucion
			printf("Llegue\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{

			//LL5
			if(verificarAB(bActual) == 1){
				bSiguiente = AB(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}


		}

		printf("ABIERTOS:\n");
		for (int i = 0; i < canAbiertos; ++i)
		{
			imprimirEstado(abiertos[i]);
		}


		printf("\nCERRADOS:\n");
		for (int i = 0; i < canCerrados; ++i)
		{
			imprimirEstado(cerrados[i]);
		}
		printf("\n\n");
	}
	return 0;
}

