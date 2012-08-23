#include <stdio.h>
#include <string.h>
#include <malloc.h>
 

/* Buffer Size */
#define BUFFER_SIZE  1024

#pragma pack(1)
typedef struct
{
   unsigned int *keys[BUFFER_SIZE];   /**< Element of ciruclar buffer */
   unsigned int writePointer; /**< write pointer */
   unsigned int readPointer;  /**< read pointer */
   unsigned int size;         /**< size of circular buffer */
} CircularBuffer;
 
/**< Init Ciruclar Buffer */
CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size)
{       
        unsigned int sz =  sizeof(CircularBuffer);
        *pQue = (CircularBuffer*) malloc(sz);
        //unsigned int *(*(*pQue)->keys)) = (unsigned int **)calloc(size,sizeof(unsigned int *));
        if(*pQue)
        {
            printf("Init CircularBuffer: keys[%d] QUEUE = %d ### CB SIZE = %d \n", size, sz,sizeof(CircularBuffer));
            (*pQue)->size = size;
            (*pQue)->writePointer = 0;
            (*pQue)->readPointer  = 0;
        }
        return *pQue;
}
 
inline int CircularBufferIsFull(CircularBuffer* que)
{
     return ((que->writePointer + 1) % que->size == que->readPointer); 
}
 
inline int CircularBufferIsEmpty(CircularBuffer* que)
{
     return ((que->readPointer + 1) % que->size == que->writePointer); 
}
 
inline int CircularBufferWrite(CircularBuffer* que, void* k)
{
        int isFull = 0;
        isFull = CircularBufferIsFull(que);
        que->keys[que->writePointer] = (unsigned int *)calloc(188,sizeof(char));
        //*que->keys[que->writePointer] = k;
        memcpy(que->keys[que->writePointer],k,188);
        que->writePointer++;
        que->writePointer %= que->size;

        return isFull;
}
 
inline int CircularBufferRead(CircularBuffer* que, void* pK)
{
        int isEmpty = 0;
        isEmpty = CircularBufferIsEmpty(que);
        //*pK = *que->keys[que->readPointer];
        memcpy(pK,que->keys[que->readPointer],188);
        que->readPointer++;
        que->readPointer %= que->size;
        
        return(isEmpty);
}
 
int main(int argc, char *argv[])
{
        CircularBuffer* que;
        unsigned int a = 0,*p=NULL;
        int isEmpty;
        p = (unsigned int *)calloc(188,sizeof(char));

        CircularBufferInit(&que, BUFFER_SIZE);
        do{
          a += 1;
         }while(!CircularBufferWrite(que, &a));
 
        do {
            isEmpty = CircularBufferRead(que, p); 
            printf("%02d ", *p);
        } while (!isEmpty);
        printf("\n");
        
        free(p);
        free(que);
        return 0;
}
