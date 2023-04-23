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
  
  while (fscanf(archivoCsv, "%m[^,],%d,%d,%m[^\n]\n", &nombre, &ptoHab, &CantItems,&Items) != EOF) {
   tipoJugador *jugador = malloc(sizeof(tipoJugador));
   jugador->nombre = nombre;
   jugador->ptoHab = ptoHab;
   jugador->cantItems = CantItems;
   jugador->Items = createList();

   char *item = strtok(Items, ",");
   while(item != NULL)
   {
    pushBack(jugador->Items, strdup(item));
    item = strtok(NULL, ",");
   }
   insertMap(mapaJugadores, nombre, jugador);
  }
  fclose(archivoCsv);
  while (true) {

    printf("Elije opcion\n");

    printf("1.- Crear Perfil jugador/a \n");
    printf("2.- Mostrar perfil jugador/a\n");
    printf("3.- Agregar item a jugador/a\n");
    printf("4.- Eliminar item a jugador/a\n");
    printf("5.- Agregar puntos de habilidad a jugador/a\n");
    printf("6.- Mostrar jugador@s con item específico\n");
    printf("7.- Deshacer última acción de jugador/a\n");
    printf("8.- Exportar datos de jugadores a archivo de texto\n");
    printf("9.- Cargar datos de jugadores desde un archivo de texto\n");
    scanf("%d", &opcion);
    getchar();
    char* nombre_csv_importar;
    char* nombre_csv_exportar;
    
    switch (opcion) {
  
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:  
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    default:
      return 0;
    }
  }
  
  return 0;
}