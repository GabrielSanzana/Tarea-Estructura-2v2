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

void registrar_Jugador(HashMap *mapaJugador){
  char *items = NULL, *nombre ;
  int ptoHab = 0, CantItems = 0;
  tipoJugador *jugador = malloc(sizeof(tipoJugador));
  scanf("%m[^,],",&nombre);
  jugador->nombre = strdup(nombre);
  jugador->ptoHab = 0;
  jugador->Items = createList();
  jugador->cantItems = 0;
  insertMap(mapaJugador, nombre, jugador);    
}

void Exportar_datos_de_jugadores_a_archivo_de_texto(char* nombre_archivo, HashMap* mapaJugadores) {
    tipoJugador* local = NULL;
    FILE* archivo = fopen(nombre_archivo, "w");
    printf("\n——————————————————————————————————————————————\n");
    fprintf(archivo, "Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");

    Pair* pair = firstMap(mapaJugadores);
    while (pair != NULL) {
        local = pair->value;
        fprintf(archivo, "%s,%d,%d,", local->nombre, local->ptoHab, local->cantItems);

        char* item = firstList(local->Items);
        while (item != NULL) {
            fprintf(archivo, "%s", item);
            if (nextList(local->Items) == NULL) {
                break;
            } else {
                fprintf(archivo, ",");
            }
            item = nextList(local->Items);
        }

        fprintf(archivo, "\n");
        pair = nextMap(mapaJugadores);
    }

    printf("Archivo exportado.\n");
    printf("——————————————————————————————————————————————\n\n");
    fclose(archivo);
}


int main() {
   HashMap *mapaJugadores = createMap((long)2000);
  //se pone 2000 de capacidad para tener el doble de capacidad que la totalidad de jugadores 
  char caracter[100];

  FILE *archivoCsv = fopen("players10.csv", "r"); // abre el archivo CSV
  fgets(caracter, 99, archivoCsv);
  int ptoHab = 0, CantItems = 0,opcion = 0;
  char *nombre = NULL, *Items = NULL;
  
  while (fscanf(archivoCsv, "%m[^,],%d,%d,%m[^\n]\n", &nombre, &ptoHab, &CantItems,&Items) != EOF) {
   tipoJugador *jugador = malloc(sizeof(tipoJugador));
   jugador->nombre = strdup(nombre);
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
      printf("\nIngrese el nombre del archivo, introduzca el formato (.txt)\n");
      scanf("%m[^\n]",&nombre_csv_exportar);
      getchar();
      printf("\n——————————————————————————————————————————————\n");
      
    if (strstr(nombre_csv_exportar,".txt")==0) 
    {
      printf("El formato del archivo %s es incorrecto\n", nombre_csv_exportar);
      printf("——————————————————————————————————————————————\n\n");
      break;
    }
      
      Exportar_datos_de_jugadores_a_archivo_de_texto(nombre_csv_exportar, mapaJugadores);
      break;
    case 9:
      break;
    default:
      return 0;
    }
  }
  
  return 0;
}