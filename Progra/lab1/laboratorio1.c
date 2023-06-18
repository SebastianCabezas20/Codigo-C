#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////problemas matriz de contagiados///////////////////////////////////////////////////
//Sebastian Cabezas//seccion L-3//RUT 20.453.460-8////////////
////////////////Fecha creacion 28-08-2020///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//////MATRIZ//////////

int leerMatriz(int matriz[][20], int *filas, int *columnas, char*nombreArchivo);
void imprimirMatriz(int matriz[][20], int *filas, int *columnas);
/////////cola////////

typedef struct cola cola;

cola *crearCola();
int colaLlena(cola *a);
cola encolar(cola *a, int x);
int colaVacia(cola *a);
int desencolar(cola *a);

////////////////////////////
//Definimos la estructura de la cola
struct cola
{
	int primero; //primero de la cola
	int vacioultimo; // el lugar VACIO despues del ultimo
	int tamano; // en tamano de la cola
	int capacidad; // capacidad maxima de la cola
	int *arreglo; //arreglo de indices
};

/////////implemantacion de cola

//Salida: Retorna una estructura cola
//crea un cola nueva predeterminada
cola *crearCola(){
	cola *nuevaCola = malloc(sizeof(cola));
	nuevaCola->arreglo = malloc(sizeof(int)*100);
	nuevaCola->primero = 0;
	nuevaCola->vacioultimo = 0;
	nuevaCola->tamano = 0;
	nuevaCola->capacidad = 100;
}

//Entrada: estructura cola
//salida: retorna un 1 si esta llena o 0 si no.
//verifica si la cola esta llena.
int colaLlena(cola *a){
	return(a->capacidad == a->tamano); 
}

//Entrada: estructura de cola y numero que queremos encolar
//Salida: retorna el numero encolado en la cola
//encola en la ultima posicion de la cola
cola encolar(cola *a, int x){
	if(colaLlena(a)){       /////////duplicamos capacidad
		a->capacidad = 2*(a->capacidad);
		a->arreglo = realloc(a->arreglo,sizeof(int)*a->capacidad);
		memcpy(a->arreglo+a->tamano, a->arreglo, a->primero); 
		a->vacioultimo = a->primero+a->tamano;
	}
	a->arreglo[a->vacioultimo] = x;
	if(a->vacioultimo == a->capacidad){
		a->vacioultimo = 0;
	}
	else{
		a->vacioultimo = a->vacioultimo +1;
	}
	a->tamano = a->tamano +1;
}

//Entrada: estructura cola.
//salida: retorna un 1 si esta vacia y 0 si no.
//confirma si la cola esta vacia.
int colaVacia(cola *a){
	return(a->tamano ==0);
}

//Entrada: estructura de cola.
//Salida: retorna el numero desencolado.
//saca el primer elemento de la cola
int desencolar(cola *a){
	if(colaVacia(a))
		return -1; ///////no desencola.
	else{
		static int x;
		x = a->arreglo[a->primero];
		if(a->primero == a->capacidad){
			a->primero = 0;
		}
		else{
			a->primero = a->primero +1;
		}
		a->tamano=a->tamano-1;
		return x;
	}
}


////////IMPLEMENTACIONES MATRIZ

//Entrada: una matriz "vacia", dos numero que seran filas y columnas
//y un char que es el nombre del archivo
//Salida: Sale una matriz con sus respectivas filas y columnas
///Abrir y leer texto que contiene una matriz,
//esta matriz se "traspasa" a una matriz de arreglos
int leerMatriz(int matriz[][20], int *filas, int *columnas, char*nombreArchivo){
	FILE *pf;
	pf = fopen(nombreArchivo,"r");
	if(pf == NULL){
		return 0;
	}
	int filasA,columnasA;
	fscanf(pf,"%d",&filasA);
	fscanf(pf,"%d",&columnasA);
	
	for (int i = 0; i < filasA; i++)
	{
		for (int j = 0; j < columnasA; j++)
		{
		
			if(fscanf(pf,"%d",&matriz[i][j])==EOF){
				return 2;
			}
			
		}
	}
	

	for (int i = 0; i < filasA; ++i)
	{
		for (int j = 0; j < columnasA; ++j)
		{

			printf(" %d",matriz[i][j] );
		}
		printf("\n");
	}
	*filas = filasA,*columnas = columnasA;
	return 1;
	fclose(pf);
}

//Entrada: matriz con su fila y columnas
///imprime la matriz
void imprimirMatriz(int matriz[][20], int *filas, int *columnas){
	for (int i = 0; i < *filas; ++i)
	{
		for (int j = 0; j < *columnas; ++j)
		{
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}

////FUNCION PRINCIPAL Contagios


///llama a la funcion que lee el archivo
//luego detecta los sanos y contagiados
// finalmente comienza a contagiar cambiando la matriz
int funcionContagios()
{
	char nombreArchivo[50];
	int matriz[20][20];
	int *filas=malloc(sizeof(int)),*columnas = malloc(sizeof(int)) ;
	printf("ingrese nombre del archivo: ");
	scanf("%s",&nombreArchivo);
	printf("nombreArchivo : %s\n",nombreArchivo);
	int ver = leerMatriz(matriz,filas,columnas,nombreArchivo);
	if(ver == 0){
		printf("error de archivo\n\n");
		return 0;
	}
	if(ver == 2){
		printf("error del formato de la matriz\n\n");
		return 0;
	}
	/////////creo las colas a ocupar
	cola *colai = crearCola(),*colaj = crearCola();
	//////////////identificamos los CONTAGIADOS y cantidad de personas SANAS
	int sanas = 0;

	for (int i = 0; i < *filas; ++i)
	{
		for (int j = 0; j < *columnas; ++j)
		{
			if(matriz[i][j] == 1){
				sanas++;      ////identificamos sanas
			}
			if(matriz[i][j] == 2){// si en un punto hay infectado
				encolar(colai,i); //lo agregamos a la cola 
				encolar(colaj,j);
			}
		}
	}
	printf("sanas %d \n\n",sanas );//creamos colas auxiliares
	cola *colapuntosi = crearCola();
	cola *colapuntosj = crearCola();

	int puntoi,puntoj,t=0,verificar;
	while(!colaVacia(colai)){
		verificar = 0;
		while(!colaVacia(colai)){
			puntoi = desencolar(colai);
			puntoj = desencolar(colaj);
			//////////se compara cada punto i,j hacia cada lado
			////si encuentra lo convierte en un 2
			////los nuevos contagiados los agrega a la cola auxiliar
			if(matriz[puntoi+1][puntoj] == 1 && puntoi+1<*filas ){//se traslada hacia abajo
				matriz[puntoi+1][puntoj] = 2;
				encolar(colapuntosi, puntoi+1);
				encolar(colapuntosj, puntoj);
				sanas = sanas-1;
				verificar = 1;
			}
			if(matriz[puntoi-1][puntoj] == 1 && puntoi-1>=0){ //se traslada hacia arriba
				matriz[puntoi-1][puntoj] = 2;
				encolar(colapuntosi, puntoi-1);
				encolar(colapuntosj, puntoj);
				sanas = sanas-1;
				verificar = 1;
			}
			if(matriz[puntoi][puntoj+1] == 1 && puntoj+1 < *columnas){//se traslada hacia la derecha
				matriz[puntoi][puntoj+1] = 2;
				encolar(colapuntosi, puntoi);
				encolar(colapuntosj, puntoj+1);
				sanas = sanas-1;
				verificar = 1;
			}
			if(matriz[puntoi][puntoj-1] == 1 && puntoj-1>=0 ){// se traslada a la izquierda
				matriz[puntoi][puntoj-1] = 2;
				encolar(colapuntosi, puntoi);
				encolar(colapuntosj, puntoj-1);
				sanas = sanas-1;
				verificar = 1;
			}
			
		}
		int auxi=0, auxj = 0;
		while(!colaVacia(colapuntosi)){//los de la cola auxiliar los agregamos a la original
			auxi = desencolar(colapuntosi);
			auxj = desencolar(colapuntosj);
			encolar(colai,auxi);
			encolar(colaj,auxj);
		}
		if(verificar == 1){//si hubo modificacion sumamos t y imprimimos t y sanas
			t= t+1;
			imprimirMatriz(matriz,filas,columnas);
			printf("t = %d sanas = %d\n\n",t ,sanas);
		}
	}
	if(sanas != 0){
		printf("no se pudo contagiar a toda la matriz.\n");
		return 0;
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////Muestra los pasos de las torres de hanoi////////Fecha creacion 28-08-2020////////////////////////////////
//Sebastian Cabezas//seccion L-3//RUT 20.453.460-8////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////Definimos la estructura de pila
typedef struct pila pila;
struct pila
{
    int *arreglo;//contiene los numeros
    int maximo;//maximo de elemntos del arreglo
    int ultimo;// posicion del ultimo
    char nombre;//nombre de la pila
};

//////implementaciones
pila *crearpila();
int pilaVacia(pila *a);
int buscarPila(pila *a, int x);
void imprimir(pila *a);
/////////////Movimientos
int extraer(pila *a, int *x);
void insertar(pila *a, int x);
////Torre//////////////
void torre(int N, pila *pilaA, pila *pilaB, pila *pilaC);

///////////Pila

//Crea una pila nueva predeterminada
//Retorna una pila
pila *crearpila(){
    pila *pilaNueva = malloc(sizeof(pila));
    pilaNueva->arreglo = malloc(sizeof(int)*100);
    pilaNueva->maximo=100;
    pilaNueva->ultimo=-1;
    pilaNueva->nombre ='N';
    return pilaNueva; 
}

//Entrada: una estructura de pila
//salida: un entero que indica si esta vacia
//Indica si la pila esta vacia
int pilaVacia(pila *a){
    if(a->ultimo == -1)
        return 1;
    else
        return 0;
}

//Entrada: una estructura de pila y el numero a buscar
//Salida: retorna un entero que indica si esta el numero.
//busca un numero en la pila
int buscarPila(pila *a, int x){
    if(pilaVacia(a)==1)
        return 0;
    else{
        for (int i = 0; i <= a->maximo; ++i)
        {
            if(a->arreglo[i]== x)
                return 1;
        }
        return 0;
    }
}

//Entrada: estructura de pila
//imprime la pila completa mediante iteracion
void imprimir(pila *a){
    for (int i = 0; i <= a->ultimo; ++i)
    {
        printf("%d ",a->arreglo[i] );
    }
    printf("\n");
}
/////////////Movimientos

//Entrada: una estructura de pila y la direccion de memoria de un entero.
//Salida: deja el valor extraido en la memoria de x y retorna un entero si pudo o no extraer.
//extrae el primero de la pila, ingresando el valor en la memoria de x.
int extraer(pila *a, int *x){
    if(pilaVacia(a) == 1)
        return 0;
    *x = a->arreglo[a->ultimo];
    a->ultimo = a->ultimo -1;
    return 1;
}
//Entrada: una estructura de pila y un entero a insertar.
//inserta al principio de la pila.
void insertar(pila *a, int x){
    if(a->ultimo+1> a->maximo){
        a->maximo = 2*a->maximo;
        a->arreglo = realloc(a->arreglo,sizeof(int)*a->maximo);
        if(a->arreglo == NULL)
            printf("error\n");
    }
    a->ultimo = a->ultimo+1;
    a->arreglo[a->ultimo] = x;
}


////////////////////torre///////////////////

int disco;// disco el cual sera movido


//Entrada: 3 estructuras de pila y el numero de discos en la pilaA
//funcion que lleva los discos de la pila A a pila C mediante recursion
// Los primeros elementos de A a B
// despues de A a C
// finalmente de B a C
void torre(int N, pila *torreA, pila *torreB, pila *torreC){
    if (N <= 0){
        return;
    }
    // de A a B 
    torre(N-1, torreA, torreC, torreB);
    // de A a C
    extraer(torreA,&disco);
    insertar(torreC,disco);
    //para imprimir en orden detecto cual es A,B y C.
    printf("A: ");
    if (torreA->nombre == 'A')
    {
        imprimir(torreA);
    }
    else if(torreB->nombre == 'A'){
        imprimir(torreB);
    }
    else{
        imprimir(torreC);
    }
    printf("B: ");
    if (torreA->nombre == 'B')
    {
        imprimir(torreA);
    }
    else if(torreB->nombre == 'B'){
        imprimir(torreB);
    }
    else{
        imprimir(torreC);
    }
    printf("C: ");
    if (torreA->nombre == 'C')
    {
        imprimir(torreA);
    }
    else if(torreB->nombre == 'C'){
        imprimir(torreB);
    }
    else{
        imprimir(torreC);
    }
    printf("\n");
    // de B a C
    torre(N-1,torreB, torreA, torreC);
}


///FUNCION PRINCIPAL
//Crea las pilas y se les ingresan datos(discos y nombresa cada pila)
int torresHanoi()
{
    int numeroDiscos;
    printf("Numero de discos en la torre: ");
    scanf("%d",&numeroDiscos);
    pila *A,*B,*C;
    A=crearpila();B = crearpila(); C = crearpila();
    for (int i = 0; i < numeroDiscos; ++i)
    {
        insertar(A,numeroDiscos -i);
    }
    A->nombre = 'A';//identificamos cada pila
    B->nombre = 'B';
    C->nombre = 'C';
    printf("A: ");
    imprimir(A);
    printf("B: " );
    imprimir(B);
    printf("C: ");
    imprimir(C);
    printf("\n");

    torre(numeroDiscos,A,B,C);
    return 0;
}

////////////////////////////////////////////////////////////////
//////////Funcion principal/////////////////////////////////////
//funcion menu que permite ingresar a las torres y contagiados//
int main()
{
	int valido = 1;
	while(valido == 1){
		int opcion;
		printf("1 -Torres de hanoi  \n");
		printf("2 -Contagiados \n");
		printf("3 -salir\n");
		printf("Ingrese opcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
			torresHanoi();
			break;
			case 2:
			funcionContagios();
			break;
			case 3:
			printf("Fin programa\n");
			system("pause");
			valido = 0;
			break;
			default:
			printf("Opcion invalida\n\n");
		}
	}
	return 0;
}
