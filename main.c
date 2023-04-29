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
//Se crea la struct que representan las acciones del usuario que se pueden deshacer, se utilizan solo 3 datos para maximizar la eficiencia.

typedef struct {
  char *nombre;  
  int ptoHab;

  int cantItems;
  List * Items;
  //Crear tabla hash de items y que los valores sean punteros a jugador
  Stack *acciones; //Se hace pila del tipo de dato tipoAccion, asi se deshace la ultima accion de forma eficiente
} tipoJugador;
  //Se utiliza esta struct para representar los datos del jugador

//Se crea la función registrar_Jugador, almacenando los datos del jugador ingresado en el mapa de jugadores.
void registrar_Jugador(HashMap *mapaJugador){
  printf("\n————————————————————————————————————————————————————————————");
  // Declaración de variables
  char *items = NULL, *nombre ;
  int ptoHab = 0, CantItems = 0;
  // Creación de un nuevo jugador
  tipoJugador *jugador = malloc(sizeof(tipoJugador));
  printf("\nIngrese el nombre del jugador: \n");
  scanf("%m[^\n]",&nombre);

  if (searchMap(mapaJugador, nombre) == NULL) {
    // Si el jugador no existe, se inicializan sus atributos
    jugador->nombre = strdup(nombre);
    jugador->ptoHab = 0;
    jugador->cantItems = 0;
    jugador->Items = createList(); // Se crea una nueva lista para los items del jugador
    jugador->acciones = stack_create(); // Se crea una pila para las acciones del jugador
    insertMap(mapaJugador, nombre, jugador); // Se inserta al jugador en el mapa
    printf("\nEl jugador '%s' ha sido registrado exitosamente.\n", nombre);
  } else 
    printf("\nEl jugador '%s' ya existe en el mapa.\n", nombre);
  printf("————————————————————————————————————————————————————————————\n\n");
  return; // Finaliza la función
}

//Esta función muestra los datos del jugador, recibiendo de argumento el mapa de jugadores y el nombre del jugador a buscar.
void mostrar_Jugador(HashMap *mapaJugador,char* jugador){
  int cont=1;
  Pair* jugadorBuscado= searchMap(mapaJugador,jugador);
  if(jugadorBuscado != NULL){
    tipoJugador* datosJugador=(tipoJugador*)jugadorBuscado->value;
    printf("Nombre jugador: %s\n",jugadorBuscado->key);
    printf("Puntos de habilidad: %d\n",datosJugador->ptoHab);
    printf("Cantidad de items: %d\n",datosJugador->cantItems);
    printf("Item(s): - ");
    //Este ciclo for muestra los items del jugador.
    for (char *item = firstList(datosJugador->Items); item != NULL; item = nextList(datosJugador->Items)) 
    {
      if(cont!=1)
        printf("%-9s- ", " ");
      printf("%s\n",item);
      cont++;
    }
  } 
  else
    printf("\nEl jugador '%s' no existe.", jugador);
  if(cont!=1)
    printf("————————————————————————————————————————————————————————————\n\n");
  else
    printf("\n————————————————————————————————————————————————————————————\n\n");
}

//Esta función agrega items a un jugador
void Agregar_item(HashMap *mapaJugador, HashMap *mapaItems)
{
  printf("\n————————————————————————————————————————————————————————————");
  char *nombreJugador=NULL, *item=NULL;
  tipoJugador *datoJugador;
  printf("\nIngrese el nombre del jugador: \n");
  scanf("%ms[^\n]",&nombreJugador);
  Pair* jugadorBuscado = searchMap(mapaJugador,nombreJugador);
  getchar();
  //Se busca el jugador en el mapa de jugadores
  if(jugadorBuscado != NULL)
  {
    datoJugador = jugadorBuscado->value;
    if(datoJugador->cantItems==8)
    {
      //Si el jugador tiene más items de los que puede llevar, no se pueden agregar mas items.
      printf("\nEl jugador no puede llevar más items.");
      printf("\n————————————————————————————————————————————————————————————\n\n");
      return;
    }
    if(datoJugador->cantItems<=7)
    {
      printf("\nIngrese el nombre del item:\n");
      scanf("%m[^\n]", &item);
      getchar();

      Pair *value = searchMap(mapaItems, item);
      if (value == NULL) {
         List *jugadoresConItem = createList();
         insertMap(mapaItems, strdup(item), jugadoresConItem);
         value = searchMap(mapaItems, item);
        //Si no existe el item escrito por el usuario, se agrega dicho item en mapa de items
      }
      tipoAccion *accionJugador = malloc(sizeof(tipoAccion));
      accionJugador->accion = 0;
      accionJugador->datoEliminado = item;
      accionJugador->puntosHabSumados = 0;
      stack_push(datoJugador->acciones, accionJugador );
      pushBack(datoJugador->Items, item);
      pushBack(value->value, strdup(nombreJugador));
      datoJugador->cantItems++;
      //Se modifica el struct del jugador.
      printf("\nItem '%s' ingresado correctamente en el jugador '%s'.\n", item, nombreJugador);
      printf("————————————————————————————————————————————————————————————\n\n");
      return;
    }
   }
   else
    printf("\nEl jugador '%s' no existe.", nombreJugador);
   printf("\n————————————————————————————————————————————————————————————\n\n");
}

//Esta función elimina items a un jugador
void Eliminar_item_de_jugador(HashMap *mapaJugador, HashMap *mapaItems)
{
  printf("\n————————————————————————————————————————————————————————————");
  char *nombreJugador=NULL, *item=NULL;
  tipoJugador *datoJugador;
  printf("\nIngrese el nombre del jugador: \n");
  scanf("%ms[^\n]",&nombreJugador);
  getchar();
  Pair* jugadorBuscado = searchMap(mapaJugador,nombreJugador); // Busca el jugador en el mapa
  if(jugadorBuscado != NULL)
  {
    printf("\nIngrese el nombre del item:\n");
    scanf("%m[^\n]", &item);
    getchar();
    datoJugador = jugadorBuscado->value;
    Pair *value = searchMap(mapaItems, item); // Busca el item en el mapa de items
    if (value == NULL) {
      printf("\nEl item '%s' no existe.\n", item);
      printf("————————————————————————————————————————————————————————————\n\n");
      return;
    }
    else
    {
      bool encontrado = false;
      for(char * local = firstList(value->value); local != NULL; local = nextList(value->value))
      {
        if (strcmp(local, nombreJugador) == 0)
        {  
          tipoAccion *accionJugador = malloc(sizeof(tipoAccion)); // Agrega la acción a la pila de acciones del jugador
          accionJugador->accion = 1;
          accionJugador->datoEliminado = item;
          accionJugador->puntosHabSumados = 0;
          stack_push(datoJugador->acciones, accionJugador);
          
          // Elimina el item de la lista de items del jugador
          for(char *cadenaNombreItem = firstList(datoJugador->Items); cadenaNombreItem != NULL; cadenaNombreItem = nextList(datoJugador->Items))
          {
            if(strcmp(cadenaNombreItem,item) == 0)
            {
              popCurrent(datoJugador->Items);
              datoJugador->cantItems--;
              printf("\nItem '%s' eliminado correctamente del jugador '%s'.", item, nombreJugador);
              break;
            }
          }
          popCurrent(value->value);
          encontrado = true;
          break;
        }
      }
      if (!encontrado) {
        printf("El jugador '%s' no tiene el item '%s'.\n", nombreJugador, item);
        printf("\n————————————————————————————————————————————————————————————\n\n");
        return;
      }
    }
    
  }
  else
    printf("\nEl jugador '%s' no existe.", nombreJugador);
  printf("\n————————————————————————————————————————————————————————————\n\n");
}


void Agregar_puntos_de_habilidad(HashMap *mapaJugador)
{
  printf("\n————————————————————————————————————————————————————————————");
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
    printf("\nSe han agregado %d puntos de habilidad al jugador '%s'.", ptoHab, nombreJugador);
    tipoAccion *accionJugador = malloc(sizeof(tipoAccion)); // Crear un objeto de tipo tipoAccion para registrar la acción del jugador
    accionJugador->accion = 2; // Asignar el valor correspondiente a la acción de sumar puntos de habilidad
    accionJugador->datoEliminado = NULL;
    accionJugador->puntosHabSumados = ptoHab;
    stack_push(datoJugador->acciones, accionJugador); // Agregar la acción a la pila de acciones del jugador
  }
  else
    printf("\nEl jugador '%s' no existe.", nombreJugador);
  printf("\n————————————————————————————————————————————————————————————\n\n");
}

void Deshacer_última_acción(HashMap *mapaJugador, HashMap *mapaItems){
  tipoJugador *datoJugador;
  char *nombreJugador = NULL;
  printf("\n————————————————————————————————————————————————————————————");
  printf("\nIngrese el nombre del jugador \n");
  scanf("%ms[^\n]",&nombreJugador);
  Pair *jugadorBuscado = searchMap(mapaJugador, nombreJugador); // buscamos en el mapa de jugadores el jugador ingresado
  
  if(jugadorBuscado != NULL)
  {
    datoJugador = jugadorBuscado->value;
    
    // Si el jugador no tiene acciones previas, se informa y se sale de la función
    if(datoJugador->acciones == NULL){
      printf("No hay acciones para deshacer. \n");
      return;
    }

    // Se desapila la última acción realizada por el jugador
    tipoAccion *ultimaAccion = stack_pop(datoJugador->acciones);
    
    if(ultimaAccion!=NULL)
    {
  
    if(ultimaAccion->accion == 0){ // Si la última acción fue agregar un item
      char *nombreItem = ultimaAccion->datoEliminado;
      Pair *itemBuscado = searchMap(mapaItems, nombreItem);
      for(char * local = firstList(itemBuscado->value); local != NULL; local = nextList(itemBuscado->value))
      {
        if (strcmp(local, nombreJugador) == 0)
        {
          popCurrent(itemBuscado->value);
          break;
        }
      }
      popBack(datoJugador->Items); // Se elimina el item del inventario del jugador y se decrementa la cantidad de items que posee
      
      datoJugador->cantItems--;
      printf("\nSe deshizo la accion de agregar el item '%s' \n", nombreItem);
      
    }  else if(ultimaAccion->accion == 1){ // Si la última acción fue eliminar un item
      char *nombreItem = ultimaAccion->datoEliminado;
      pushBack(datoJugador->Items,nombreItem);  // Se agrega el item al inventario del jugador y se incrementa la cantidad de items que posee
      datoJugador->cantItems++;
      Pair *itemBuscado = searchMap(mapaItems, nombreItem);
      pushBack(itemBuscado->value,datoJugador->nombre);
      printf("\nSe deshizo la accion de eliminar el item '%s' \n", nombreItem);
      
      } else if (ultimaAccion->accion == 2){ // Si la última acción fue sumar puntos de habilidad
      int puntosHabRestar = ultimaAccion->puntosHabSumados;
      datoJugador->ptoHab -= puntosHabRestar; // Se restan los puntos de habilidad sumados previamente
      printf("\nSe deshizo la accion de agregar puntos de habilidad\n");
      }
      printf("————————————————————————————————————————————————————————————\n\n");
      return;
    }
    else
      printf("\nEl jugador no tiene acciones previas\n");
    printf("————————————————————————————————————————————————————————————\n\n");
    return;
  }
  else
    printf("\nEl jugador '%s' no existe.\n", nombreJugador);
  printf("————————————————————————————————————————————————————————————\n\n");
}

void Mostrar_jugadores_con_item_específico(HashMap *mapaItems)
{
  printf("\n————————————————————————————————————————————————————————————");
  char *nombreItem=NULL;
  printf("\nIngrese el nombre del item: \n");
  scanf("%ms[^\n]",&nombreItem);
  getchar();
  Pair* jugadoresBuscados = searchMap(mapaItems,nombreItem); // buscamos en el mapa de items el item ingresado
  if(jugadoresBuscados != NULL)
  {
    printf("\n");
    for(char *jugador = firstList(jugadoresBuscados->value); jugador != NULL; jugador = nextList(jugadoresBuscados->value)) // recorremos la lista de jugadores que tienen el item buscado
    {
      printf("- %s\n",jugador);
    }
  }
  else
    printf("\nEl item '%s' no existe.\n", nombreItem);
  printf("————————————————————————————————————————————————————————————\n\n");
}

void Exportar_datos_de_jugadores_a_archivo_de_texto(char* nombre_archivo, HashMap* mapaJugadores) {
    tipoJugador* local = NULL;
    FILE* archivo = fopen(nombre_archivo, "w");
    fprintf(archivo, "Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");

    // Recorrer los jugadores en el mapa y escribir sus datos en el archivo
    Pair* datoJugador = firstMap(mapaJugadores);
    while (datoJugador != NULL) {
        local = datoJugador->value;
        if(local==NULL)
          break;
        // Escribir nombre, puntos de habilidad y cantidad de items en el archivo
        fprintf(archivo, "%s,%d,%d,", local->nombre, local->ptoHab, local->cantItems);

        // Recorrer los items del jugador y escribirlos en el archivo
        char* item = firstList(local->Items);
        for (int i = 0; i < local->cantItems; i++)
        {
          // Escribir el último item sin coma al final
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

void importar_paciente_desde_un_archivo_Txt(char* nombre_archivo, HashMap* mapaJugadores,HashMap* mapaItems){
  char caracter[100];
  FILE *archivoTxt = fopen(nombre_archivo, "r");
  if (archivoTxt == NULL) 
    {
      printf("\n——————————————————————————————————————————————————————————————————————————\n");
      printf("El archivo %s no existe en el directorio actual o esta mal escrito.\n", nombre_archivo);
      printf("——————————————————————————————————————————————————————————————————————————\n\n");
      return;
    }
  fgets(caracter, 99, archivoTxt); // Lee la primera línea (cabecera) del archivo
  int ptoHab = 0, CantItems = 0;
  char *nombre = NULL, *Items = NULL;
  
  // Lee los datos de cada jugador del archivo mientras no llegue al final
  while (fscanf(archivoTxt, "%m[^,],%d,%d,%m[^\n]\n", &nombre, &ptoHab, &CantItems, &Items) != EOF) {
   tipoJugador *jugador = malloc(sizeof(tipoJugador));
   jugador->nombre = strdup(nombre);
   jugador->ptoHab = ptoHab;
   jugador->cantItems = CantItems;
   jugador->Items = createList();
   jugador->acciones = stack_create();
   char *item = strtok(Items, ",");
   while (item != NULL) {
      Pair *value = searchMap(mapaItems, item);
     
      // Si el ítem no existe en el mapa de ítems, lo agrega y crea una nueva lista de jugadores con ese ítem
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
  printf("\nArchivo importado.\n");
  fclose(archivoTxt);
}


int main() {
   HashMap *mapaJugadores = createMap((long)2000);
  //se pone 2000 de capacidad para tener el doble de capacidad que la totalidad de jugadores 
  char caracter[100];
  HashMap *mapaItems = createMap((long) 100);
  FILE *archivoCsv = fopen("players1000.csv", "r"); // abre el archivo CSV

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
    case 2:
      printf("\n————————————————————————————————————————————————————————————\n");
      printf("Escriba el nombre del Jugador a buscar\n");
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
      printf("\nEl formato del archivo '%s' es incorrecto.\n", nombre_txt_exportar);
      printf("————————————————————————————————————————————————————————————\n\n");
      break;
    }

      Exportar_datos_de_jugadores_a_archivo_de_texto(nombre_txt_exportar, mapaJugadores);
      break;
    case 9:
      printf("\n————————————————————————————————————————————————————————————\n");
      printf("Ingrese el nombre del archivo, introduzca el formato (.txt)\n");
      scanf("%m[^\n]",&nombre_txt_importar);
      getchar();
      if (strstr(nombre_txt_importar,".txt")==0)
      {
        printf("\nEl formato del archivo '%s' es incorrecto.\n", nombre_txt_importar);
        printf("————————————————————————————————————————————————————————————\n\n");
        break;
      }
      importar_paciente_desde_un_archivo_Txt(nombre_txt_importar, mapaJugadores,mapaItems);
      printf("————————————————————————————————————————————————————————————\n\n");
      break;
    default:
      return 0;
    }
  }
  return 0;
}