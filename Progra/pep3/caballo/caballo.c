#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Pregunta 2 "caballo" con busqueda espacio estado
//Sebastian Cabezas
//RUT 20.453.460-8
//Seccion C-3

//Para este programa se tiene que modificar el archivo tablero
//donde van el tablero y posicion del caballo
//ejemplo posicion del caballo[4,0] y tablero [00010] 
//                                            [00000] Donde los peones son 1 y 0 vacio
//                                            [00000]  
//                                            [00001]  
//                                            [00000]  
//
//EN EL ARCHIVO SE ESCRIBIRIA:
//4 0
//0 0 0 1 0
//0 0 0 0 0
//0 0 0 0 0
//0 0 0 0 1
//0 0 0 0 0


//Un estado estara representado por una estructura donde:
//Estara el tablero
//Posicion de caballo
//El numero de los peones, para encontrar la solucion
//La cantidad de moviemientos del caballo
//Matriz de movimientos donde se guardaran los movimientos hechos por el caballo

//ESTADO INICIAL
//Tablero que indique el usuario en el archivo
//Posicion que indique el usuario
//Cantidad de peones que ingrese el usuario
//Cantidad de movimientos 0 ya que no a comenzado
//Matriz de 0 elemntos ya que no se a movido el caballo

//ESTADO FINAL
//tablero sin peones si es que el caballo si los pudo comer todos
//posicion final del caballo
//cantidad de peones restantes
//Cantidad de movimemientos que hizo el caballo
//Matriz de movimientos n (2xn) donde podremos ver todos los movimientos del caballo hasta llega al final

//TRANSICIONES
//el caballo se puede mover :
//2 a la izquierda una arriba
//2 a la izquierda una abajo
//2 a la derecha una arriba
//2 a la derecha una abajo
//2 arriba una izquierda
//2 arriba una derecha
//2 abajo una izquierda
//2 abajo una derecha
//para estas transiciones se veriicara y despues se movera
//para el movimiento se cambiara la posicion del caballo,se suma cantidad de movimientos
//se agrega movimiento a la matriz movimientos del caballo

//Este tipo de busqueda es en anchura ya que se utilizan colas para guardar estados





typedef struct tablero tablero;

//definimos estructura de tablero
struct tablero{
	int **tablero; //tablero con peones y espacios vacios
	int *posicionCaballo; //arreglo con la posicion del caballo[eje y,eje x]
	int numeroPeones; //numero peones del tablero
	int canMovimientos;// cantidad de movimientos que efectuo el caballo
	int ** movimientos;  // matriz que tiene los movimientos
};




// Funciones de listas
tablero crearEstado( int ** tableroNuevo, int *posicionCaballoNueva, int numeroPeones, int ** movimientos, int canMovimientos); // crea un estado
tablero * agregarEstado(tablero * lista, int * elementos, tablero estado); // inserta elemento
tablero * sacarElemento(tablero * lista, int * elementos); // elimina primer elemento
int estaEstado(tablero * lista, int elementos, tablero b); // revisa si se encuenta en lista
void mostrarSolucion(tablero * lista, int ultimo); // imprime los pasos

// funciones chequear transicion 
int verificarIzqAbajo(tablero estado); // verifica si se puede avanzar a la izquierda abajo
int verificarIzqArriba(tablero estado); // verifica si se puede avanzar a la izquierda arriba
int verificarDerAbajo(tablero estado); // verifica si se puede avanzar a la derecha abajo
int verificarDerArriba(tablero estado); // verifica si se puede avanzar a la derecha arriba
int verificarAbajoIzq(tablero estado); // verifica si se puede avanzar abajo izquierda
int verificarAbajoDer(tablero estado); // verifica si se puede avanzar abajo derecha
int verificarArribaDer(tablero estado); // verifica si se puede avanzar arriba derecha
int verificarArribaIzq(tablero estado); // verifica si se puede avanzar arriba izquierda

// funciones de transicion
tablero izqAbajo(tablero estado); // avanzar a la izquierda abajo
tablero izqArriba(tablero estado); //avanzar a la izquierda arriba
tablero derAbajo(tablero estado); // avanzar a la derecha abajo
tablero derArriba(tablero estado); // avanzar a la derecha arriba
tablero abajoIzq(tablero estado); // avanzar abajo izquierda
tablero abajoDer(tablero estado); // avanzar abajo derecha
tablero arribaDer(tablero estado); // avanzar arriba derecha
tablero arribaIzq(tablero estado); // avanzar arriba izquierda


// funciones generales
int esFinal(tablero b);  // si es solucion
void imprimirEstado(tablero b); // para imprimir
tablero estadoInicial(); // genera un estado inicial, usa crear estado
int obtenerDatos(int **tableroNuevo,int *numeroPeones, int *posicionCaballoNueva);//obtiene posiciones
void imprimirSolucion(tablero estado);//imprime las posiciones a seguir
// implementaciones


/////////// La COLA //////////////////

//Entrada: tablero matriz,arreglo de dos elementos con la posicion,entero numero de peones
//entero con el id del anterior,una matriz de dos por canMovimientos que contiene los movimientos de a pares
//salida: retorna una estructura de tablero
//  Crea la estructura tablero, aumenta el correlativo
tablero crearEstado(int **tableroNuevo, int*posicionCaballoNueva,int numeroPeones, int ** movimientos, int canMovimientos){
	tablero nuevoEstado;
	nuevoEstado.tablero = tableroNuevo;
	nuevoEstado.posicionCaballo = posicionCaballoNueva;
	nuevoEstado.numeroPeones = numeroPeones;
	nuevoEstado.canMovimientos = canMovimientos;
	nuevoEstado.movimientos = movimientos;
	return nuevoEstado;
}

//Entrada:arreglo con la lista de tableros,entero con el numero de elementos de la lista
//estructura de tablero a agregar
//Salida: retorna una lista de tableros con tablero agregado
// crea una nuevo arreglo de largo *elementos+1
// incrementa *elementos
tablero * agregarEstado(tablero * lista, int * elementos, tablero estado){
	tablero * nuevaLista = (tablero *)malloc(sizeof(tablero)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado; // copia el contenido de elementos
	*elementos = *elementos+1; // notar que incrementa este contador externo
	free(lista); // libera el arreglo antiguo
	return nuevaLista;
}

//Entrada:arreglo con la lista de tableros,entero con el numero de elementos de la lista
//Salida: retorna una lista de tableros con tablero elminado
// crea un nuevo arreglo de tamaño menor y copia
// el antiguo en el
tablero * sacarElemento(tablero * lista, int * elementos){
	tablero * nuevaLista = (tablero *)malloc(sizeof(tablero)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1; // notar que se decrementa el contador
	free(lista);
	return nuevaLista;
}

//Entrada:arreglo con la lista de tableros,entero con el numero de elementos de la lista
//estructura de tablero a buscar
//Salida: retorna una entero .
// Verifica si el estado se encuentra en el arreglo
int estaEstado(tablero * lista, int elementos, tablero estado){
	for (int i = 0; i < elementos; ++i)
	{	//verificamos si la posicion del caballo es la misma, cantidad de peones y cantidad de movimientos
		if(lista[i].posicionCaballo[0] == estado.posicionCaballo[0] && lista[i].posicionCaballo[1] == estado.posicionCaballo[1]){
			if(lista[i].canMovimientos == estado.canMovimientos && lista[i].numeroPeones == estado.numeroPeones)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
}

//////////CHEQUEAR TRANSICIONES///////////////////

//Para todas las verificaciones
//Entrada: una estructura de tablero
//salida: entero que indica si se puede mover el caballo
//verificar si se puede mover el caballo hacia las direcciones


//primero verificamos si podermos mover el caballo hacia la izquierda suponiendo que lo movemos y no se sale del tablero
int verificarIzqArriba(tablero estado){
	if(estado.posicionCaballo[1]- 2 >= 0){
		if(estado.posicionCaballo[0]-1 >= 0)//verificamos si se puede mover hacia arriba   
			return 1;
		else
			return 0;// no puede subir     
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia la izquierda suponiendo que lo movemos y no se sale del tablero
int verificarIzqAbajo(tablero estado){
	if(estado.posicionCaballo[1]- 2 >= 0){
		if(estado.posicionCaballo[0]+1 <= 4)//verificamos si se puede mover hacia abajo y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia la derecha suponiendo que lo movemos y no se sale del tablero
int verificarDerAbajo(tablero estado){
	if(estado.posicionCaballo[1]+2 <= 4){
		if(estado.posicionCaballo[0]+1 <= 4)//verificamos si se puede mover hacia abajo y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia la derecha suponiendo que lo movemos y no se sale del tablero
int verificarDerArriba(tablero estado){
	if(estado.posicionCaballo[1]+2 <= 4){
		if(estado.posicionCaballo[0]-1 >= 0)//verificamos si se puede mover hacia arriba y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia arriba suponiendo que lo movemos y no se sale del tablero
int verificarArribaIzq(tablero estado){
	if(estado.posicionCaballo[0]- 2 >= 0){
		if(estado.posicionCaballo[1]-1 >= 0)//verificamos si se puede mover hacia la izquierda y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia arriba suponiendo que lo movemos y no se sale del tablero
int verificarArribaDer(tablero estado){
	if(estado.posicionCaballo[0] - 2 >= 0){
		if(estado.posicionCaballo[1]+1 <= 4)//verificamos si se puede mover hacia la derecha y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia abajo suponiendo que lo movemos y no se sale del tablero
int verificarAbajoIzq(tablero estado){
	if(estado.posicionCaballo[0]+ 2 <= 4){
		if(estado.posicionCaballo[1]-1 >= 0)//verificamos si se puede mover hacia la izquierda y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

//primero verificamos si podermos mover el caballo hacia abajo suponiendo que lo movemos y no se sale del tablero
int verificarAbajoDer(tablero estado){
	if(estado.posicionCaballo[0]+2 <= 4){
		if(estado.posicionCaballo[1]+1 <= 4)//verificamos si se puede mover hacia la derecha y no salirse
			return 1;
		else
			return 0;// no puede bajar   
	}
	else
		return 0;//no se puede mover
}

///////////TRANSICIONES//////////////////

//Para todos los movimientos 
//Entrada: una estructura de tablero
//la estructura de tablero con el movimiento del caballo
//o la eliminacion del peon
//Salida: estructura de tablero
//realiza el moviemiento descrito,eliminando el peon si se encuentra en
//esa ubicacion

// muevo el caballo izquierda abajo
tablero izqAbajo(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]+1][estado.posicionCaballo[1]-2] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]+1][estado.posicionCaballo[1]-2] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]+1][estado.posicionCaballo[1]-2] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}

//mover caballo izquierda arriba
tablero izqArriba(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]-1][estado.posicionCaballo[1]-2] == 0){//en esa posicion no hay peon
	
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}

		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}

		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}

	if(estado.tablero[estado.posicionCaballo[0]-1][estado.posicionCaballo[1]-2] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon

		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]-1][estado.posicionCaballo[1]-2] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}

//mover caballo hacia la derecha y abajo
tablero derAbajo(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]+1][estado.posicionCaballo[1]+2] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]+1][estado.posicionCaballo[1]+2] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]+1][estado.posicionCaballo[1]+2] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}

//mover caballo hacia la derecha arriba
tablero derArriba(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]-1][estado.posicionCaballo[1]+2] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]-1][estado.posicionCaballo[1]+2] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]-1][estado.posicionCaballo[1]+2] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-1;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+2;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}

//mover 2 arriba y a la derecha
tablero arribaDer(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]-2][estado.posicionCaballo[1]+1] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]-2][estado.posicionCaballo[1]+1] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]-2][estado.posicionCaballo[1]+1] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}

//mover el caballo 2 arriba y izquierda
tablero arribaIzq(tablero estado){
	
	if(estado.tablero[estado.posicionCaballo[0]-2][estado.posicionCaballo[1]-1] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				movimientosNuevos[i][0] = estado.movimientos[i][0];
				movimientosNuevos[i][1] = estado.movimientos[i][1];
			}
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]-2][estado.posicionCaballo[1]-1] == 1){//en esa posicion hay peon
	
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}

		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]-2][estado.posicionCaballo[1]-1] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]-2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}

//mover caballo 2 abajo y derecha
tablero abajoDer(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]+2][estado.posicionCaballo[1]+1] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]+2][estado.posicionCaballo[1]+1] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]+2][estado.posicionCaballo[1]+1] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]+1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}
tablero abajoIzq(tablero estado){
	if(estado.tablero[estado.posicionCaballo[0]+2][estado.posicionCaballo[1]-1] == 0){//en esa posicion no hay peon
		//es el mismo tablero ya que no se modifica
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];
		return crearEstado(estado.tablero, posicionCaballoNueva, estado.numeroPeones, movimientosNuevos,estado.canMovimientos+1);
	}
	if(estado.tablero[estado.posicionCaballo[0]+2][estado.posicionCaballo[1]-1] == 1){//en esa posicion hay peon
		//no es el mismo tablero asi que se modifica y se saca el peon
		int **tableroNuevo = malloc(sizeof(int*)*5);
		for (int i = 0; i < 5; ++i)
		{
			tableroNuevo[i] = malloc(sizeof(int)*5);
		}
		//copiamos el tablero
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				tableroNuevo[i][j] = estado.tablero[i][j];
			}
		}
		//modificamos el nuevo tablero
		tableroNuevo[estado.posicionCaballo[0]+2][estado.posicionCaballo[1]-1] = 0;//sacamos peon
		//se modifica la posicion del caballo y se agrega a movientos
		int *posicionCaballoNueva = malloc(sizeof(int)*2);//arreglo con las posiciones nuevas
		posicionCaballoNueva[0] = estado.posicionCaballo[0]+2;
		posicionCaballoNueva[1] = estado.posicionCaballo[1]-1;
		int **movimientosNuevos = malloc(sizeof(int*)*estado.canMovimientos +1);//matriz nuevos movimientos
		for (int i = 0; i < estado.canMovimientos+1; ++i)
		{
			movimientosNuevos[i]=malloc(sizeof(int)*2);
		}
		//copiamos los movimientos
		for (int i = 0; i < estado.canMovimientos; ++i)
		{
			movimientosNuevos[i][0] = estado.movimientos[i][0];
			movimientosNuevos[i][1] = estado.movimientos[i][1];
		}
		//agregamos movimientos
		movimientosNuevos[estado.canMovimientos][0] = posicionCaballoNueva[0];
		movimientosNuevos[estado.canMovimientos][1] = posicionCaballoNueva[1];

		return crearEstado(tableroNuevo, posicionCaballoNueva, estado.numeroPeones-1, movimientosNuevos,estado.canMovimientos+1);
	}
}



//x////////FUNCIONES GENERALES///////////////////


//Entrada: estructura de tablero
//Salida: entero que verifica si es el final
// verifica si es la solucion 
int esFinal(tablero b){
  return(b.numeroPeones == 0);
}

//Entrada: estructura de tablero
// imprime un estado en particular


//Entrada: estructura de tablero
// muestra los pasos para llegar a la solucion
void imprimirSolucion(tablero estado){
	printf("cantidad de movimientos %d \n", estado.canMovimientos );
	for (int i = 0; i < estado.canMovimientos; ++i)
	{
		printf("%d %d \n",estado.movimientos[i][0],estado.movimientos[i][1] );
	}
}

//Entrada: matriz a rellenar con los numeros del archivo
//la direccion de memoria del numero de peones y la direccion de memoria
//de la posicion del caballo
//Salida: Retorna un entero si se realiza con exito
//obtenemos los datos,posiciones a traves de archivos
int obtenerDatos(int **tableroNuevo,int *numeroPeones, int *posicionCaballoNueva){
	FILE *pf;
	pf = fopen("tablero.txt","r");//abrimos el archivo
	if(pf == NULL){
		return 0;
	}
	int posicionI,posicionJ;
	fscanf(pf,"%d",&posicionJ);//leemos la posicion j
	fscanf(pf,"%d",&posicionI);//leemos la posicion i
	//asignamos
	posicionCaballoNueva[0] = posicionJ;
	posicionCaballoNueva[1] = posicionI;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
		
			if(fscanf(pf,"%d",&tableroNuevo[i][j])==EOF){//leemos matriz
				return 2;
			}
			
		}
	}
	

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{

			printf(" %d",tableroNuevo[i][j] );//imprimimos la matriz 
			if(tableroNuevo[i][j] == 1)
				*numeroPeones = *numeroPeones + 1;//identificamos la cantidad de peones
		}
		printf("\n");
	}
	fclose(pf);//cerramos el archivo
	return 1;
	
}

//Salida: retorna tablero inicial con matriz del
// crea el estado inicial
tablero estadoInicial() {//reservo memoria para el tablero
  	int ** tableroNuevo = malloc(sizeof(int*)*5);
  	for (int i = 0; i < 5; ++i)
  	{
  		tableroNuevo[i] = malloc(sizeof(int)*5);
  	}
  	for (int i = 0; i < 5; ++i)//rellenamos de 0s
  	{
  		for (int j = 0; j < 5; ++j)
  		{
  			tableroNuevo[i][j] = 0;
  		}
  	}
  	int * posicionCaballoNueva = malloc(sizeof(int)*2);
  	int numeroPeones;
  	int datos = obtenerDatos(tableroNuevo,&numeroPeones,posicionCaballoNueva);//obtenemos las posiciones y peones
  	if(datos == 2 || datos == 0){//identificamos si es error de matriz
  		printf("error matriz\n");
  	}
  	printf("%d %d\n",posicionCaballoNueva[0],posicionCaballoNueva[1] );
  	int **movimientosNuevos = malloc(sizeof(int*)*0);
  	int canMovimientos = 0;
 	return crearEstado(tableroNuevo, posicionCaballoNueva,numeroPeones, movimientosNuevos, canMovimientos);
}

///////////PRINCIPAL//////////////////
int main(){
	int canAbiertos = 0;
	int canCerrados = 0;
	tablero bActual, bSiguiente;
	tablero * abiertos = (tablero *)malloc(sizeof(tablero)*canAbiertos);
	tablero * cerrados = (tablero *)malloc(sizeof(tablero)*canCerrados);

	tablero inicial = estadoInicial();
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);

    // mientras existan estados por revisar (abiertos)
	while(canAbiertos > 0){
		
		bActual = abiertos[0]; // sacamos el primero de la lista de los pendientes(abiertos)
		abiertos = sacarElemento(abiertos, &canAbiertos); // eliminamos el primero de la lista
		cerrados = agregarEstado(cerrados, &canCerrados, bActual); // agregamos a los revisados 
		if(esFinal(bActual) == 1){ // es la solucion buscada?
			printf("Se encontro la solucion\n");
			imprimirSolucion(bActual);
			return 0;
		}
		else{ // si no es solucion, reviso todas las transiciones posibles
			
			int verifica = verificarArribaDer(bActual);
			//puedo mover el caballo 2 izquierda y abajo
			if(verificarIzqAbajo(bActual) == 1){
				
				bSiguiente = izqAbajo(bActual); // genero el estado
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}
			//puedo mover el caballo 2 izquierda y arriba
			if(verificarIzqArriba(bActual) == 1){
			
				bSiguiente = izqArriba(bActual); // genero el estado
                // verifico si no se paso por el anteriormente
       
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
					
				}
			}
			//puedo mover el caballo 2 derecha y abajo
			if(verificarDerAbajo(bActual) == 1){
				bSiguiente =derAbajo(bActual); // genero el estado
			
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}
			//puedo mover el caballo 2 derecha y arriba
			if(verificarDerArriba(bActual) == 1){
				bSiguiente = derArriba(bActual); // genero el estado
		
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}
			//puedo mover el caballo 2 arriba y derecha
			if(verificarArribaDer(bActual) == 1){
				bSiguiente = arribaDer(bActual); 
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}
			//puedo mover el caballo 2 arriba y izquierda
			if(verificarArribaIzq(bActual) == 1){
				bSiguiente = arribaIzq(bActual); // genero el estado
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}
			//puedo mover el caballo 2 abajo y derecha
			if(verificarAbajoDer(bActual) == 1){
				bSiguiente = abajoDer(bActual); // genero el estado
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}
			//puedo mover el caballo 2 abajo y izquierda
			if(verificarAbajoIzq(bActual) == 1){
				bSiguiente = abajoIzq(bActual); // genero el estado
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
			}

		} // fin del else caso que no era solucion


	} // vuelvo a revisar si es que quedan pendientes (abiertos)

	printf("no se pudo comer a todos los peones\n");
	return 0;
}

