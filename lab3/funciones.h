typedef struct nodo nodo;
typedef struct grafo grafo;
typedef struct nodoVertice nodoVertice;
typedef struct nodoNumero nodoNumero;

//FUNCIONES
nodoNumero * crearNodoNumero(int dato);
nodoNumero * verificarGasolina(grafo * grafito, nodoNumero * primero);
nodoNumero * caminoCorto(grafo * grafoAdy);
nodoNumero * insertarPrincipio(nodoNumero * primero, nodoNumero * nuevo);
nodo * crearNodo(char * nombre, int costo, int costoGasolina);
nodo * insertar(nodo * primero,nodo * planeta);
grafo * crearGrafo(char * nombreArchivo);
grafo * modificarGrafo(grafo * grafito, char * nombreArchivo);
int TodoVisitado(int * visitados, int vertices);
int menorArreglo(int * distancia,int * visitados, int vertices);
int buscarIndex(nodoVertice * grafoAdyacente, char * nombre, int vertices);
int indexGasolina(nodoVertice * listaVertices, int indexOrigen, int vertices);
int costo(nodo * listaPlanetas, char * nombreBuscar );
int costoSinGasolina(nodo * listaPlanetas, char * nombreBuscar );
int costoGasolina(nodoVertice * lista, int index, int indexGasolina);
void agregarArchivo(grafo * grafoAdy, nodoNumero * primero);