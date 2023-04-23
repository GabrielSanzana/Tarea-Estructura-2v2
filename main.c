#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "stack.h"
#include "list.h"

typedef struct {
  char *nombre;  
  int ptoHab;
  int cantItems;
  List *Items;
  
} tipoJugador;

int main() {
   HashMap *mapaJugadores = createMap((long)2000);
  //se pone 2000 de capacidad para tener el doble de capacidad que la totalidad de jugadores 
  char caracter[100];
  FILE *archivoCsv = fopen("players100.csv", "r"); // abre el archivo CSV
  fgets(caracter, 99, archivoCsv);
  int ptoHab, CantItems,opcion = 0;
  char *nombre, *Items;
  
  return 0;
}