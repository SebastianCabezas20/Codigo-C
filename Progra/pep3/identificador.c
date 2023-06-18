#include <stdio.h>
#include <stdlib.h>
//Pregunta 1 "identificador" con busqueda espacio soluciones
//Sebastian Cabezas
//RUT 20.453.460-8
//Seccion C-3

//Para este programa se tiene que modificar el archivo identificador
//donde van las tripletas, cada numero va separado de un espacio
//ejemplo tripleta1[3,2,1] y tripleta2[3,3,0]
//EN EL ARCHIVO SE ESCRIBIRIA:
// 3 2 1 
// 3 3 0


//Una solucion se representa mediante una matriz de 3x3
//[1,0,0]
//[1,1,0]  donde los 1 representan cuadrados negros y 0 vacio
//[1,1,1]
//
//donde se van haciendo las posibles soluciones con los numeros de las tripletas

//RESTRICCION
//La restriccion principal es que el numero de la columna sea el numero de la tripleta
//Es restriccion ya que con asi podemos identificar las soluciones al problema
//Se valida porque el problema requiere que asi sea

//Optimizacion
//En este caso solo se hace la combinacion del numero de la tripleta y no de todos por ejemplo
//tripleta1 [1,2,3]
//El primer elemento es 1 entonces solo se haran las combinaciones [1,0,0][0,1,0][0,0,1] en la fila 1
//El segundo elemento es 2 entonces solo se haran las combinaciones [0,1,1][1,0,1][1,1,0] en la fila 2
//El tetcer elemento es 3 entonces solo se hara [1,1,1] en la fila 3
//asi haciendo mas rapido el proceso, no viendo todas las soluciones

//mediante 3 for,el primero hace las combinaciones de la primera fila, el segundo de la segunda y el tercero
// de la tercera, cuando encuentra una solucion valida, se vera que no sea repetida y se guardara 
//para no repetirlas.
//Habra un contador global que nos permitira ver si hay mas de un caso.



int casos = 0;//variable global

//Entrada: una lista de matrices, la direccion de memoria de la cantidad
//y la matriz a agregar
//salida: lista de matrices con la matriz agregada
//agrega matriz a lista
int *** agregarSolucion(int *** conjunto, int * cantElementos, int ** solucion){
	//Se crea el nuevo conjunto de soluciones
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos+1));
	for (int i = 0; i < *cantElementos+1; ++i){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*4);
		for (int j = 0; j < 4; ++j){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*4);
		}
	}
	//Se copian las soluciones existentes
	for (int numSolucion = 0; numSolucion < *cantElementos; ++numSolucion){
		for(int i = 0; i < 3; i ++){
			for (int j = 0; j < 3; ++j){
				conjuntoNuevo[numSolucion][i][j] = conjunto[numSolucion][i][j];
			}
		}
	}
	//Se agrega la nueva solución
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			conjuntoNuevo[*cantElementos][i][j] = solucion[i][j];
		}
	}
	*cantElementos = *cantElementos+1;//Se actualiza la cantidad de elementos
	free(conjunto);//Se libera memoria del conjunto de soluciones que ya no se utilizará
	return conjuntoNuevo;
}

//Entrada: lista de matrices, la cantidad de elementos de la lista y matriz a buscar
//Salida: retorna entero que verifica si se encuentra la matriz
//verifica si se encuentra la solucion repetida
int estaSolucion(int ***soluciones, int elementos, int **matriz){
	int iguales = 0;//caso inicial que no esta
	for (int i = 0; i < elementos; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				if(soluciones[i][j][k] == matriz[j][k])//revisamos uno elemento por uno
					iguales++;
			}
		}
		if(iguales == 9)//si son todos iguales retorna 1,significa que esta
			return 1;
		else
			iguales = 0;//volvemos a reiniciar el iguales
	}
	return 0;//si no se encuentran iguales no se encuentra repetida
}

//Entrada: matriz de identificador
//imprime identificador
void imprimir(int **identificador){
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			printf("%d ", identificador[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}

//Entrada: matriz identificador y matriz de posible solucion
/*int sonIguales(int **identificador, int**solucion){
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(identificador[i][j] != solucion[i][j])
				return 0;//son distintas
		}
	}
	return 1;//son todos iguales, entonces no se suma a los casos
}*/

//Entrada: matriz identificador y arreglo tripleta con los numeros
//Salida: retorna entero para verificar
//verifica si la suma de la columna es igual al numero en la tripleta
int verificar(int **identificador, int *tripleta){
	int sumacolumna0 = 0,sumacolumna1 = 0,sumacolumna2 = 0;
	for (int i = 0; i < 3; ++i){//sumamos los elemntos de la primero columna
		sumacolumna0 = sumacolumna0 + identificador[i][0];
	}
	for (int i = 0; i < 3; ++i){//sumamos los elemntos de la segunda columna
		sumacolumna1 = sumacolumna1 + identificador[i][1];
	}
	for (int i = 0; i < 3; ++i){//sumamos los elemntos de la tercera columna
		sumacolumna2 = sumacolumna2 + identificador[i][2];
	}

	//verificamos si las sumas coinciden;
	if(sumacolumna0 == tripleta[0]){
		if(sumacolumna1 == tripleta[1]){
			if(sumacolumna2 == tripleta[2]){
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

//Entrada: arreglo de tripletas
//Salida: retorna entero
//leer archivo y obtiene las tripletas
int obtenerDatos(int *tripleta1, int *tripleta2){

	FILE *pf;
	pf = fopen("identificador.txt","r");//abrimos el archivo
	if(pf == NULL)
		return 0;
	//leemos y rellenamos tripleta 1
	for (int i = 0; i < 3; ++i){
		fscanf(pf,"%d",&tripleta1[i]);
	}
	//leemos y rellenamos tripleta 1
	for (int i = 0; i < 3; ++i){
		fscanf(pf,"%d",&tripleta2[i]);
	}
	fclose(pf);//cerramos el archivo
	return 1;
	
}

//Entrada: matriz identificador inicial,arreglo tripleta 1
//arreglo tripleta 2
//Realiza las combinaciones de numeros
//                                tripleta1[3,2,3] tripleta2[3,3,2]
void semejante(int** identificador,int *tripleta1, int *tripleta2){
	int elementos = 0;
	int ***soluciones = malloc(sizeof(int**)*elementos);
	for(int i = 0;i < 3;i++){//primera fila
		//colocamos los numeros
		if(tripleta1[0] == 1){//caso que en la tripleta sale uno
			if(i == 0){//esta en la primera posicion
				identificador[0][0] = 1;
				identificador[0][1] = 0;
				identificador[0][2] = 0;
			}
			else if(i == 1){//esta en la segunda posicion
				identificador[0][0] = 0;
				identificador[0][1] = 1;
				identificador[0][2] = 0;
			}
			else if(i == 2){//esta en la tercera posicion
				identificador[0][0] = 0;
				identificador[0][1] = 0;
				identificador[0][2] = 1;
			}
		}
		else if(tripleta1[0] == 2){//caso que la tripleta sale 2
			if(i == 0){//esta en la primera posicion
				identificador[0][0] = 0;
				identificador[0][1] = 1;
				identificador[0][2] = 1;
			}
			else if(i == 1){//esta en la segunda posicion
				identificador[0][0] = 1;
				identificador[0][1] = 0;
				identificador[0][2] = 1;
			}
			else if(i == 2){//esta en la tercera posicion
				identificador[0][0] = 1;
				identificador[0][1] = 1;
				identificador[0][2] = 0;
			}

		}
		else if(tripleta1[0] == 3){//caso en la tripleta sale 3
			identificador[0][0] = 1;
			identificador[0][1] = 1;
			identificador[0][2] = 1;
		}
		else if(tripleta1[2] == 0){//caso en la tripleta sale 0
			identificador[2][0] = 0;
			identificador[2][1] = 0;
			identificador[2][2] = 0;
		}
		for (int j = 0; j < 3; ++j){
			if(tripleta1[1] == 1){//caso que en la tripleta sale uno
				if(j == 0){
					identificador[1][0] = 1;
					identificador[1][1] = 0;
					identificador[1][2] = 0;
				}
				else if(j == 1){
					identificador[1][0] = 0;
					identificador[1][1] = 1;
					identificador[1][2] = 0;
				}
				else if(j == 2){
					identificador[1][0] = 0;
					identificador[1][1] = 0;
					identificador[1][2] = 1;
				}
			}
			else if(tripleta1[1] == 2){//caso que la tripleta sale 2
				if(j == 0){
					identificador[1][0] = 0;
					identificador[1][1] = 1;
					identificador[1][2] = 1;
				}
				else if(j == 1){
					identificador[1][0] = 1;
					identificador[1][1] = 0;
					identificador[1][2] = 1;
				}
				else if(j == 2){
					identificador[1][0] = 1;
					identificador[1][1] = 1;
					identificador[1][2] = 0;
				}
			}
			else if(tripleta1[1] == 3){//caso en la tripleta sale 3
				identificador[1][0] = 1;
				identificador[1][1] = 1;
				identificador[1][2] = 1;
			}
			else if(tripleta1[2] == 0){//caso en la tripleta sale 0
					identificador[2][0] = 0;
					identificador[2][1] = 0;
					identificador[2][2] = 0;
				}
			for (int k = 0; k < 3; ++k)
			{
				if(tripleta1[2] == 1){//caso que en la tripleta sale uno
					if(k == 0){
						identificador[2][0] = 1;
						identificador[2][1] = 0;
						identificador[2][2] = 0;
					}
					else if(k == 1){
						identificador[2][0] = 0;
						identificador[2][1] = 1;
						identificador[2][2] = 0;
					}
					else if(k == 2){
						identificador[2][0] = 0;
						identificador[2][1] = 0;
						identificador[2][2] = 1;
					}
				}
				else if(tripleta1[2] == 2){//caso que la tripleta sale 2
					if(k == 0){
						identificador[2][0] = 0;
						identificador[2][1] = 1;
						identificador[2][2] = 1;
					}
					else if(k == 1){
						identificador[2][0] = 1;
						identificador[2][1] = 0;
						identificador[2][2] = 1;
					}
					else if(k == 2){
						identificador[2][0] = 1;
						identificador[2][1] = 1;
						identificador[2][2] = 0;
					}
				}
				else if(tripleta1[2] == 3){//caso en la tripleta sale 3
					identificador[2][0] = 1;
					identificador[2][1] = 1;
					identificador[2][2] = 1;
				}
				else if(tripleta1[2] == 0){//caso en la tripleta sale 0
					identificador[2][0] = 0;
					identificador[2][1] = 0;
					identificador[2][2] = 0;
				}
			
				int verificador = verificar(identificador,tripleta2);//verificamos si la suma de las columnas da la tripleta
				if(verificador == 1){
					if(estaSolucion(soluciones,elementos,identificador) == 0){//para verificar que no se repitan
						imprimir(identificador);
						casos++;//caso que no este en las soluciones
						soluciones = agregarSolucion(soluciones,&elementos,identificador);//agregamos para no repetir
					}
				}
			}
		}
	}
}



int main(int argc, char const *argv[])
{
	int *tripleta1,*tripleta2,**identificador;
	//reservamos memoria
	tripleta1 = malloc(sizeof(int)*3);
	tripleta2 = malloc(sizeof(int)*3);
	identificador = malloc(sizeof(int*)*3);
	for (int i = 0; i < 3; ++i)
	{
		identificador[i] = malloc(sizeof(int)*3);
	}

	//rellenamos la matriz
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			identificador[i][j] = 0;
		}
	}

	int info = obtenerDatos(tripleta1,tripleta2);
	if(info == 2||info == 0){
		printf("error de matriz\n");
		return 0;
	}
	//hay que sumar tripletas y ver si se podra
	semejante(identificador,tripleta1,tripleta2);
	printf("numero casos %d \n", casos );
	if(casos == 1)
		printf("Es correcto, hay un caso.\n");
	else if(casos == 0){
		printf("No es posible hacer combinaciones\n");
	}
	else{
		printf("Hay mas de un caso\n");
	}


	return 0;
}

