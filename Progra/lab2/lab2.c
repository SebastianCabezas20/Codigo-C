#include <stdio.h>
#include <stdlib.h>

//Sebastian cabezas
//Seccion L-3
//RUT 20.453.460-8
//Fecha creacion: 12-09-20 

//Misioneros y canibales//

//   [C | M | B ] 
//   [Canibales | Misioneros | bote] en lado A o B
//   Estado inicial = [0 | 0 | 0 ]
//   Estado Final = [3 | 3 | 1]

//Definimos la estructura a utilizar
typedef struct scmb{
int *lado;//  Arreglo que sera el lado  [Canibales | Misioneros | bote]
int idEstado;    // numeracion de este estado
int estadoAnterior; // numeracion del estado de donde proviene
char * transicion; 
} cmb;

int correlativo;


// Funciones de listas
cmb crearEstado(int*lado ,int anterior, char * t); 
cmb * agregarEstado(cmb * lista, int * elementos, cmb estado);
cmb * sacarElemento(cmb * lista, int * elementos);
int estaEstado(cmb * lista, int elementos, cmb estado);
void mostrarSolucion(cmb * lista, int ultimo);

// funciones chequear transicion 
int verificarPasarCanival(cmb estado);

// funciones de transicion
cmb moverAB(cmb estado);

// funciones generales
int esFinal(cmb b);
void imprimirEstado(cmb b);

// implementaciones


///////////LISTAS//////////////////
//Entrada: arreglo que indica el lado del rio, entero con el id del estado anterior
// y la transicion
//Salida : crea un estructura de cmb con los valores de entrada
//crea estado con nuevos valores
cmb crearEstado(int* lado, int anterior, char * t){
	cmb nuevoEstado;
	nuevoEstado.lado = lado; 
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

//Entrada: una lista de estructuras cmb, la cantidad de elementos y el estado a agregar
//Salida: lista de estructuras con el estado agregado
//agrega al final de la lista un estado
cmb * agregarEstado(cmb * lista, int * elementos, cmb estado){  
	cmb * nuevaLista = (cmb *)malloc(sizeof(cmb)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

//Entrada: una lista de estructuras cmb, la cantidad de elementos.
//Salida: lista de estructuras con el estado eliminado
//elimina el primer elementos de la lista
cmb * sacarElemento(cmb * lista, int * elementos){
	cmb * nuevaLista = (cmb *)malloc(sizeof(cmb)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

//Entrada: una lista de estructuras, los elementos que tiene y el estado a buscar
//Salida: retorna un entero verificando
//verifica si esta el estado en la lista
int estaEstado(cmb * lista, int elementos, cmb estado){
	for (int i = 0; i < elementos; ++i){
		if(lista[i].lado[0] == estado.lado[0] && lista[i].lado[1] == estado.lado[1] && lista[i].lado[2] == estado.lado[2])
			return 1;
	}
	return 0;
}
//////////CHEQUEAR TRANSICIONES///////////////////

//PARA TODAS LAS VERIFICACIONES:
//Entrada: estructura cmb
//salida: entero que verifica si se puede hacer la transicion
//verificar la transicion

int verificarPasarCanival(cmb estado){
	if(estado.lado[2] == 0 && estado.lado[0] < 3){//Bote esta en el lado A y hay menos de 3 Cles en B.
		if(estado.lado[1] == 0 || estado.lado[1] == 3)//Puede pasar un canival al lado B
			return 1; //Hay no hay misioneros en B o hay 3
		else
			return 0;
	}
	else if(estado.lado[2] == 1 && estado.lado[0] <= 3){// El bote esta en el lado B y hay maximo 3 Clse en B.
		if(estado.lado[1] == 0 || estado.lado[1] == 3)//Puede pasar un canival al lado B
			return 1;//Hay no hay misioneros en B o hay 3
		else
			return 0;
	}
	else
		return 0;
}

int verificarPasar2Canivales(cmb estado){
	if(estado.lado[2] == 0 && estado.lado[0] < 2){//Bote esta en el lado A y hay maximo un canival en B
		if(estado.lado[1] == 0 || estado.lado[1] == 3)//Puede pasar un canival al lado B
			return 1; //Hay no hay misioneros en B o hay 3
		else
			return 0;
	}
	else if(estado.lado[2] == 1 && estado.lado[0] >= 2 && estado.lado[0] <= 3){// El bote esta en el lado B y tiene que haber mas de 2 Cles. 
		if(estado.lado[1] == 0 || estado.lado[1] == 3)//Puede pasar un canival al lado B
			return 1;//Hay no hay misioneros en B o hay 3
		else
			return 0;
	}
	else
		return 0;
}

int verificarPasarMisionero(cmb estado){
	if(estado.lado[2] == 0 && estado.lado[0] > 0 && estado.lado[0] <= 3){//Bote esta en el lado A y por lo menos un canival
		if(estado.lado[1] == 2 && estado.lado[0] == 2 )//Si hay 2 canivales y dos misioneros
			return 1; //Se puede pasar
		else if(estado.lado[1]+1 == estado.lado[0])//si al pasar un misionero quedan iguales en lado B
			return 1;//se puede pasar
		else
			return 0;//no se puede
	}
	else if(estado.lado[2] == 1 && estado.lado[1] > estado.lado[0]){// El bote esta en el lado B y hay mas misioneros que Cles.
		return 1;
	}
	else//Esta la misma cantidad de canivales y misioneros
		return 0;
}

int verificarPasar2Misioneros(cmb estado){
	if(estado.lado[2] == 0 && estado.lado[0] < 3){//Bote esta en el lado A y hay maximo 2 canivales en B
		//existen dos casos posibles
		if(estado.lado[0] == 1 && estado.lado[1] == 1)//Puede pasar 2 misioneros al lado B
			return 1; //caso que haya un canival y un misionero en B
		else if (estado.lado[0] == 2  && estado.lado[1] == 0)//Hay dos canivales en B
			return 1;//Se puede ////cuando hay 2 
		else
			return 0;
	}

	else if(estado.lado[2] == 1 && estado.lado[0] <= 2){// El bote esta en el lado B y hay maximo dos canibales
		if(estado.lado[0] == 2 && estado.lado[1] == 2)//Puede pasar dos misioneros 
			return 1;//Hay dos misioneros y dos canibales en B
		else if(estado.lado[0] == 1  && estado.lado[1] == 3)// hay 3 misioneros y un canibal
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int verificarPasarUYU(cmb estado){
	if(estado.lado[2] == 0 && estado.lado[0] < 3 && estado.lado[1] < 3){//caso que no este completo el lado B
		if(estado.lado[0] == estado.lado[1])//si tienen la misma cantidad de misioneros y canivales
			return 1;
		else
			return 0;
	}
	else if(estado.lado[2] == 1 && estado.lado[0] > 0 && estado.lado[1] > 0 && estado.lado[0] <= 3 && estado.lado[1] <= 3){//Caso que no este vacio el lado B
		if(estado.lado[0] == estado.lado[1])//si tienen la misma cantidad de misioneros y canivales
			return 1;
		else
			return 0;
	}
	else
		return 0;
}


///////////TRANSICIONES//////////////////

//PARA TODAS LAS TRANSICIONES:
//Entrada: estructura de cmb
//salida : estructura de cmb con la transicion
//Realiza la transicion del estado

cmb pasarCanival(cmb estado){
	if(estado.lado[2] == 0){//Caso que este en lado A paso canival a B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0] + 1; //aumentamos canival
		nuevoLado[1] = estado.lado[1];
		nuevoLado[2] = 1;
		return crearEstado(nuevoLado, estado.idEstado, "Paso canival de A a B");
	}
	else{//caso que este en lado B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0] - 1; //Disminuimos canival a B
		nuevoLado[1] = estado.lado[1];
		nuevoLado[2] = 0;
		return crearEstado(nuevoLado, estado.idEstado, "Paso canival de B a A");
	}
}

cmb pasar2Canivales(cmb estado){
	if(estado.lado[2] == 0){//Caso que este en lado A paso canival a B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0] + 2; //aumentamos canivales
		nuevoLado[1] = estado.lado[1];
		nuevoLado[2] = 1;
		return crearEstado(nuevoLado, estado.idEstado, "Paso 2 canivales de A a B");
	}
	else{//caso que este en lado B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0] - 2; //Disminuimos canivales a B
		nuevoLado[1] = estado.lado[1];
		nuevoLado[2] = 0;
		return crearEstado(nuevoLado, estado.idEstado, "Paso 2 canivales de B a A");
	}
}

cmb pasarMisionero(cmb estado){
	if(estado.lado[2] == 0){//Caso que este en lado A paso misionero a B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0]; 
		nuevoLado[1] = estado.lado[1] + 1;//aumentamos misionero
		nuevoLado[2] = 1;//cruzar
		return crearEstado(nuevoLado, estado.idEstado, "Paso misionero de A a B");
	}
	else{//caso que este en lado B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0];
		nuevoLado[1] = estado.lado[1] - 1; //Disminuimos misionero a B
		nuevoLado[2] = 0;//cruzar
		return crearEstado(nuevoLado, estado.idEstado, "Paso misionero de B a A");
	}
}

cmb pasar2Misioneros(cmb estado){
	if(estado.lado[2] == 0){//Caso que este en lado A paso misioneros a B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0]; 
		nuevoLado[1] = estado.lado[1] + 2;//aumentamos misioneros
		nuevoLado[2] = 1;//cruzar
		return crearEstado(nuevoLado, estado.idEstado, "Paso 2 misioneros de A a B");
	}
	else{//caso que este en lado B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0];
		nuevoLado[1] = estado.lado[1] - 2; //Disminuimos misioneros a B
		nuevoLado[2] = 0;//cruzar
		return crearEstado(nuevoLado, estado.idEstado, "Paso 2 misioneros de B a A");
	}
}

cmb pasarUYU(cmb estado){
	if(estado.lado[2] == 0){//Caso que este en lado A paso canival y misionero a B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0] + 1; //aumentamos canival
		nuevoLado[1] = estado.lado[1] + 1;//aumentamos misionero
		nuevoLado[2] = 1;//cruzar
		return crearEstado(nuevoLado, estado.idEstado, "Paso misionero y canival de A a B");
	}
	else{//caso que este en lado B
		int *nuevoLado = malloc(sizeof(int)*3);
		nuevoLado[0] = estado.lado[0] - 1;// disminuimos canival a B
		nuevoLado[1] = estado.lado[1] - 1; //Disminuimos misionero a B
		nuevoLado[2] = 0;//cruzar
		return crearEstado(nuevoLado, estado.idEstado, "Paso misionero y canival de B a A");
	}
}


//////////FUNCIONES GENERALES///////////////////

//Entrada: estructura de cmb
//Salida: entero que verifica
//verifica si es la solucion 
int esFinal(cmb estado){
	if(estado.lado[0] == 3 && estado.lado[1] == 3 && estado.lado[2] == 1)  ///si es estado final
		return 1;
	else
		return 0;
}

//Entrada: estructura de cmb
//imprime estados
void imprimirEstado(cmb estado){
	printf("Id:%d; T:%s, IdAnt:%d\n", estado.idEstado, estado.transicion, estado.estadoAnterior );
}

//Entrada: lista de estructura de cmb y cantidad de estados
//muestra los pasos a seguir
void mostrarSolucion(cmb * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].estadoAnterior;
	}
}


///////////PRINCIPAL//////////////////
int canivalesMisioneros(){
	correlativo = 0;//id global
	int canAbiertos = 0;
	int canCerrados = 0;
	cmb bActual, bSiguiente;
	//definimos colas a ocupar
	cmb * abiertos = (cmb *)malloc(sizeof(cmb)*canAbiertos);
	cmb * cerrados = (cmb *)malloc(sizeof(cmb)*canCerrados);
	int *ladoInicio = malloc(sizeof(int)*3);
	//inicializamos estado inicial
	ladoInicio[0] = 0;
	ladoInicio[1] = 0;
	ladoInicio[2] = 0;
	cmb inicial = crearEstado(ladoInicio,0,"");
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	while(canAbiertos > 0){
		//sacamos estado a modificar
		bActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, bActual);
		if(esFinal(bActual) == 1){ // Aqui se encontro la solucion
			printf("Llegue\n");
			mostrarSolucion(cerrados,canCerrados-1);
			printf("\n\n");
			return 0;
		}else{
			//pasar canibal
			if(verificarPasarCanival(bActual) == 1){
				//se puede hacer el movimiento
				bSiguiente = pasarCanival(bActual);
				//se verifica que no este repetido
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					//si no esta repetido agregamos
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					//si esta repetido volvemos el id
					correlativo = correlativo - 1;
				}
			}
			//pasar 2 canivales 
			if(verificarPasar2Canivales(bActual) == 1){
				//se puede hacer el movimiento
				bSiguiente = pasar2Canivales(bActual);
					//se verifica que no este repetido
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					//si no esta repetido agregamos a abiertos
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					//si esta repetido volvemos el id
					correlativo = correlativo - 1;
				}
			}
			if(verificarPasarMisionero(bActual) == 1){
				bSiguiente = pasarMisionero(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarPasar2Misioneros(bActual) == 1){
				//se puede hacer el movimiento
				bSiguiente = pasar2Misioneros(bActual);
				//se verifica que no este repetido
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					//si no esta repetido agregamos a abiertos
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					//si esta repetido volvemos el id
					correlativo = correlativo - 1;
				}
			}
			//pasar UYU
			if(verificarPasarUYU(bActual) == 1){
				//se puede hacer el movimiento
				bSiguiente = pasarUYU(bActual);
				//se verifica que no este repetido
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					//si no esta repetido agregamos a abiertos
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					//si esta repetido volvemos el id
					correlativo = correlativo - 1;
				}
			}
		}
		//imprimimos estados
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
		//volvemos a sacar un estado al principio
	}
	printf("\n\n");
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sebastian Cabezas 
//Seccion L-3
//RUT 20.453.460-8
//Fecha creacion: 17-09-20
//Cuadrados magicos con BES

//FUNCIONES
int numerosIguales(int *** soluciones, int ** cuadrado, int cantidad);
int *** agregarSolucion(int *** soluciones, int * cantidad, int ** solucion);
int suma(int **cuadrado);
void imprimirSol(int *** soluciones, int cantidad);
int iguales(int **cuadrado);


//Entrada : lista de matrices soluciones, cuadrado a verificar, cantidad de soluciones en la lista
//Salida : entero que verifica
//verifica si los numeros de la martriz son iguales
int numerosIguales(int *** soluciones, int ** cuadrado, int cantidad){
    //comparamos todos los numeros para que no se repitan en el cuadrado
    int repetidos = 0;
    for (int i = 0; i < cantidad; i++)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                for (int z = 0; z < 3; ++z)
                {
                    for (int x = 0; x < 3; ++x)
                    {
                        if(soluciones[i][j][k] == cuadrado[z][x]){
                            repetidos++;
                        }
                    }
                }
            }
        }
        if(repetidos == 9)
            return 0;
        else
            repetidos = 0;
    }
    return 1;
}

//Entrada: lista de matrices con las soluciones , direccion de memoria de la cantidad de soluciones
// matriz solucion a agregar
//Salida: lista de soluciones con la solucion agregada
//Agrega solucion a la lista de soluciones
int *** agregarSolucion(int *** soluciones, int * cantidad, int ** solucion){
    int*** solucionesNuevas = (int ***)malloc(sizeof(int**)*(*cantidad+1));
    for (int i = 0; i < *cantidad+1; ++i){
        solucionesNuevas[i] = (int **)malloc(sizeof(int *)*3);
        for (int j = 0; j < 3; ++j){
            solucionesNuevas[i][j] = (int *)malloc(sizeof(int)*3);
        }
    }
    //Se copian las soluciones que ya estaban en la lista
    for (int i = 0; i < *cantidad; ++i){
        for(int j = 0; j < 3; j ++){
            for (int k = 0; k < 3; ++k){
                solucionesNuevas[i][j][k] = soluciones[i][j][k];
            }
        }
    }
    //Se agrega la nueva solución
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            solucionesNuevas[*cantidad][i][j] = solucion[i][j];
        }
    }
    *cantidad = *cantidad+1;//Se le suma a la cantidad 
    free(soluciones);//Se libera memoria 
    return solucionesNuevas;
}


//Entrada: cuadrado matriz
//Salida: suma de numeros
//funcion que suma la diagonal del cuadrado
int suma(int **cuadrado)
{
    int sumacol1 =0;
    for (int i = 0; i < 3; ++i)
    {
        sumacol1 = cuadrado[i][i] + sumacol1;
    }
    return sumacol1;
}

//Entrada:lista de soluciones y su cantidad
//imprime las matrices
void imprimirSol(int *** soluciones, int cantidad){
	for(int i = 0; i < cantidad; i ++){
		for (int j = 0; j < 3; ++j){
			for (int k = 0; k < 3; ++k){
				printf("%d ", soluciones[i][j][k]);
			}
			printf("\n");
		}
        int sumas = suma(soluciones[i]);
        printf("Suma del cuadrado = %d\n",sumas );
        printf("Solucion numero =  %d\n\n", i+1);
	}
	return;	
}

//Entrada: matriz cuadrado
//Salida: verifica con un entero
//verifica si la suma de sus columnas,filas y diagonales con iguales
int iguales(int **cuadrado){
    //definimos las sumas y sumamos filas,columnas y diagonales
    int sumaFil1  = cuadrado[0][0]+cuadrado[0][1]+cuadrado[0][2];
    int sumaFil2  = cuadrado[1][0]+cuadrado[1][1]+cuadrado[1][2];
    int sumaFil3  = cuadrado[2][0]+cuadrado[2][1]+cuadrado[2][2];
    int sumacol1  = cuadrado[0][0]+cuadrado[1][0]+cuadrado[2][0];
    int sumacol2  = cuadrado[0][1]+cuadrado[1][1]+cuadrado[2][1];
    int sumacol3  = cuadrado[0][2]+cuadrado[1][2]+cuadrado[2][2];
    int diagonal1 = cuadrado[0][0]+cuadrado[1][1]+cuadrado[2][2];
    int diagonal2 = cuadrado[0][2]+cuadrado[1][1]+cuadrado[2][0];
    //comparamos que las filas sean iguales y las columnas sean iguales
    if (sumaFil1 == sumaFil2 && sumaFil1 == sumaFil3 && sumacol1 == sumacol2 && sumacol1 == sumacol3){
        //comparamos que la fila y columna sumen igual
        if (sumacol1 == sumaFil1){
            //diagonales iguales
            if (diagonal1 == diagonal2){
                //que las diagonales sumen igual que las columnas
                 if(diagonal1 == sumaFil1 && diagonal2 == sumacol1){
                    return 1;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}

//FUNCION PRINCIPAL
void CuadradosMagicos(){
	int cantidad = 0;//cantidad de soluciones iniciales
	int *** soluciones = (int ***)malloc(sizeof(int**)*cantidad);//inicializamos lista
	int ** cuadrado = (int **)malloc(sizeof(int*)*3);//inicializamos cuadrado
	for (int i = 0; i < 3; ++i){
		cuadrado[i] = (int *)malloc(sizeof(int)*3);
	}
    int n;
    printf("Ingrese numero para los cuadrados : ");
    scanf("%d", &n);
    printf("\n");
    //hacemos la combinacion de numeros siempre que sean distintos
    for (int a = 0; a <= n; a++)
    {
        for (int b = 0; b <= n; b++)
        {
            if (b != a)
            {
                for (int c = 0; c <= n ; c++)
                {
                    if (c != b && c != a)
                    {
                        for (int d = 0; d <= n; d++)
                        {
                            if (d != b && d != b && d != c)
                            {
                                for (int e = 0; e <= n; e++)
                                {
                                    if ( e!= a && e != b && e != c && e != d)
                                    {
                                        for (int f = 0; f <= n; f++)
                                        {
                                            if (f!=a && f != b && f != c && f != d && f!= e)
                                         {
                                                for (int g = 0; g <= n; g++)
                                               	 {
                                                    if (g!= a && g != b && g != c && g != d && g!= e && g!= f)
                                                    {
                                            
                                                        for (int h = 0; h <= n; h++)
                                                        {
                                                            if (h!= a && h != b && h != c && h != d && h!= e && h != f && h != g)
                                                            {
                                                                for (int i = 0; i <= n ; i++)
                                                                {
                                                                    if (i!= a && i != b && i != c && i != d && i!= e && i!= f && i!= g && i!= h)
                                                                    {

                                                                        cuadrado[0][0] = a;
                                                                        cuadrado[0][1] = b;
                                                                        cuadrado[0][2] = c;
                                                                        cuadrado[1][0] = d;
                                                                        cuadrado[1][1] = e;
                                                                        cuadrado[1][2] = f;
                                                                        cuadrado[2][0] = g;
                                                                        cuadrado[2][1] = h;
                                                                        cuadrado[2][2] = i;
                                                                        //comparamos las filas,columnas y diagonales
                                                                        if (iguales(cuadrado)){
                                                                            //ver si los numeros del cuadrado se repite con alguno
                                                                            if(numerosIguales(soluciones, cuadrado, cantidad)){
                                                                                //se agrega a la solucion
                                                                                soluciones = agregarSolucion(soluciones, &cantidad, cuadrado);
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }  
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
            }
        }
        
    }
    //finalmente imprimimos las soluciones
    printf("Cantidad de soluciones = %d \n\n", cantidad);
    imprimirSol(soluciones, cantidad);
    //liberamos memoria
    for (int i = 0; i < 3; i++)
    {
        free(cuadrado[i]);
    }
    free(cuadrado);
    
}

//MENU PRINCIPAL
int main()
{
	//menu principal
	int validador = 1;
	while(validador == 1){
		int opcion;
		printf("1-Canivales y misioneros\n");
		printf("2-Cuadrados magicos\n");
		printf("3-Salir\n");
		printf("Ingrese opcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
			canivalesMisioneros();
			break;
			case 2:
			CuadradosMagicos();
			break;
			case 3:
			printf("Fin programa\n");
			validador = 0;
			break;
			default:
			printf("Opcion invalida.\n\n");
		}
	}
	return 0;
}


