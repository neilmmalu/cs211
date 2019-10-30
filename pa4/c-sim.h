#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Cache_* Cache;
typedef struct Block_* Block;

struct Block_ {
    int valid;
    int dirty;
    char *tag;
};

struct Cache_ {
    int hits;
    int misses;
    int reads;
    int writes;
    int cacheSize;
    int blockSize;
    int numLines;
    int WriteMethod;
    char *associativity;
    int assoc_value;
    Block *blocks;    
};

unsigned int hexToInt(const char temp[]);
char* binaryString(unsigned int num);
char* formatBinary(char *temp);
int binaryToInt(char *bin);
void finalPrint(Cache cache);
Cache createCache(int cache_size,int block_size, int WriteMethod, char *associativity, int assoc_value);
void destroyCache(Cache cache);
int readCache(Cache cache,char* address);
int writeCache(Cache cache,char* address);