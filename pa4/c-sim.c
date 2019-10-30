
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "c-sim.h"

int main(int argc,char* argv[])
{
    int WriteMethod, count, i, j, cache_size, block_size, assoc_value = 0;
    Cache cache;
    FILE *fp;
    char instruction, location[30], fileLine[30];
    char *associativity, *temp;

     if(argc != 7 || strcmp(argv[1], "-h") == 0){
        printf("Error\n");
        return 0;
	 }
	 
	 cache_size = strtol(argv[1], NULL, 10);
	 
	if(strcmp(argv[2], "direct") == 0 || strcmp(argv[2],"assoc") == 0)
    {    
        associativity = argv[2];
    }
    else
    {
        associativity = "assoc";
        temp = malloc(strlen(argv[2]) - 6);
        strncpy(temp, argv[2] + 6, strlen(argv[2]) - 6);
        assoc_value = atoi(temp);
        if(assoc_value < 1)
        {
            printf("Invalid associativity\n");
        }
    }
	block_size = strtol(argv[3], NULL, 10);
	
	if(strcmp(argv[4],"FIFO") == 0)
    {

    }
    else if(strcmp(argv[4], "LRU") == 0)
    {
        fprintf(stderr,"ERROR: not implimented\n");
		return 0;
    }
    else
    {
        fprintf(stderr, "Invalid replacement method.\n FIFO\n LRU\n");
        return 0;
    }
	
	if(strcmp(argv[5],"wt") == 0)
    {
        WriteMethod = 0;   
    }
    else if(strcmp(argv[5],"wb") == 0)
    {
        WriteMethod = 1;
    }
    else
    {
        fprintf(stderr,"Invalid Write Policy.\n wt\n wb\n");
        return 0;
    }
	
    fp=fopen(argv[6],"r");
	
    if(!fp)
    {
        fprintf(stderr,"Error: Could not open file.\n");
        return 0; 
    }
	
    cache = createCache(cache_size, block_size, WriteMethod, associativity, assoc_value);
    
    while(fgets(fileLine, 30, fp) != NULL)
    {
		i = 0;
		while((fileLine[i] != ':'))
        {
			i++;
		}
		instruction = fileLine[i+2];
        j = 0;
		i = i+6;
        while(fileLine[i] != '\0')
        {
            location[j] = fileLine[i];
			i++;
            j++;
        }
        location[j-1] = '\0';
			
		if(instruction =='R')
        {
            readCache(cache, location);
        }
        else if(instruction =='W')
        {
            writeCache(cache, location);
        }
        else
        {
            fprintf(stderr,"ERROR: trouble reading or writting\n");
            fclose(fp);
            destroyCache(cache);           
            return 0;
		}
	}
  
    fclose(fp);
	finalPrint(cache);
    destroyCache(cache);
   return 0;
}

char* binaryString(unsigned int num)
{
    char* temp;
    int i;
    temp = (char*)calloc(1,33);
    temp[32] = '\0';
    for(i = 31; i >= 0; i--)
    {
        temp[i] = num;
    } 
    return temp;
}

unsigned int hexToInt(const char temp[])
{
    unsigned int decimalInt = 0;
    int i;
    for(i = 2; temp[i] != '\0' ;i++)
    {
        if(temp[i] >= '0' && temp[i] <= '9')
        {
            decimalInt = decimalInt + (temp[i] -'0');
            decimalInt = decimalInt * 16;
        }
        else if(temp[i] >= 'a' && temp[i] <= 'f')
        {
            decimalInt = decimalInt + (temp[i] - 'a') + 10;
            decimalInt= decimalInt * 16;
        }
    }
    return decimalInt;
}

int binaryToInt(char *bin){
    int total;
    total = strtol(bin, NULL, 10);
    return total;
}

char* formatBinary(char *temp)
{
    char* bin;
    int i;
    bin = (char*)calloc(1, 33);
    bin[32] = '\0';
    for(i = 0; i < 32; i++)
    {
        bin[i] = temp[i];
    }
    return bin;
}

void finalPrint(Cache cache)
{   
    printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",cache->reads,cache->writes,cache->hits,cache->misses);
    return;
}

Cache createCache(int cache_size,int block_size, int WriteMethod, char *associativity, int assoc_value)
{
    Cache cache;
    int i = 0, lines;
    cache = (Cache)malloc(sizeof(struct Cache_));
    cache->hits = 0;
    cache->misses = 0;
    cache->reads = 0;
    cache->writes = 0;
    cache->WriteMethod = WriteMethod;
    cache->cacheSize = cache_size;
    cache->blockSize = block_size;
    lines = cache_size/block_size;
    cache->numLines = lines;
    cache->blocks = (Block*)malloc(sizeof(Block) * lines);
    while(i<lines)
    {
		cache->blocks[i] = (Block)malloc(sizeof(struct Block_ ));
		i++;
	}
    return cache;
}

void destroyCache(Cache cache)
{
    free(cache->blocks);
    free(cache);
    return;
}

int readCache(Cache cache,char* address)
{
    unsigned int decimalInt;
    char *temp, *stringFormat, *tag, *setIndex;
    int i;
    Block block;
    decimalInt = hexToInt(address);
    temp = binaryString(decimalInt);
    stringFormat = formatBinary(temp);
    tag = (char*)calloc(1,19); 
    tag[18] = '\0'; 
    for(i = 0; i < 18; i++)
    {
        tag[i] = stringFormat[i];
	} 
    setIndex = (char*)calloc(1, 13); 
    setIndex[12] = '\0';
    for(i = 18; i < 30; i++)
    {
        setIndex[i-18] = stringFormat[i];
    } 
    block = cache->blocks[binaryToInt(setIndex)];
    if(block->valid == 1 && strcmp(block->tag,tag) == 0)
    {
        cache->hits++;
        free(tag);
    }
    else
    {        
        cache->misses++;
        cache->reads++;
        if(cache->WriteMethod == 1 && block->dirty == 1)
        {
            cache->writes++;
            block->dirty = 0;
        }
        block->valid = 1;
        free(block->tag);
        block->tag = tag;
    }
    free(temp);
    free(stringFormat);
    free(setIndex);
    return;
}

int writeCache(Cache cache, char* address)
{
    unsigned int decimalInt;
    char *temp, *stringFormat, *tag, *setIndex;
    int i;
    Block block;
    decimalInt = hexToInt(address);
    temp = binaryString(decimalInt);
    stringFormat = formatBinary(temp);
    tag = (char*)calloc(1, 18);
    tag[17] = '\0';
    for(i = 0; i < 17; i++)
    {
        tag[i] = stringFormat[i];
    }
    setIndex = (char*)calloc(1, 13);
    setIndex[12] = '\0'; 
    for(i = 17; i < 30; i++)
    {
        setIndex[i-17] = stringFormat[i];
    }
    block = cache->blocks[binaryToInt(setIndex)];
    if(block->valid == 1 && strcmp(block->tag, tag) == 0)
    {
        block->dirty = 1;
        cache->hits++;
        free(tag);
		if(cache->WriteMethod == 0)
        {
            cache->writes++;
			cache->misses++;
        }
    }
    else
	{
        cache->reads++;
        if(cache->WriteMethod == 0)
        {
            cache->writes++;
        }
        if(cache->WriteMethod == 1 && block->valid == 0)
        {
            cache->writes++;
        }        
        block->dirty = 1;
        block->valid = 1;
		free(block->tag);
        block->tag = tag;
    }
    free(temp);
    free(stringFormat);
    free(setIndex);
    return;
}
