#include <stdio.h>
#include <stdlib.h>
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
			system("torres");
			break;
			case 2:
			system("contagiados");
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