#ifndef DGRAPH_H_
#define DGRAPH_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef void * Type;

typedef struct strDGraph * DG;

typedef struct strList * List;

typedef enum{False, True} Bool;

// <----- Header DGraph ----->

DG createDGraph(size_t, size_t, size_t); // Crea una nueva instancia de un contenedor DGraph.

int sizeDGraph(DG); // Retorna el número de vértices que existen en el grafo.

Bool addVertex(DG graph, Type data, Type ID); // Agrega un nuevo vértice x, si no existe en el grafo DG.

Bool adjacent(DG graph, Type V1_ID, Type V2_ID); // Retornar true si en el contendor DG, existe una arista entre los vértices: x y y.

Bool addEdge(DG graph, Type source, Type destination, Type arista); // Agrega al grafo DG una arista z del vértice x al vértice y, si no existe.

Type getVertexData(DG graph, Type V); // Retorna el dato almacenado en el vértice x.

List neighbors(DG graph, Type Vert); // Retorna los datos que se encuentran en los vértices y que son vecinos del vértice x. Un vértice y es vecino de x,
                                     // si existe una arista de x a y.

Bool setVertexData(DG graph, Type V, Type data); // Almacena el dato d en el vértice x.

Type getEdgeLabel(DG graph, Type V1_ID, Type V2_ID); // Retorna la etiqueta asociada con la arista que conecta a los vértices: x, y;

Bool setEdgeLabel(DG graph, Type V1_ID, Type V2_ID, Type label); // Asigna la etiqueta l a la arista asociada con la arista que une a los vértices: x, y.

void destroyDGraph(DG graph); // Destruye el contenedor DGraph.

void printFlag(Bool f); 

#endif /* DGRAPH_H_ */

// <----- Header DGraph ----->

// <----- Header list.h ----->

// Creates the list and initialices all the values in 0 or NULL
List listCreate(size_t);

int listSize(List);

void listAdd(List, Type);

Type listGet(List, int);

void listSet(List, int, Type);

Type listRemove(List, int);

void listDestroy(List);

// <----- Header list.h ----->
