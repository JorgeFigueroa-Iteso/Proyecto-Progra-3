#include "DGraph.h"

void printFlag(Bool f); //Función auxiliar para imprimir el resultado booleano

int main(void) {
    //Creación del grafo
    DG grafo = createDGraph(sizeof(int), sizeof(int), sizeof(char));
    //Contenido del grafo
    int n1 = 250, n2 = 500, n3 = 1000, n4=700, n5=235, size = sizeDGraph(grafo);
    //ID de los vértices, en este caso tipo char
    char idV1 = 'A', idV2 = 'B', idV3 = 'C', idV4 = 'D', idV5 = 'F';
    //Etiquetas de las aristas, en este caso tipo int
    int idE1 = 1, idE2 = 3, idE3 = 5, idE4 = 8, idE5 = 9;

    // Grafo vacío
    printf("Tamanio del grafo: %d\n", size);

    //Bandera para las funciones booleanas
    int flag;
    // Agregar vertice 1
    printf("\nAgregar vertice %c\n", idV1);
    flag = addVertex(grafo, &n1, &idV1);
    //printFlag(flag);
    // Agregar vertice 2
    printf("\nAgregar vertice %c\n", idV2);
    flag = addVertex(grafo, &n2, &idV2);
    //printFlag(flag);
    // Agregar vertice 3
    printf("\nAgregar vertice %c\n", idV3);
    flag = addVertex(grafo, &n3, &idV3);
    //printFlag(flag);
    // Agregar vertice 4
    printf("\nAgregar vertice %c\n", idV4);
    flag = addVertex(grafo, &n4, &idV4);
    //printFlag(flag);
    // Agregar vertice 5
    printf("\nAgregar vertice %c\n", idV5);
    flag = addVertex(grafo, &n5, &idV5);
    //printFlag(flag);
    // Repetir la agregación del vértice 4
    printf("\nAgregar vertice %c\n", idV4);
    flag = addVertex(grafo, &n4, &idV4);
    //printFlag(flag);

    size = sizeDGraph(grafo);
    printf("Tamanio del grafo: %d\n", size);

    //Crear relación de V1/A a V2/B, con ID5/9
    printf("\nAgregar relacion del V1:%c a V2:%c con la etiqueta %d\n", idV1, idV2, idE5);
    addEdge(grafo, &idV1, &idV2, &idE5);
    // Crear relación de V2/B a V3/C, , con ID1/1
    printf("\nAgregar relacion del V2:%c a V3:%c con la etiqueta %d\n", idV2, idV3, idE1);
    addEdge(grafo, &idV2, &idV3, &idE1);
    // Crear relación de V3/C a V4/D, con ID4/8
    printf("\nAgregar relacion del V3:%c a V4:%c con la etiqueta %d\n", idV3, idV4, idE4);
    addEdge(grafo, &idV3, &idV4, &idE4);
    // Crear relación de V3/C a V5/F, , con ID3/5
    printf("\nAgregar relacion del V3:%c a V5:%c con la etiqueta %d\n", idV3, idV5, idE3);
    addEdge(grafo, &idV3, &idV5, &idE3);
    // Crear relación de V3/C a V1/A, con ID2/3
    printf("\nAgregar relacion del V3:%c a V1:%c con la etiqueta %d\n", idV3, idV1, idE2);
    addEdge(grafo, &idV3, &idV1, &idE2);
    // Repetir la relación de V2/B a V3/C, con ID1/1
    printf("\nAgregar relacion del V2:%c a V3:%c con la etiqueta %d\n", idV2, idV3, idE1);
    addEdge(grafo, &idV2, &idV3, &idE1);

    printf("\n");
    //Verificar adyacencia de V1/A y V2/B
    printf("El vertice %c es adyacente al %c?\n", idV1, idV2);
    adjacent(grafo, &idV1, &idV2);
    // Verificar adyacencia de V5/A Y V3/C
    printf("El vertice %c es adyacente al %c?\n", idV5, idV3);
    adjacent(grafo, &idV5, &idV3);

    // Retorna los datos que se encuentran en los vértices y que son vecinos del vértice x.
    //Los retorna dentro de una lista
    printf("\n");
    List VecinosV3 = neighbors(grafo, &idV3);
    int tam = listSize(VecinosV3);
    printf("Tamanio lista de adyacencia de vertice C: %d\n", tam);
    for (int i = 0; i < tam; i++) {
        int * dato = listGet(VecinosV3, i);
        printf("Vecinos del Vertice %c, el vecino %d contiene el dato: %d\n", idV3, i+1, *dato);
    }

    //Retorna una lista negativa en -1, lo que significa que no tiene vecinos
    printf("\n");
    List VecinosV5 = neighbors(grafo, &idV5);
    tam = listSize(VecinosV5);
    printf("Tamanio lista %d\n", tam);

    //Obtener el dato del vértice 1
    printf("\n");
    int * datoV1 = getVertexData(grafo, &idV1);
    printf("El dato del vertice %c es: %d\n", idV1, *datoV1);

    //Modificar el dato del vértice 1 y obtenerlo
    printf("\n");
    int modifV1 = 100;
    setVertexData(grafo, &idV1, &modifV1);
    datoV1 = getVertexData(grafo, &idV1);
    printf("El dato del vertice %c es: %d\n", idV1, *datoV1);

    // Obtener la etiqueta de la arista entre V3 y V4
    printf("\n");
    int * label = getEdgeLabel(grafo, &idV3, &idV4);
    printf("Etiqueta de la relacion entre %c-%c: %d\n", idV3, idV4, *label);

    // Modificar la etiqueta de la arista entre V3 Y V4 y obtenerla
    printf("\n");
    int newEdge = 12;
    setEdgeLabel(grafo, &idV1, &idV2, &newEdge);
    label = getEdgeLabel(grafo, &idV1, &idV2);
    printf("Etiqueta de la relacion entre %c-%c: %d\n", idV3, idV4, *label);

    printf("\n");
    destroyDGraph(grafo);

    return 0;
}
