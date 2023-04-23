#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; 
    long capacity; 
    long current;
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  if(map==NULL || key == NULL)
    return;
  
  size_t index = hash(key, map->capacity);
  
  while (map->buckets[index] != NULL && is_equal(map->buckets[index]->key,key)!=1) 
  {
    index = (index + 1) % map->capacity;
    if (index == hash(key, map->capacity))
      return;
  }
  if (map->buckets[index] == NULL || map->buckets[index]->key == NULL) 
  {  
    map->buckets[index] = createPair(key, value);
    map->size++;
    map->current = index;
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    if(map==NULL)
      return;
    Pair** old_buckets = map->buckets;
    long old_capacity = map->capacity;
    map->capacity *= 2;
    map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));
    map->size = 0;
    for (size_t indice = 0; indice < old_capacity; indice++) 
    {
      if (old_buckets[indice] != NULL && old_buckets[indice]->key != NULL) 
        insertMap(map, old_buckets[indice]->key, old_buckets[indice]->value);
    }
    return;
}


HashMap * createMap(long capacity) {
    HashMap *mapaLocal = malloc(sizeof(HashMap));
    mapaLocal->buckets = (Pair **) calloc(sizeof(Pair*),capacity);
    mapaLocal->size=0;
    mapaLocal->capacity = capacity;
    mapaLocal->current = -1;
    return mapaLocal;
}

void eraseMap(HashMap * map,  char * key) {    
  if(map==NULL || key == NULL)
      return;
  
  size_t index = hash(key, map->capacity);
  
  while(map->buckets[index]!=NULL && is_equal(map->buckets[index]->key,key)!=1) 
  {
     index = (index + 1) % map->capacity;
     if (index == hash(key, map->capacity))
      return;
  }
  
  if (map->buckets[index] != NULL && strcmp(map->buckets[index]->key, key) == 0)
  {
    map->buckets[index]->key=NULL;
    map->size--;
  }
  return;
}

Pair * searchMap(HashMap * map,  char * key) {   
  if(map==NULL || key == NULL)
      return NULL;
  
  size_t index = hash(key, map->capacity);
  
   while(map->buckets[index]!=NULL && is_equal(map->buckets[index]->key,key)!=1) 
   {
      index = (index + 1) % map->capacity;
      if (index == hash(key, map->capacity))
        return NULL;
   }

    map->current = index;
    return map->buckets[index];
}

Pair * firstMap(HashMap * map) {
    if(map==NULL)
      return NULL;
    for(size_t indice = 0; indice<=map->capacity ; indice++)
      if(map->buckets[indice]!=NULL && map->buckets[indice]->key !=NULL)
      {
        map->current = indice;
        return map->buckets[indice];
      }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    if(map==NULL)
      return NULL;
    for(size_t indice = map->current+1; indice<=map->capacity ; indice++){
      if(map->buckets[indice]!=NULL && map->buckets[indice]->key !=NULL)
      {
        map->current = indice;
        return map->buckets[indice];
      }
    }
    return NULL;
}
