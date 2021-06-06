#ifndef MAP_H
#define MAP_H

typedef struct Pair Pair;
typedef struct HashMap HashMap;

HashMap * createMap(long capacity);
void insertMap(HashMap * map, char * key, void * value);
void eraseMap(HashMap * map,  char * key);
void * searchMap(HashMap * map,  char * key);
void * firstMap(HashMap * map);
void * nextMap(HashMap * map);
char* get_key(HashMap* map);
#endif /* MAP_h */
