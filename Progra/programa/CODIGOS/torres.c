#include <stdio.h>
#include <stdlib.h>

/////////Muestra los pasos de las torres de hanoi/////////
//Sebastian Cabezas//seccion L-3//RUT 20.453.460-8///////
typedef struct pila pila;
struct pila
{
    int *arreglo;
    int maximo;
    int ultimo;
    char nombre;
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
//crea una pila nueva predeterminada
pila *crearpila(){
    pila *pilaNueva = malloc(sizeof(pila));
    pilaNueva->arreglo = malloc(sizeof(int)*100);
    pilaNueva->maximo=100;
    pilaNueva->ultimo=-1;
    pilaNueva->nombre ='N';
    return pilaNueva; 
}
 //indica si la pila esta vacia
int pilaVacia(pila *a){
    if(a->ultimo == -1)
        return 1;
    else
        return 0;
}
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
//imprime la pila completa
void imprimir(pila *a){
    for (int i = 0; i <= a->ultimo; ++i)
    {
        printf("%d ",a->arreglo[i] );
    }
    printf("\n");
}
/////////////Movimientos
//extrae el primero de la pila
int extraer(pila *a, int *x){
    if(pilaVacia(a) == 1)
        return 0;
    *x = a->arreglo[a->ultimo];
    a->ultimo = a->ultimo -1;
    return 1;
}
//inserta al principio de la pila
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
//funcion que lleva los discos de la pila A a pila C
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
//Crea las pilas y se les ingresan datos
int main()
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


