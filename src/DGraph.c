#include "DGraph.h"
// #include "list.h"

// <----- Contenedor DGraph ----->

//Estructura del Vértice
struct strVertex {
    Type data; //Datos génericos almacenados en el Vértice
    Type ID;    //Identificador génerico
    List edges; //Lista de adyacencia
    int lenlist; //Longitud de la lista de adyacencia
};

typedef struct strVertex * Vertex; //Definición de tipo Vértice

// Estructura de la Arista
struct strEdge {
    Type ID;            //Identificador génerico
    Vertex source;      //Vértice de origen
    Vertex destination; //Vértice destino
};

typedef struct strEdge *Edge; // Definición de tipo Edge/Arista

// Estructura para representar el DGraph
// Podemos definir un grafo como un arreglo de listas de adyacencia
struct strDGraph {
    unsigned int size;  //Tamaño del grafo (número de vértices)
    size_t size_data;   //Tamaño de la información contenida en el vértice
    size_t size_ID_vert; //Tamaño del identificador del vértice
    size_t size_ID_edge; //Tamaño del identificador de la arista
    List vertex;        //Lista de vértices
    List edges;         //Lista de aristas
};

DG createDGraph(size_t bytes, size_t ID_V, size_t ID_E) { // Crea una nueva instancia de un contenedor DGraph.
    DG graph = malloc(sizeof(struct strDGraph)); //Reservar memoria dinámica
    // Inicializar todos los campos de tamaños con los parámetros de la función
    graph->size_data = bytes;   
    graph->size_ID_edge = ID_E;
    graph->size_ID_vert = ID_V;
    graph->size = 0;
    // Crear lista de vértices
    graph->vertex = listCreate(sizeof(struct strVertex));
    return graph; //Regresar apuntador tipo DG
}

//Función para la creación de Vértices
Vertex CreateVertex(Type data, size_t bytes, Type ID, size_t bytesID) {
    Vertex newVertex = malloc(sizeof(struct strVertex)); //Reservar memoria dinámica para el vértice
    newVertex->data = malloc(bytes);    // Reservar memoria dinámica para el dato genérico del vértice
    memcpy(newVertex->data, data, bytes); //Copiarlo a su respectivo campo

    newVertex->ID = malloc(bytesID);    // Reservar memoria dinámica para el identificador genérico del vértice
    memcpy(newVertex->ID, ID, bytesID); // Copiarlo a su respectivo campo

    newVertex->edges = listCreate(sizeof(Edge)); //Crear la lista de aristas
    newVertex->lenlist = 0;                     //Inicializar su tamaño en 0
    return newVertex;   //Regresar apuntador tipo vértice
}

int sizeDGraph(DG graph) { // Retorna el número de vértices que existen en el grafo.
    if (graph != NULL)
        return graph->size;
    return -1;
}

Vertex searchVertex(DG graph, Type ID) {
    // Buscar vértice mediante su identificador
    for (int i = 0; i < listSize(graph->vertex); i++) {
        Vertex temp = malloc(sizeof(Vertex));
        temp = listGet(graph->vertex, i);
        //  Comparar la memoria para determinar si los ID son iguales
        if (memcmp(ID, temp->ID, graph->size_ID_vert) == 0) {
            return temp;
        }
    }
    //Si el vértice no existe o no es encontrado regresar NULL
    return NULL;
}

Bool addVertex(DG graph, Type data, Type ID) { // Agrega un nuevo vértice x, si no existe en el grafo DG.
    if (graph != NULL) {
        //Caso Grafo vacío
        Vertex New_vertex = CreateVertex(data, graph->size_data, ID, graph->size_ID_vert);
        if (graph->size == 0) {
            listAdd(graph->vertex, New_vertex); // Añadir a la lista de vértices
            graph->size = 1; // Actualizar el tamaño del grafo
            printf("Vertice agregado correctamente\n");
            return True;
        }
        //Caso Grafo no vacío
        //Verificar que no exista el vértice en el grafo
        for(int i=0; i<graph->size; i++){
            Vertex current = listGet(graph->vertex, i);
            if(memcmp(ID, current->ID, graph->size_ID_vert)==0){ //En caso de que ya existe ese identificador del vértice
                printf("Coincidencia\n"); 
                return False;}
        }
        //Si no existe
        listAdd(graph->vertex, New_vertex); // Añadir a la lista de vértices
        graph->size += 1;                   // Actualizar el tamaño del grafo
        printf("Vertice agregado correctamente\n");
        return True;
    }
}

//Agrega al grafo DG una arista z del vértice x al vértice y, si no existe.
Bool addEdge(DG graph , Type source, Type destination, Type arista) {
    Vertex sourceVertex = searchVertex(graph, source);          // Encontrar el vértice de origen
    Vertex destinationVertex = searchVertex(graph, destination); // Encontrar el vértice de destino
    if (graph != NULL) { // Comprobar que graph existe
        if (adjacent(graph, source, destination) == False) { // Verificar que esa relación no exista
            Edge newEDG = malloc(sizeof(struct strEdge));    //  Reservar memoria
            newEDG->source = sourceVertex;                   //  Registrar los vertices en la arista
            newEDG->destination = destinationVertex;
            newEDG->ID = malloc(sizeof(graph->size_ID_edge)); // Reservar memoria para el identificador
            memcpy(newEDG->ID, arista, graph->size_ID_edge); // Asignar el identificador
            sourceVertex->lenlist += 1;                       // Actualizar el tamnaño de la lista de adyacencia
            listAdd(sourceVertex->edges, newEDG); //  Registrar la arista en las relaciones de el vertice x
            printf("La arista del vertice x al vertice y fue creada con exito\n");
            return True;
        }
        printf("La arista del vertice x al vertice y ya existe\n"); //Si la arista ya había sido previamente creada
        return False;
    }
    printf("Error, direción del grafo invalida\n"); //Caso de dirección del grafo NULL
    return False;
}

// Retorna los datos que se encuentran en los vértices y que son vecinos del vértice x. Un vértice y es vecino de x, si existe una arista de x a y.
List neighbors(DG graph, Type Vert) {
    Vertex V = searchVertex(graph, Vert); //Buscar el vértice
    if (graph != NULL) { //Si el grafo existe
        if (listSize(V->edges) != 0) { //Si la lista de adyacencia existe
            List VertCont = listCreate(sizeof(Type)); //Crear una nueva lista para retornaar
            for (int i = 0; i < V->lenlist; i++) {
                Edge current = listGet(V->edges, i); //Arista temporal para clonar la lista
                listAdd(VertCont, current->destination->data); // Agregar a la lista los vértices destino
            }
            printf("El vertice x cuenta con vecinos\n");
            return VertCont; //Retornar la lista
        }
        printf("El vertice x no tiene vecinos\n");
        return NULL;
    }
    return NULL;
}

Bool adjacent(DG graph, Type V1_ID, Type V2_ID) { // Retornar true si en el contendor DG, existe una arista entre los vértices: x y y.
    Vertex V1 = searchVertex(graph, V1_ID); // Buscar el vértice 1
    Vertex V2 = searchVertex(graph, V2_ID); // Buscar el vértice 2
    if (V1 != NULL && V2 != NULL) {         // Si ambos vértices existen o fueron encontrados
        if (V1->lenlist > 0 || V2->lenlist > 0) { // Si ambos vértices cuentan con una lista de adyacencia
            for (int i = 0; i < listSize(V1->edges); i++) {
                Edge current = listGet(V1->edges, i); //Obtener una arista temporal de su lista de relaciones
                if (current->destination == V2) {     //Comparar el destino de la arista con el vértice que estamos buscando
                    printf("El vertice x tiene una relacion con el vertice y\n"); 
                    return True;
                }
            }
            printf("No existe una arista desde el vertice X al vertice Y\n");
            return False;
        }
        printf("No existen relaciones en los vertices\n");
        return False;
    }
    printf("No se encontro uno o ambos vertices dados\n");
    return False;
}

Type getVertexData(DG graph, Type Vert){ // Retorna el dato almacenado en el vértice x.
    if (graph != NULL) { //Si el grafo existe
        Vertex V = searchVertex(graph, Vert); //Encontrar el vertice
        if (V != NULL) { //Si el vértice existe
            return V->data; //Retornar su dato
            }
            printf("No existe el vertice\n");
            return NULL;
        }
        return NULL;
}

Bool setVertexData(DG graph, Type V, Type data) { // Almacena el dato d en el vértice x.
    if (graph != NULL) { //Si el grafo existe
        Vertex Vert = searchVertex(graph, V); //Buscar el vértice
        if (Vert != NULL) { //Si el vértice existe o fue encontrado
            memcpy(Vert->data, data, graph->size_data);
            return True;
        }
        printf("No existe el vertice\n");
    }
}

Type getEdgeLabel(DG graph, Type V1_ID, Type V2_ID) { // Retorna la etiqueta asociada con la arista que conecta a los vértices: x, y;
    if (graph != NULL) { //Si el grafo existe
        Vertex Vert1 = searchVertex(graph, V1_ID); // Buscar el vértice 1
        Vertex Vert2 = searchVertex(graph, V2_ID); // Buscar el vértice 2
        for (int i = 0; i < Vert1->lenlist; i++) {  //Recorrer la lista de relaciones
            Edge current = listGet(Vert1->edges, i); // Obtener una arista temporal de su lista de relaciones
            if (memcmp(current->destination, Vert2, graph->size_ID_vert) == 0) { //Si le etiqueta coincide con el destino de la arista temporal
                return current->ID; //Retornar la etiqueta
            }
        }
    }
    return NULL;
}

Bool setEdgeLabel(DG graph, Type V1_ID, Type V2_ID, Type label) { // Asigna la etiqueta l a la arista asociada con la arista que une a los vértices: x, y.
    if (graph != NULL) {
        Vertex V1 = searchVertex(graph, V1_ID); // Buscar el vértice 1
        Vertex V2 = searchVertex(graph, V2_ID); // Buscar el vértice 2
        for (int i = 0; i < V1->lenlist; i++) {
            Edge current = listGet(V1->edges, i); // Obtener una arista temporal de su lista de relaciones
            if (memcmp(current->destination, V2, graph->size_ID_vert) == 0) { //Si le etiqueta coincide con el destino de la arista temporal
                memcpy(current->ID, label, graph->size_ID_edge); //Actualizar la etiqueta
                return True;
            }
            printf("No existe la arista\n");
        }
    }
    return False;
}

// Destruir el grafo y liberar la memoria asignada.
void destroyDGraph(DG graph) {
    if (graph != NULL) { //Si el grafo existe
        for (int i = 0; i < graph->size; i++) {
            Vertex current = listGet(graph->vertex, i); //Obtener un vértice temporal de la lista de vértices
            listDestroy(current->edges); //Destruir la lista de adyacencia
            free(current); //Liberar la memoria del vértice
            printf("Se destruyo el vertice\n");
        }
        listDestroy(graph->vertex); //Destruir la lista de vértices
        free(graph); //Liberar la memoria del grafo
        printf("Se destruyo el grafo\n");
        return;
    }
    printf("No existe el grafo\n");
    return;
}

void printFlag(Bool f) { //Función auxiliar
    if (f == 0) //Imprimir False
        printf("Operacion no realizada\n");
    else if (f == 1) //Imprimir True
        printf("Operacion realizada con exito\n");
}

// <----- Contenedor DGraph ----->


// <----- Contenedor List ----->



struct strNode {
    struct strNode * next;
    struct strNode * prior;
    Type data;
};

typedef struct strNode * Node;

struct strList {
    Node first;
    Node last;
    unsigned int size;
    size_t bytes;
};

List listCreate(size_t bytes) {
    List new = malloc(sizeof(struct strList));
    if (new != NULL) {
        new->bytes = bytes;
        new->first = NULL;
        new->last = NULL;
        new->size = 0;
        return new;
    }
    return NULL;
}

int listSize(List l1) {
    if (l1 != NULL)
        return l1->size;
    return -1;
}

Node nodeCreate(Type data, size_t bytes) {
    Node new = malloc(sizeof(struct strNode));
    new->data = data;
    new->prior = NULL;
    new->next = NULL;
    return new;
}

void listAdd(List lt, Type data) {
    if (lt != NULL) {
        Node new = nodeCreate(data, lt->bytes);
        if (listSize(lt) == 0) {
            lt->first = new;
            lt->last = new;
            lt->size++;
        }
        else {
            new->prior = lt->last;
            lt->last->next = new;
            lt->last = new;
            lt->size++;
        }
    }
}

Type listGet(List lt, int index) {
    if (lt == NULL) {
        return NULL;
    }
    else if (index >= lt->size || index < 0) {
        return NULL;
    }
    Node current = lt->first;
    for (size_t i = 0; i < lt->size; i++) {
        if (i == index) {
            return current->data;
        }
        else {
            current = current->next;
        }
    }
    return NULL;
}

void listSet(List lt, int index, Type data) {
    if (lt != NULL) {
        if (lt->size <= index && index >= 0) {
            Node current = lt->first;
            int i = 0;
            while (i < index) {
                current = current->next;
                i++;
            }
            memcpy(current->data, data, lt->bytes);
        }
        else {
            printf("Index fuera del rango\n");
        }
    }
    else {
        printf("List not created\n");
    }
}

Type listRemove(List lt, int index) {
    if (lt != NULL) {
        if (index >= 0 && index < lt->size) {
            if (lt->size == 1) {
                Type temp = lt->first->data;
                free(lt->first);
                lt->first = NULL;
                lt->last = NULL;
                lt->size--;
                return temp;
            }
            else {
                if (index == 0) {
                    Type temp = lt->first->data;
                    Node next = lt->first->next;
                    free(lt->first);
                    lt->first = next;
                    lt->first->prior = NULL;
                    lt->size--;
                    return temp;
                }
                else if (index == lt->size - 1) {
                    Type temp = lt->last->data;
                    Node prior = lt->last->prior;

                    free(lt->last);
                    lt->last = prior;
                    prior->next = NULL;
                    lt->size--;
                    return temp;
                }
                else {
                    Node current = lt->first;
                    int i = 0;
                    while (i < index){
                        current = current->next;
                        i++; }
                    Type temp = current->data;
                    Node next = current->next;
                    Node prior = current->prior;
                    free(current);
                    next->prior = prior;
                    prior->next = next;
                    lt->size--;
                    return temp;
                }
                return NULL;
            }
        }
        else {
            return NULL;
        }
    }
    else {
        printf("List not created\n");
        return NULL;
    }
}

void listDestroy(List l) {
    Type temp;
    if (l != NULL) {
        while (l->size != 0) {
            temp = listRemove(l, 0);
        }
        free(temp);
    }
    free(l);
}


// <----- Contenedor List ----->

