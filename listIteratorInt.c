
/*
  listIteratorInt.c ... list Iterator ADT implementation
  Written by Daisong Yu(z5098539)
  Date: 4.9
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

typedef struct Node *node;

struct Node {

    int value;
    node next;
    node prev;

};

typedef struct IteratorIntRep {

    node head;
    node prevNode;
    node nextNode;
    node lastReturn;
    node tempPrev; // use for find next and find previous
    node tempNext;

} IteratorIntRep;


//function for testing

void show(IteratorInt it){

    if(it->prevNode != NULL){
        printf("value of prevNode is %d\n",it->prevNode->value);
    }else{
        printf("prevNode is NULL\n");
    }

    if(it->nextNode != NULL){
        printf("value of nextNode is %d\n",it->nextNode->value);
    }else{
        printf("nextNode is NULL\n");
    }

}


//----------------------------------------------------------------------


IteratorInt IteratorIntNew(){

    IteratorIntRep *newIterator = malloc(sizeof(IteratorIntRep));

    newIterator->prevNode = NULL;
    newIterator->nextNode = NULL;
    newIterator->lastReturn = NULL;
    newIterator->head = NULL;
    newIterator->tempNext = NULL;
    newIterator->tempPrev = NULL;

    return newIterator;
}

void reset(IteratorInt it){

    if(it->prevNode == NULL){ // if cursor already at the beginning of the list
	//do nothing
    }else{
        it->nextNode = it->head;
        it->prevNode = NULL;
    }
}


int add(IteratorInt it, int v){

  node newNode = malloc(sizeof(struct Node));

  int ifadd = 0;

  if(it->head == NULL){ //if there is no elements in the list

        it->prevNode = newNode;
        it->nextNode = NULL;
        it->head = newNode;
        it->prevNode->value = v;
        ifadd = 1;

  }else{

       if(it->nextNode == NULL){ //if cursor at the end of the list

            it->prevNode->next = newNode;
            it->prevNode->next->prev = it->prevNode;
            it->prevNode = it->prevNode->next;
            it->nextNode = NULL;
            it->prevNode->value = v;
            ifadd = 1;

       }else if(it->prevNode == NULL){ //if cursor at the beginning of the list

            it->nextNode->prev = newNode;
            it->nextNode->prev->next = it->nextNode;
            it->prevNode = it->nextNode->prev;
            it->head = it->prevNode;
            it->prevNode->value = v;
            ifadd = 1;

       }else{   //if cursor at the middle of the list

            it->nextNode->prev = newNode;
            it->nextNode->prev->next = it->nextNode;
            it->nextNode->prev->prev = it->prevNode;
            it->prevNode->next = it->nextNode->prev;
            it->prevNode = it->nextNode->prev;
            it->prevNode->value = v;
            ifadd = 1;
       }

  }

  return ifadd;

}


int hasNext(IteratorInt it){

    //int hasNext = 0;

    if(it->nextNode != NULL){
        return 1;
    }else{
        return 0;
    }
// changed
}

int hasPrevious(IteratorInt it){


    if(it->prevNode != NULL){
        return 1;
    }else{
        return 0;
    }
}


int *next(IteratorInt it){

    int *pNext = NULL;

    if(it->nextNode == NULL){
        return pNext;
    }else{

        if(it->nextNode->next == NULL){

            pNext = &it->nextNode->value;
            it->lastReturn = it->nextNode;
            it->prevNode = it->nextNode;
            it->nextNode = NULL;
            return pNext;

        }else{

            pNext = &it->nextNode->value;
            it->lastReturn = it->nextNode;
            it->prevNode = it->nextNode;
            it->nextNode = it->nextNode->next;
            return pNext;

        }
    }

}

int *previous(IteratorInt it){

    int *pPrev = NULL;

    if(it->prevNode == NULL){

        return pPrev;

    }else{

        if(it->prevNode->prev == NULL){

            pPrev = &it->prevNode->value;
            it->lastReturn = it->prevNode;
            it->nextNode = it->prevNode;
            it->prevNode = NULL;
            return pPrev;

        }else{

            pPrev = &it->prevNode->value;
            it->lastReturn = it->prevNode;
            it->nextNode = it->prevNode;
            it->prevNode = it->prevNode->prev;
            return pPrev;
        }
    }

}


int delete(IteratorInt it){

    node temp = it->lastReturn;
    int ifDelete;

    if(it->lastReturn == NULL){

        ifDelete = 0;

    }else{

        if(it->lastReturn->prev == NULL){  //lastReturn is the first node of the list

            if(it->prevNode == NULL){//prevNode is NULL

                it->nextNode = it->nextNode->next;
                it->nextNode->prev = NULL;
                it->head = it->nextNode;
                free(temp);
		it->lastReturn = NULL; // last return value has been deleted
                ifDelete = 1;
            }else{
                it->prevNode = NULL;
                it->nextNode->prev = NULL;
                it->head = it->nextNode;
                free(temp);
		it->lastReturn = NULL;
                ifDelete = 1;
            }

        }else if(it->lastReturn->next == NULL){//lastReturn is the last node in the list

            if(it->nextNode == NULL){
                it->prevNode = it->prevNode->prev;
                it->prevNode->next = NULL;
                free(temp);
		it->lastReturn = NULL;
                ifDelete = 1;
            }else{
                it->nextNode = NULL;
                it->prevNode->next = NULL;
                free(temp);
		it->lastReturn = NULL;
                ifDelete = 1;
            }
        }else{ //lastReturn at the middle of the list

            if(it->nextNode == it->lastReturn){ //lastReturn by findnext or next
                it->prevNode->next = it->nextNode->next;
                it->nextNode->next->prev = it->prevNode;
                it->nextNode = it->nextNode->next;
                free(temp);
		it->lastReturn = NULL;
                ifDelete = 1;

            }else if(it->prevNode == it->lastReturn){ //lastReturn by findprev or prev
                it->nextNode->prev = it->prevNode->prev;
                it->prevNode->prev->next = it->nextNode;
                it->prevNode = it->prevNode->prev;
                free(temp);
		it->lastReturn = NULL;
                ifDelete = 1;

            }
        }
    }

    return ifDelete;  //changed
}


int set(IteratorInt it, int v){

    int ifset = 0;

    if(it->lastReturn == NULL){
        return ifset;
    }else{

        it->lastReturn->value = v;
        ifset = 1;
    }


    return ifset;
}

int *findNext(IteratorInt it, int v){

    int *pFindNext = NULL;
    int ifFind = 0;
    it->tempNext = it->nextNode;
    it->tempPrev = it->prevNode;

    if(it->nextNode == NULL){
        pFindNext = 0;
    }else{

        while(ifFind == 0 && it->nextNode != NULL){

                if(it->prevNode->value == v){ // move until cursor before the value that wanted

                    pFindNext = &it->prevNode->value;
                    it->lastReturn = it->prevNode;
                    ifFind = 1;
                    printf("enter if\n");//DDD

                }else{
                    printf("enter else\n");
                    it->prevNode = it->nextNode;
                    it->nextNode = it->nextNode->next;
                    show(it);

                }
        }

        if(ifFind == 0){ // is not find the value return the cursor to the original place
            it->nextNode = it->tempNext;
            it->prevNode = it->tempPrev;
            pFindNext = 0;
        }
    }

  return pFindNext;
}

int *findPrevious(IteratorInt it, int v){

    int *pFindPrev = NULL;
    int ifFind = 0;
    it->tempNext = it->nextNode;
    it->tempPrev = it->prevNode;

    if(it->prevNode == NULL){
        pFindPrev = 0;
    }else{
        while(ifFind == 0 && it->prevNode!=NULL){

                printf("enter the while loop\n");

                if(it->nextNode->value == v){

                        printf("enter the if \n");

                    pFindPrev = it->nextNode->value;
                    it->lastReturn = it->nextNode;
                    ifFind = 1;
                }else{

                    printf("enter the else\n");

                    printf("1\n");

                    it->nextNode = it->prevNode;
                    printf("2\n");
                    it->prevNode = it->prevNode->prev;
                    printf("3\n");

                    show(it);

                }

        }

        if(ifFind = 0){ // if not find the value make cursor to the original place
            it->tempNext = it->nextNode;
            it->tempPrev = it->prevNode;
            pFindPrev = 0;
        }
    }

  return pFindPrev;
}



