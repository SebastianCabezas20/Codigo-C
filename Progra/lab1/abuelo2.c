#include <stdlib.h>
#include <stdio.h>

//Sebastian cabezas
//Seccion L-3
//rut 20.453.460-8

///monedas  10   $500
//          50   $100         
//          100  $50       Monedas 660
//          500  $10       Total 22000  
//
//Mayor al menos 50% del total
//Medio al menos 20% del total
//Menor la mayor cantidad de monedas

//Mayor[500,100,50,10];
//Medio[500,100,50,10];
//Menor[500,100,50,10];

// un criterio de optimizacion es el total de monedas de 500,100,50, y 10 
//porque existe cierto tope de monedas que tiene el abuelo
//criterio de el minimo de dinero que debe tener cada hermano


int verificar(int **hermanos){
	int mayor,medio,menor;
	//suma de monedas
	mayor = hermanos[0][0]+hermanos[0][1]+hermanos[0][2]+hermanos[0][3];
	medio = hermanos[1][0]+hermanos[1][1]+hermanos[1][2]+hermanos[1][3];
	menor = hermanos[0][0]+hermanos[2][1]+hermanos[2][2]+hermanos[2][3];
	//suma de dinero
	//segun la matriz se multiplica por valores
	int mayorDinero = (hermanos[0][0]*500)+(hermanos[0][1]*100)+(hermanos[0][2]*50)+(hermanos[0][3]*10);
	int medioDinero = (hermanos[1][0]*500)+(hermanos[1][1]*100)+(hermanos[1][2]*50)+(hermanos[1][3]*10);

	if(menor > mayor && menor > medio){//verificar con restricciones de cantidad de monedas
		if(mayorDinero >= 11250 && medioDinero >= 4400)//verificar con restricciones de cantidad de dinero
			return 1;
		else 
			return 0;
	}
	else
		return 0;
}



int main(int argc, char const *argv[])
{
	int **hermanos =malloc(sizeof(int*)*3);
	for (int i = 0; i < 3; ++i)
	{
		hermanos[i] = malloc(sizeof(int)*4);
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			for (int k = 0; k < 10; ++k)
			{
				printf(" %d %d %d \n",i,j,k);
			}
		}
	}

	return 0;
}