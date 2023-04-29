#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "stack.h"
#include "list.h"

typedef struct{
  int accion;
  /* accion = 0 es agregar item
     accion = 1 es eliminar item
     accion = 2 es aumentar puntos de habilidad
  */
  char *datoEliminado;
  int puntosHabSumados;
} tipoAccion;

typedef struct {
  char *nombre;  
  int ptoHab;

  int cantItems;
  List * Items;
  //crear tabla hash de items y que los valores sean punteros a jugador
  Stack *acciones; //(se hace pila del tipo de dato tipoAccion, asi se deshace la ultima accion de forma eficiente)
} tipoJugador;

void registrar_Jugador(HashMap *mapaJugador){
  char *items = NULL, *nombre ;
  int ptoHab = 0, CantItems = 0;
  tipoJugador *jugador = malloc(sizeof(tipoJugador));
  printf("\nIngrese el nombre del jugador.\n");
  scanf("%m[^\n]",&nombre);
  if (searchMap(mapaJugador, nombre) == NULL) {
    jugador->nombre = strdup(nombre);
    jugador->ptoHab = 0;
    jugador->cantItems = 0;
    jugador->Items = createList();
    jugador->acciones = stack_create();
    insertMap(mapaJugador, nombre, jugador);
  } else 
    printf("El jugador ya existe en el mapa.\n");
  return;
}

void mostrar_Jugador(HashMap *mapaJugador,char* jugador){
  int cont=1;
  Pair* jugadorBuscado= searchMap(mapaJugador,jugador);
  if(jugadorBuscado != NULL){
    tipoJugador* datosJugador=(tipoJugador*)jugadorBuscado->value;
    printf("Nombre jugador: %s\n",jugadorBuscado->key);
    printf("Puntos de habilidad: %d\n",datosJugador->ptoHab);
    printf("Cantidad de items: %d\n",datosJugador->cantItems);
    printf("Item(s): - ");
      for (char *item = firstList(datosJugador->Items); item != NULL; item = nextList(datosJugador->Items)) { 
        if(cont!=1)
          printf("%-9s- ", " ");
        printf("%s\n",item);
        cont++;
      }
    printf("————————————————————————————————————————\n\n");
  } else{
    printf("El jugador no existe\n");
  }
}

void Agregar_item(HashMap *mapaJugador, HashMap *mapaItems)
{
  char *nombreJugador=NULL, *item=NULL;
  tipoJugador *datoJugador;
  printf("\nIngrese el nombre del jugador: \n");
  scanf("%ms[^\n]",&nombreJugador);
  Pair* jugadorBuscado = searchMap(mapaJugador,nombreJugador);
  getchar();
  
  if(jugadorBuscado != NULL)
  {
    datoJugador = jugadorBuscado->value;
    if(datoJugador->cantItems==8)
    {
      printf("El jugador no puede llevar mas items.\n\n");
      return;
    }
    if(datoJugador->cantItems<=7)
    {
      printf("Ingrese el nombre del item:\n");
      scanf("%m[^\n]", &item);
      getchar();

      Pair *value = searchMap(mapaItems, item);
      if (value == NULL) {
         List *jugadoresConItem = createList();
         insertMap(mapaItems, strdup(item), jugadoresConItem);
         value = searchMap(mapaItems, item);
      }
      tipoAccion *accionJugador = malloc(sizeof(tipoAccion));
      accionJugador->accion = 0;
      accionJugador->datoEliminado = item;
      accionJugador->puntosHabSumados = 0;
      stack_push(datoJugador->acciones, accionJugador );
      pushBack(datoJugador->Items, item);
      pushBack(value->value, strdup(nombreJugador));
      datoJugador->cantItems++;
      return;
    }
   }
   else
    printf("\nEl jugador ingresado no existe\n\n");
}

void Eliminar_item_de_jugador(HashMap *mapaJugador, HashMap *mapaItems)
{
  char *nombreJugador=NULL, *item=NULL;
  tipoJugador *datoJugador;
  printf("\nIngrese el nombre del jugador: \n");
  scanf("%ms[^\n]",&nombreJugador);
  getchar();
  Pair* jugadorBuscado = searchMap(mapaJugador,nombreJugador);
  if(jugadorBuscado != NULL)
  {
    printf("Ingrese el nombre del item:\n");
    scanf("%m[^\n]", &item);
    getchar();
    datoJugador = jugadorBuscado->value;
    Pair *value = searchMap(mapaItems, item);
    if (value == NULL) {
      puts("El item ingresado no existe");
      return;
    }
    else
    {
      for(char * local = firstList(value->value); value != NULL; local = nextList(value->value))
        {
          if (strcmp(local, nombreJugador) == 0)
          {
            tipoAccion *accionJugador = malloc(sizeof(tipoAccion));
            accionJugador->accion = 1;
            accionJugador->datoEliminado = item;
            accionJugador->puntosHabSumados = 0;
            stack_push(datoJugador->acciones, accionJugador);
            for(char *cadenaNombreItem = firstList(datoJugador->Items); cadenaNombreItem != NULL; cadenaNombreItem = nextList(datoJugador->Items))
            {
              if(strcmp(cadenaNombreItem,item) == 0)
              {
                popCurrent(datoJugador->Items);
                datoJugador->cantItems--;
                return;
              }
            }
          }
        }
    }
    
  }
  else
    printf("\nEl jugador ingresado no existe\n\n");
}

void Agregar_puntos_de_habilidad(HashMap *mapaJugador)
{
  char *nombreJugador=NULL;
  int ptoHab;
  tipoJugador *datoJugador;
  printf("\nIngrese el nombre del jugador: \n");
  scanf("%ms[^\n]",&nombreJugador);
  getchar();
  Pair* jugadorBuscado = searchMap(mapaJugador,nombreJugador);
  if(jugadorBuscado != NULL)
  {
    printf("\nIngrese la cantidad de puntos de habilidad: \n");
    scanf("%d", &ptoHab);
    datoJugador = jugadorBuscado->value;
    datoJugador->ptoHab += ptoHab;
    tipoAccion *accionJugador = malloc(sizeof(tipoAccion));
    accionJugador->accion = 2;
    accionJugador->datoEliminado = NULL;
    accionJugador->puntosHabSumados = ptoHab;
    stack_push(datoJugador->acciones, accionJugador);
  }
  else
    printf("\nEl jugador ingresado no existe\n\n");
}

void Deshacer_última_acción(HashMap *mapaJugador, HashMap *mapaItems){
  tipoJugador *datoJugador;
  char *nombreJugador = NULL;
  
  printf("Ingrese el nombre del jugador \n");
  scanf("%ms[^\n]",&nombreJugador);
  Pair *jugadorBuscado = searchMap(mapaJugador, nombreJugador);
  if(jugadorBuscado != NULL)
  {
    datoJugador = jugadorBuscado->value;
    if(datoJugador->acciones == NULL){
      printf("No hay acciones para deshacer. \n");
      return;
    }
    
    tipoAccion *ultimaAccion = stack_pop(datoJugador->acciones);
    if(ultimaAccion!=NULL)
    {
  
    if(ultimaAccion->accion == 0){
      char *nombreItem = ultimaAccion->datoEliminado;
      Pair *itemBuscado = searchMap(mapaItems, nombreItem);
      popBack(datoJugador->Items);
      datoJugador->cantItems--;
      printf("Se deshizo la accion de agregar el item %s \n", nombreItem);
      
    }  else if(ultimaAccion->accion == 1){
      char *nombreItem = ultimaAccion->datoEliminado;
      pushBack(datoJugador->Items,nombreItem);
      datoJugador->cantItems++;
      printf("Se deshizo la accion de eliminar el item %s \n", nombreItem);
      
      } else if (ultimaAccion->accion == 2){
      int puntosHabRestar = ultimaAccion->puntosHabSumados;
      datoJugador->ptoHab -= puntosHabRestar;
      }
      return;
    }
    else
      printf("\nEl jugador no tiene acciones previas\n\n");
    return;
  }
  else
    printf("\nEl jugador ingresado no existe\n\n");
  
}

void Mostrar_jugadores_con_item_específico(HashMap *mapaItems)
{
  char *nombreItem=NULL;
  printf("\nIngrese el nombre del item: \n");
  scanf("%ms[^\n]",&nombreItem);
  getchar();
  Pair* jugadoresBuscados = searchMap(mapaItems,nombreItem);
  if(jugadoresBuscados != NULL)
  {
    for(char *jugador = firstList(jugadoresBuscados->value); jugador != NULL; jugador = nextList(jugadoresBuscados->value))
    {
      printf("- %s\n",jugador);
    }
  }
  else
    printf("\nEl item no existe.\n\n");
  
}

void Exportar_datos_de_jugadores_a_archivo_de_texto(char* nombre_archivo, HashMap* mapaJugadores) {
    tipoJugador* local = NULL;
    FILE* archivo = fopen(nombre_archivo, "w");
    fprintf(archivo, "Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");
    
    Pair* datoJugador = firstMap(mapaJugadores);
    while (datoJugador != NULL) {
        local = datoJugador->value;
        if(local==NULL)
          break;
        fprintf(archivo, "%s,%d,%d,", local->nombre, local->ptoHab, local->cantItems);

        char* item = firstList(local->Items);
        for (int i = 0; i < local->cantItems; i++)
        {
          if(i == local->cantItems - 1)
            fprintf(archivo, "%s", item); 
          else
            fprintf(archivo, "%s,", item); 
          item = nextList(local->Items);
        }
        
        fprintf(archivo, "\n");
        datoJugador = nextMap(mapaJugadores);
    }

    printf("\nArchivo exportado.\n");
    printf("————————————————————————————————————————————————————————————\n\n");
    fclose(archivo);
}

int main() {
   HashMap *mapaJugadores = createMap((long)2000);
  //se pone 2000 de capacidad para tener el doble de capacidad que la totalidad de jugadores 
  char caracter[100];
  HashMap *mapaItems = createMap((long) 100);
  FILE *archivoCsv = fopen("player100.csv", "r"); // abre el archivo CSV

  fgets(caracter, 99, archivoCsv);
  int ptoHab = 0, CantItems = 0,opcion = 0;
  char *nombre = NULL, *Items = NULL;
  
   while (fscanf(archivoCsv, "%m[^,],%d,%d,%m[^\n]\n", &nombre, &ptoHab, &CantItems, &Items) != EOF) {
   tipoJugador *jugador = malloc(sizeof(tipoJugador));
   jugador->nombre = strdup(nombre);
   jugador->ptoHab = ptoHab;
   jugador->cantItems = CantItems;
   jugador->Items = createList();
   jugador->acciones = stack_create();
   char *item = strtok(Items, ",");
   while (item != NULL) {
      Pair *value = searchMap(mapaItems, item);
      if (value == NULL) {   
         List *jugadoresConItem = createList();
         insertMap(mapaItems, strdup(item), jugadoresConItem);
         value = searchMap(mapaItems, item);
      }
      pushBack(jugador->Items, strdup(item));
      pushBack(value->value, strdup(nombre));
     
      item = strtok(NULL, ",");
   }
  insertMap(mapaJugadores, nombre, jugador);
}
  fclose(archivoCsv);
  
  while (true) {

    printf("Elija opcion\n");

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
    char* nombre_txt_importar;
    char* nombre_txt_exportar;
    char* jugadorAbuscar;
    
   switch (opcion) {
  
    case 1:
      registrar_Jugador(mapaJugadores);
      break;
    case 2:printf("Escriba el nombre del Jugador a buscar\n");
      scanf("%m[^\n]",&jugadorAbuscar);
      mostrar_Jugador(mapaJugadores, jugadorAbuscar);
      break;
    case 3:
      Agregar_item(mapaJugadores, mapaItems);
      break;
    case 4:
      Eliminar_item_de_jugador(mapaJugadores, mapaItems);
      break;
    case 5:
      Agregar_puntos_de_habilidad(mapaJugadores);
      break;
    case 6:  
      Mostrar_jugadores_con_item_específico(mapaItems);
      break;
    case 7:
      Deshacer_última_acción(mapaJugadores ,mapaItems);
      break;
    case 8:
      printf("\n————————————————————————————————————————————————————————————\n");
      printf("Ingrese el nombre del archivo, introduzca el formato (.txt)\n");
      scanf("%m[^\n]",&nombre_txt_exportar);
      getchar();

    if (strstr(nombre_txt_exportar,".txt")==0) 
    {
      printf("El formato del archivo %s es incorrecto\n", nombre_txt_exportar);
      printf("————————————————————————————————————————————————————————————\n\n");
      break;
    }

      Exportar_datos_de_jugadores_a_archivo_de_texto(nombre_txt_exportar, mapaJugadores);
      break;
    case 9:
     break;
  }
  return 0;
}